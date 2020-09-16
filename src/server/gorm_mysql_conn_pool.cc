#include "gorm_mysql_conn_pool.h"
#include "gorm_log.h"
#include "gorm_mysql_request.h"
#include "gorm_table_field_map_define.h"

using namespace gorm;

GORM_MySQLEvent::GORM_MySQLEvent(shared_ptr<GORM_Epoll> &pEpoll, MYSQL *pMySQL, int iFD, GORM_DBInfo *pDbCfg,  GORM_MySQLConnPool *pPool) :
    GORM_Event(iFD, pEpoll), m_pMySQL(pMySQL), m_pDbCfg(pDbCfg), m_pMySQLConnPool(pPool)
{
    m_pSendingToMySQLRing = make_shared<GORM_RingBuffer<GORM_MySQLRequest>>(GORM_REQUEST_BUFF_LEN);
    this->m_strDBName = pDbCfg->szDB;
    this->m_Status = GORM_CONNECT_CONNECTED;
}

GORM_MySQLEvent::~GORM_MySQLEvent()
{
    if (this->m_pMySQL != nullptr)
    {
        mysql_close(this->m_pMySQL);
        this->m_pMySQL = nullptr;
    }
}

int GORM_MySQLEvent::MySQLSyncFetchRow(MYSQL_ROW &row)
{
    do{
        m_iMySQLNetStatus = mysql_fetch_row_nonblocking(this->m_pReadingMySQLResult, &row);
    }while(NET_ASYNC_NOT_READY == m_iMySQLNetStatus);
    
    if (m_iMySQLNetStatus == NET_ASYNC_ERROR)
    {
        return GORM_ERROR;
    }
    return GORM_OK;
}

int GORM_MySQLEvent::MySQLSyncStoreResult()
{
    do{
        m_iMySQLNetStatus = mysql_store_result_nonblocking(this->m_pMySQL, &m_pReadingMySQLResult);
    } while(NET_ASYNC_NOT_READY == m_iMySQLNetStatus);
    
    if (m_iMySQLNetStatus == NET_ASYNC_ERROR)
    {
        return GORM_ERROR;
    }

    return GORM_OK;
}

int GORM_MySQLEvent::MySQLSyncQuery(char *szSQL, int iLen)
{
    do
    {
        m_iMySQLNetStatus = mysql_real_query_nonblocking(this->m_pMySQL, szSQL, iLen);
    }
    while (NET_ASYNC_NOT_READY == m_iMySQLNetStatus);

    if (m_iMySQLNetStatus == NET_ASYNC_ERROR)
    {
        return GORM_ERROR;
    }
    return GORM_OK;
}

int GORM_MySQLEvent::Write()
{
    return this->Loop();
}

int GORM_MySQLEvent::Read()
{
    return this->Loop();
}

int GORM_MySQLEvent::SendMsg2MySQL()
{
    GORM_DBRequest *pRequest = nullptr;
    // 1、获取需要发送的SQL请求
    // 判断是否有需要发送的旧的消息
    if (this->m_pSendingRequest == nullptr)
    {
        this->m_pSendingRequest = this->m_pSendingToMySQLRing->PopFront();
        if (this->m_pSendingRequest == nullptr)
        {
            this->FinishReading();
            return GORM_OK;
        }
        this->m_pSendingRequest->pDbEvent = this;
        this->m_pReadingRequest = this->m_pSendingRequest;
        int iRet = this->m_pSendingRequest->PackSQL();
        if (iRet != GORM_OK)
        {
            GORM_LOGE("pack sql failed, return error to client, table:%d, seqid:%d", this->m_pReadingRequest->iReqTableId, this->m_pReadingRequest->uiReqID);
            this->WriteError(iRet);
            this->FinishWriting();
            return GORM_OK;
        }
        GORM_LOGD("sending message to mysql:%s", GORM_SQL_REQ(this->m_pSendingRequest));
    }
    pRequest = this->m_pSendingRequest;
    if (pRequest == nullptr)
    {
        this->m_iOptStep = MYSQL_OPT_WAITING_REQ;
        this->FinishWriting();
        return GORM_OK;
    }
    this->m_iOptStep = MYSQL_SENDING_REQ;
    // 2、发送SQL请求
    m_iMySQLNetStatus = mysql_real_query_nonblocking(this->m_pMySQL, GORM_SQL_REQ(pRequest),
                                    (unsigned long)GORM_SQL_REQ_LEN(pRequest));
    if (m_iMySQLNetStatus == NET_ASYNC_ERROR)
    {
        GORM_LOGE("sending message to mysql failed:%s, error:%s", GORM_SQL_REQ(pRequest), this->DBError());               
        this->WriteError(GORM_DB_ERROR, this->DBErrNo(), this->DBError());
        // 判断是否还有消息，如果没有其它消息需要发送则删除
        if (this->m_pSendingToMySQLRing->GetNum() == 0)
        {
            this->m_iOptStep = MYSQL_OPT_WAITING_REQ;
        }
        this->FinishWriting();
        return GORM_ERROR;
    }
    if (m_iMySQLNetStatus == NET_ASYNC_COMPLETE)
    {   
        // 每次只发送一个消息，待获取到响应之后再发送下一个消息
        this->m_iOptStep = MYSQL_STORE_RESULT;
        GORM_LOGD("sending message success:%s", GORM_SQL_REQ(pRequest));
        this->FinishWriting();
        return GORM_OK;
    }

    return GORM_OK;
}

int GORM_MySQLEvent::ReadFromMySQL()
{
    if (this->m_iOptStep == MYSQL_OPT_CONNECTING)
    {
        m_iMySQLNetStatus = mysql_real_connect_nonblocking(this->m_pMySQL, m_pDbCfg->szHost, m_pDbCfg->szUser,
                                                  m_pDbCfg->szPW, m_pDbCfg->szDB, m_pDbCfg->uiPort,
                                                  nullptr, CLIENT_COMPRESS|CLIENT_MULTI_STATEMENTS|CLIENT_INTERACTIVE);
        if (m_iMySQLNetStatus == NET_ASYNC_ERROR)
        {
            GORM_LOGE("connect to mysql failed, %s, %s, errinfo:%s", m_pDbCfg->szDBSymbol, m_pMySQLConnPool->m_szUrl, this->DBError());
            // TODO 线程退出
            return GORM_ERROR;
        }
        if (this->m_iMySQLNetStatus == NET_ASYNC_NOT_READY)
        {
            return GORM_OK;
        }
        this->m_iMySQLNetStatus = NET_ASYNC_COMPLETE;
        this->ConnectSuccessCB();
        // 连接mysql成功
        GORM_LOGI("connect to mysql success:%s", this->m_pMySQLConnPool->m_szUrl);
        return GORM_OK;
    }
    // 1、检查是否有需要读取的数据
    switch (m_iOptStep)
    {
        case MYSQL_STORE_RESULT:
        {
            ASSERT(this->m_pReadingRequest != nullptr);
            if (GORM_OK != this->StoreResult())
            {
                this->GotResults(GORM_DB_ERROR, this->DBErrNo(), this->DBError());
                return GORM_ERROR;
            }
            if (this->m_iOptStep == MYSQL_FETCH_ROW)
            {
                int iRet = this->FetchRows();
                if (GORM_OK != iRet)
                {
                    this->GotResults(iRet, this->DBErrNo(), this->DBError());
                    return GORM_ERROR;
                }
            }
            break;
        }
        case MYSQL_FETCH_ROW:
        {
            int iRet = this->FetchRows();
            if (GORM_OK != iRet)
            {
                this->GotResults(iRet, this->DBErrNo(), this->DBError());
                return GORM_ERROR;
            }
            break;
        }
        default:
        {
            ASSERT(false);
        }
    }
    
    return GORM_OK;
}

GORM_Ret GORM_MySQLEvent::StoreResult()
{
    // 如果是删除和插入则直接返回结果
    int iReqCmd = this->m_pReadingRequest->iReqCmd;
    if (m_pReadingRequest->iRedirectCmd != GORM_CMD_INVALID)
        iReqCmd = m_pReadingRequest->iRedirectCmd;
    switch (iReqCmd)
    {
    case GORM_CMD_INSERT:
    {
        int iAffectRows = mysql_affected_rows(this->m_pMySQL);
        this->m_pReadingRequest->InsertResult(GORM_OK, iAffectRows);
        if (iAffectRows == 1)
            this->GotResults();
        else
            this->GotResults(GORM_DB_ERROR, this->DBErrNo(), this->DBError());
        break;
    }
    case GORM_CMD_DELETE:
    {
        int iAffectRows = mysql_affected_rows(this->m_pMySQL);
        this->m_pReadingRequest->DeleteResult(GORM_OK, iAffectRows);
        this->GotResults();
        break;
    }
    case GORM_CMD_UPDATE:
    {
        this->m_pReadingRequest->UpdateResult(GORM_OK, mysql_affected_rows(this->m_pMySQL));
        this->GotResults();
        break;
    }
    case GORM_CMD_INCREASE:
    {
        int iAffectedNows = mysql_affected_rows(this->m_pMySQL);
        // 没有
        if (iAffectedNows == 0)
        {
            if (this->m_pReadingRequest->increaseFlag == GORM_IncreaseFlag_AutoCreate)
            {
                // TODO 将当前数据关闭，重新组装默认insert语句
                //return GORM_OK;
                //this->FinishReading();
                // 获取新的数据重新组装
                
                return GORM_OK;
            }
        }
        this->m_pReadingRequest->IncreaseResult(GORM_OK, iAffectedNows);
        this->GotResults();
        break;
    }
    case GORM_CMD_REPLACE:
    {
        this->m_pReadingRequest->ReplaceResult(GORM_OK, mysql_affected_rows(this->m_pMySQL));
        this->GotResults();
        break;
    }
    case GORM_CMD_BATCH_GET:
    case GORM_CMD_GET_BY_PARTKEY:
    case GORM_CMD_GET:
    case GORM_CMD_GET_BY_NON_PRIMARY_KEY:
    {
        m_iMySQLNetStatus = mysql_store_result_nonblocking(this->m_pMySQL, &m_pReadingMySQLResult);
        if (m_iMySQLNetStatus == NET_ASYNC_ERROR)
        {
            GORM_LOGE("reading data from mysql failed:%s", this->DBError());
            this->m_iOptStep = MYSQL_READ_FINISH;
            return GORM_ERROR;
        }
        if (m_iMySQLNetStatus == NET_ASYNC_NOT_READY)
        {
            GORM_LOGD("reading data from mysql not ready.");
            return GORM_OK;
        }
        if (m_pReadingMySQLResult == nullptr)
        {
            // TODO 没有数据,将结果发送给对方
            this->m_iOptStep = MYSQL_READ_FINISH;
            return GORM_OK;
        }
        this->m_iOptStep = MYSQL_FETCH_ROW;
        break;
    }
    default:
    {
        ASSERT(false);
        return GORM_OK;
    }
    }
    
    return GORM_OK;
}

GORM_Ret GORM_MySQLEvent::FetchRows()
{
    // 检查有没有结果，如果没有结果则直接返回
    if (m_iReadingRows == 0)
    {
        m_iReadingRows =mysql_num_rows(this->m_pReadingMySQLResult);
    }
    for(; m_iReadedRows<m_iReadingRows; )
    {
        MYSQL_ROW row;
        bool bNext = false;
        // 最多尝试读取5次
        for(int i=0; i<5; i++)
        {
            int iRet = mysql_fetch_row_nonblocking(this->m_pReadingMySQLResult, &row);
            if (iRet == NET_ASYNC_ERROR)
            {
                GORM_LOGE("got result from mysql failed, errinfo:", this->DBError());
                this->m_iOptStep = MYSQL_READ_FINISH;
                return GORM_DB_ERROR;
            }
            if (iRet == NET_ASYNC_COMPLETE)
            {
                m_iReadedRows++;
                bNext = true;
                unsigned long *lengths= mysql_fetch_lengths(this->m_pReadingMySQLResult);
                if (GORM_OK != this->m_pReadingRequest->GetOneRow(row, lengths))
                {
                    this->m_iOptStep = MYSQL_READ_FINISH;
                    return GORM_DB_2_STRUCT_ERROR;
                }
                break;
            }
        }
        // 一行数据没有读完
        if (!bNext)
        {
            break;
        }
    }
    if (m_iReadedRows == m_iReadingRows)
    {
        this->m_iOptStep = MYSQL_READ_FINISH;
    }
    
    return GORM_OK;
}

char *GORM_MySQLEvent::DBError()
{
    return (char*)mysql_error(m_pMySQL);
}

int GORM_MySQLEvent::DBErrNo()
{
    return mysql_errno(m_pMySQL);
}

int GORM_MySQLEvent::GetMySQLTableInfo()
{
    if (GORM_OK !=  GORM_InitTableColumnInfo(m_mapTablesColumnOrder, m_mapTablesColumnInfo))
    {
        GORM_LOGE("init table column info failed.");
        return GORM_ERROR;
    }
    char *szSql = "SELECT column_name,table_name,data_type FROM information_schema.columns where table_schema=\"%s\"";
    char sql[2048];
    int iLen = snprintf(sql, 2048, szSql, m_strDBName.c_str());
    if (GORM_OK != MySQLSyncQuery(sql, iLen))
    {
        GORM_LOGE("get table info from mysql failed, errinfo:%s, errno:%d", this->DBError(), this->DBErrNo());
        return GORM_ERROR;
    }

    if (GORM_OK != MySQLSyncStoreResult())
    {
        GORM_LOGE("get table info from mysql failed, errinfo:%s, errno:%d", this->DBError(), this->DBErrNo());
        return GORM_ERROR;
    }


    int iRows =mysql_num_rows(this->m_pReadingMySQLResult);
    for(int i=0; i<iRows; i++)
    {
        MYSQL_ROW row;
        int iRet = this->MySQLSyncFetchRow(row);
        if (iRet != GORM_OK)
        {
            GORM_LOGE("get table info from mysql failed, errinfo:%s, errno:%d", this->DBError(), this->DBErrNo());
            return GORM_ERROR;
        }

        unsigned long *lengths= mysql_fetch_lengths(this->m_pReadingMySQLResult);
        if (GORM_OK != MySQLTableInfoUpdate(row, lengths))
        {
            GORM_LOGE("get table info from mysql failed, parse result failed.");
            return GORM_ERROR;
        }
    }

    return GORM_OK;
}

int GORM_MySQLEvent::MySQLTableInfoUpdate(MYSQL_ROW row, unsigned long *lengths)
{
    string tableName(row[1], lengths[1]);
    auto itr = m_mapTablesColumnInfo.find(tableName);

    unordered_map<string, GORM_PB_COLUMN_TYPE> colMap;
    if (itr != m_mapTablesColumnInfo.end())
    {
        colMap = itr->second;
    }

    string strColName = string(row[0], lengths[0]);
    if (colMap.find(strColName) != colMap.end())
    {
        return GORM_OK;
    }

    string strColumnType(row[2], lengths[2]);

    GORM_PB_COLUMN_TYPE iType = GORM_PB_COLUMN_TYPE_INVALID;

    static unordered_map<string, GORM_PB_COLUMN_TYPE> mapColumnType = {
        {"char", GORM_PB_COLUMN_TYPE_STRING},
        {"varchar", GORM_PB_COLUMN_TYPE_STRING},
        {"mediumtext", GORM_PB_COLUMN_TYPE_STRING},
        {"mediumblob", GORM_PB_COLUMN_TYPE_STRING},
        {"mediumstring", GORM_PB_COLUMN_TYPE_STRING},
        {"blob", GORM_PB_COLUMN_TYPE_STRING},
        {"text", GORM_PB_COLUMN_TYPE_STRING},
        {"string", GORM_PB_COLUMN_TYPE_STRING},

        {"double", GORM_PB_COLUMN_TYPE_DOUBLE},

        {"bigint", GORM_PB_COLUMN_TYPE_DOUBLE},
        {"int", GORM_PB_COLUMN_TYPE_DOUBLE},
        {"tinyint", GORM_PB_COLUMN_TYPE_DOUBLE},
        {"smallint", GORM_PB_COLUMN_TYPE_DOUBLE},
    };
    iType = mapColumnType[strColumnType];

    if (iType == GORM_PB_COLUMN_TYPE_INVALID)
    {
        GORM_LOGE("not support column type, table:%s, column:%s, type:%s", (char*)tableName.c_str(), (char*)strColName.c_str(), (char*)strColumnType.c_str());
        return GORM_ERROR;
    }

    vector<string> vectorColumnsOrder;
    auto orderItr = m_mapTablesColumnOrder.find(tableName);
    if (orderItr != m_mapTablesColumnOrder.end())
    {
        vectorColumnsOrder = orderItr->second;
    }
    vectorColumnsOrder.push_back(strColName);

    colMap[strColName] = iType;
    m_mapTablesColumnInfo[tableName] = colMap;

    m_mapTablesColumnOrder[tableName] = vectorColumnsOrder;
        
    return GORM_OK;
}

int GORM_MySQLEvent::ConnectSuccessCB()
{
    this->m_iOptStep = MYSQL_OPT_WAITING_REQ; // 需要处理数据
    GORM_GET_MYSQL_FD(this->m_pMySQL, this->m_iFD);
#ifdef GORM_DEBUG // 从数据库中获取表的信息
    if (GORM_OK != this->GetMySQLTableInfo())
    {
        GORM_LOGE("get table info from mysql failed.");
        return GORM_ERROR;
    }
#endif
    return GORM_OK;
}

int GORM_MySQLEvent::Loop()
{   
    switch (this->m_iOptStep)
    {
    case MYSQL_OPT_WAITING_REQ:
    {
        // 有新的请求则将请求发送给mysql
        this->SendMsg2MySQL();
        return GORM_OK;
    }
    case MYSQL_SENDING_REQ:
    {
        this->SendMsg2MySQL();
        return GORM_OK;
    }
    case MYSQL_STORE_RESULT:
    case MYSQL_FETCH_ROW:
    case MYSQL_OPT_CONNECTING:
    {
        this->ReadFromMySQL();
        return GORM_OK; 
    }
    // 发送结果给客户端
    case MYSQL_READ_FINISH:
    {
        this->GotResults();
        break;
    }
    default:
        ASSERT(false);
    }

    return GORM_OK;
}

void GORM_MySQLEvent::TryNextRequest()
{
    this->m_iOptStep = MYSQL_OPT_WAITING_REQ;
    if (this->m_pSendingToMySQLRing->GetNum() > 0)
    {
        this->m_iOptStep = MYSQL_SENDING_REQ;
    }
}

#define GORM_GOT_RESULT()                                                           \
int iRet = this->m_pReadingRequest->GetResult(iErrCode, iDBErrNo, szErrInfo);       \
this->m_pReadingRequest = nullptr;                                                  \
this->m_pSendingRequest = nullptr;

#define GORM_GET_CONV_TO_INSERT()

// 获取到结果了
void GORM_MySQLEvent::GotResults(int iErrCode, int iDBErrNo, char *szErrInfo)
{
    this->m_iOptStep = MYSQL_OPT_WAITING_REQ;
    // TODO 判断是否还有需要读取的数据，如果还有则需要继续读取
    this->FinishReading();

    // TODO 如果是需要回带结果，则继续发起get请求
    if (iErrCode != GORM_OK)
    {
        GORM_GOT_RESULT();
        return;
    }

    if (this->m_pReadingRequest->bGotReturn)
    {
        GORM_GOT_RESULT();
        return;
    }
    // 重新发起请求
    if (this->m_pReadingRequest->cReplyFlag !=  GORM_ResultFlag_RETURN_CODE)
    {
        this->m_pReadingRequest->iRedirectCmd = GORM_CMD_GET;
        this->m_pReadingRequest->bGotReturn = true;
        this->m_pSendingRequest = this->m_pReadingRequest;
        this->m_iOptStep = MYSQL_SENDING_REQ;
        // 重新打包SQL
        int iRet = this->m_pSendingRequest->PackSQL();
        if (iRet != GORM_OK)
        {
            iErrCode = iRet;
            GORM_GOT_RESULT();
        }
        return;
    } else if (this->m_pReadingRequest->iGetFlag == GORM_GET_FLAG_NON_INSERT) {
        if (this->m_pReadingRequest->pRspPbMsg == nullptr)
        {
            this->m_pReadingRequest->iRedirectCmd = GORM_CMD_INSERT;
            this->m_pReadingRequest->bGotReturn = true;
            this->m_pSendingRequest = this->m_pReadingRequest;
            this->m_iOptStep = MYSQL_SENDING_REQ;
            // 重新打包SQL
            int iRet = this->m_pSendingRequest->PackSQL();
            if (iRet != GORM_OK)
            {
                iErrCode = iRet;
                GORM_GOT_RESULT();
            }
            return;
        }
        GORM_PB_GET_RSP *pGetPbRsp = dynamic_cast<GORM_PB_GET_RSP*>(this->m_pReadingRequest->pRspPbMsg);
        if (pGetPbRsp != nullptr && !pGetPbRsp->has_table())
        {
            return;
        }
    }

    GORM_GOT_RESULT();
    return;
}

void GORM_MySQLEvent::FinishReading()
{
    if (this->m_pReadingMySQLResult != nullptr)
    {
        mysql_free_result(m_pReadingMySQLResult);
        this->m_pReadingMySQLResult = nullptr;
    }
    this->m_iReadedRows = 0;
    this->m_iReadingRows = 0;
    // 如果没有消息则移出事件触发器
    if (m_pSendingToMySQLRing->GetNum() == 0)
    {
        this->DelRW();
    }
}

void GORM_MySQLEvent::FinishWriting()
{
    if (this->m_pSendingRequest != nullptr)
    {
        this->m_pSendingRequest->FinishSending2DB();
        this->m_pSendingRequest = nullptr;
    }
}


void GORM_MySQLEvent::WriteError(int iErrCode, int iDBErrNo, char *szErrInfo)
{
    this->GotResults(iErrCode, iDBErrNo, szErrInfo);
}

GORM_MySQLConnPool::GORM_MySQLConnPool(int iMaxPoolSize):GORM_DBConnPool(iMaxPoolSize)
{
    bzero(m_EventList, sizeof(GORM_MySQLEvent*)*GOMR_MAX_CONNECT_NUM_PER_THREAD);
}

GORM_MySQLConnPool::~GORM_MySQLConnPool()
{
    if (this->m_pEvent != nullptr)
    {
        delete this->m_pEvent;
        this->m_pEvent = nullptr;
    }
    GORM_MySQLEvent *pEvent = nullptr;
    for (int i=0; i<this->m_iMaxPoolSize; i++)
    {
        pEvent = this->m_EventList[i];
        if (pEvent == nullptr)
            continue;
        delete pEvent;
    }
}

bool GORM_MySQLConnPool::Init(shared_ptr<GORM_Epoll> &pEpoll, GORM_DBInfo *pDbCfg, const mutex *m)
{
    if (!this->GeneralUrl(pDbCfg))
    {
        GORM_LOGE("generate database url failed.");
        return false;
    }

    
    GORM_MySQLEvent *pEvent = nullptr;
    for (int i=0; i<this->m_iMaxPoolSize; i++)
    {
        pEvent = nullptr;
        if (!this->ConnectToMySQL(pEpoll, pEvent, pDbCfg, m))
        {
            return false;
        }
        this->m_EventList[i] = pEvent;
    }

    return true;
}

bool GORM_MySQLConnPool::GetMYSQL(GORM_DBInfo *pDbCfg,const mutex *m, MYSQL *&pMySQL, net_async_status &iConnectStatus)
{
    unique_lock<mutex> locker(*(mutex*)(m));
    // 和mysql建立连接
    pMySQL = mysql_init(NULL);
    if (pMySQL == nullptr)
    {
        GORM_LOGE("mysql_init failed:%s", pDbCfg->szDBSymbol);
        return false;
    }

    iConnectStatus = NET_ASYNC_ERROR;
    while ((iConnectStatus = mysql_real_connect_nonblocking(pMySQL, pDbCfg->szHost, pDbCfg->szUser,
                                                  pDbCfg->szPW, pDbCfg->szDB, pDbCfg->uiPort,
                                                  nullptr, 0))
               == NET_ASYNC_NOT_READY);

    if (iConnectStatus == NET_ASYNC_ERROR)
    {
        GORM_LOGE("connect to mysql failed, db:%s, error:%s", pDbCfg->szDBSymbol, mysql_error(pMySQL));
        mysql_close(pMySQL);
        return false;
    }
    return true;
}

bool GORM_MySQLConnPool::GeneralUrl(GORM_DBInfo *pDbCfg)
{
    //mysql://ztgame:123456@192.168.181.191:3066/recordserver_test1
    int iLen = snprintf(m_szUrl, MAX_URL_LEN, "mysql://%s:%s@%s:%d/%s", 
        pDbCfg->szUser, pDbCfg->szPW, pDbCfg->szHost, pDbCfg->uiPort, pDbCfg->szDB);
    if (iLen >= MAX_URL_LEN-1)
    {
        iLen = MAX_URL_LEN-1;
    }
    m_szUrl[iLen] = '\n';
    return true;
}

void GORM_MySQLConnPool::Loop()
{
    this->m_pEvent->Loop();
}

bool GORM_MySQLConnPool::ConnectToMySQL(shared_ptr<GORM_Epoll> &pEpoll, GORM_MySQLEvent *&pEvent, GORM_DBInfo *pDbCfg, const mutex *m)
{
    MYSQL *pMySQL = nullptr;
    try
    {
        net_async_status iConnectStatus;
        if (!this->GetMYSQL(pDbCfg, m, pMySQL, iConnectStatus))
        {
            return false;
        }

        int iFD = 0;
        GORM_GET_MYSQL_FD(pMySQL, iFD);
        pEvent = new GORM_MySQLEvent(pEpoll, pMySQL, iFD, pDbCfg, this);
        if (iConnectStatus == NET_ASYNC_COMPLETE)
        {
            // 连接mysql成功
            GORM_LOGI("connect to mysql success:%s", this->m_szUrl);
            pEvent->m_iOptStep = MYSQL_OPT_WAITING_REQ;
            pEvent->ConnectSuccessCB();
        }
        else 
        {
            pEvent->m_iOptStep = MYSQL_OPT_CONNECTING;
        }
    }
    catch(exception &e)
    {
        GORM_LOGE("init work thread, connect to mysql failed, mysql address:%s, got exception:%s", this->m_szUrl, e.what());
        if (pEvent != nullptr)
        {
            delete pEvent;
            pEvent = nullptr;
        }
        else if (pMySQL != nullptr)
        {
            mysql_close(pMySQL);
        }
        return false;
    }
    
    return true;
}


