#include "gorm_inc.h"
#include "gorm_sys_inc.h"
#include "gorm_client_event.h"
#include "gorm_server.h"
#include "gorm_log.h"
#include "gorm_utils.h"
#include "gorm_tables.h"

using namespace gorm;

GORM_Server g_global_server;

int TestInsert()
{
    GORM_ClientRequest *pRequest = g_global_server.GetRequestForInsert("account");
    if (pRequest == nullptr)
    {
        std::cout << "get request failed" << std::endl;
        return -1;
    }

    GORM_Record *pRecord = nullptr;
    if (GORM_OK != pRequest->AddRecord(pRecord))
    {
        std::cout << "insert add record failed" << std::endl;
        return -1;
    }

    // 设置record
    if (GORM_OK != pRecord->SetFieldValue("id", 100))
    {
        std::cout << "set record value failed, for id" << std::endl;
        return -1;
    }
    if (GORM_OK != pRecord->SetFieldValue("account", "account_field"))
    {
        std::cout << "set record value failed, for id" << std::endl;
        return -1;
    }

    uint32  ulCBID;
    if (GORM_OK != g_global_server.SendRequest(pRequest, ulCBID))
    {
        std::cout << "send request failed." << std::endl;
        return -1;
    }

    std::cout << "sent request to gorm server" << std::endl;

    return 0;
}

int TestGet()
{
    GORM_ClientRequest *pRequest = g_global_server.GetRequestForGet("account");
    if (pRequest == nullptr)
    {
        std::cout << "get request failed" << std::endl;
        return -1;
    }

    GORM_Record *pRecord = nullptr;
    if (GORM_OK != pRequest->AddRecord(pRecord))
    {
        std::cout << "insert add record failed" << std::endl;
        return -1;
    }

    // 设置record
    if (GORM_OK != pRecord->SetFieldValue("id", 100))
    {
        std::cout << "set record value failed, for id" << std::endl;
        return -1;
    }
    if (GORM_OK != pRecord->SetFieldValue("account", "account_field"))
    {
        std::cout << "set record value failed, for account" << std::endl;
        return -1;
    }

    uint32  ulCBID;
    if (GORM_OK != g_global_server.SendRequest(pRequest, ulCBID))
    {
        std::cout << "send request failed." << std::endl;
        return -1;
    }

    std::cout << "sent request to gorm server" << std::endl;

    return 0;
}

int TestDelete()
{
    GORM_ClientRequest *pRequest = g_global_server.GetRequestForDelete("account");
    if (pRequest == nullptr)
    {
        std::cout << "get request failed" << std::endl;
        return -1;
    }

    GORM_Record *pRecord = nullptr;
    if (GORM_OK != pRequest->AddRecord(pRecord))
    {
        std::cout << "insert add record failed" << std::endl;
        return -1;
    }

    // 设置record
    if (GORM_OK != pRecord->SetFieldValue("id", 100))
    {
        std::cout << "set record value failed, for id" << std::endl;
        return -1;
    }
    if (GORM_OK != pRecord->SetFieldValue("account", "account_field"))
    {
        std::cout << "set record value failed, for account" << std::endl;
        return -1;
    }

    uint32  ulCBID;
    if (GORM_OK != g_global_server.SendRequest(pRequest, ulCBID))
    {
        std::cout << "send request failed." << std::endl;
        return -1;
    }

    std::cout << "sent request to gorm server" << std::endl;

    return 0;
}

int TestUpdate() 
{
    GORM_ClientRequest *pRequest = g_global_server.GetRequestForUpdate("account");
    if (pRequest == nullptr)
    {
        std::cout << "get request failed" << std::endl;
        return -1;
    }

    GORM_Record *pRecord = nullptr;
    if (GORM_OK != pRequest->AddRecord(pRecord))
    {
        std::cout << "insert add record failed" << std::endl;
        return -1;
    }

    // 设置record
    if (GORM_OK != pRecord->SetFieldValue("id", 100))
    {
        std::cout << "set record value failed, for id" << std::endl;
        return -1;
    }
    if (GORM_OK != pRecord->SetFieldValue("account", "account_field"))
    {
        std::cout << "set record value failed, for account" << std::endl;
        return -1;
    }
    if (GORM_OK != pRecord->SetFieldValue("desc", "test update"))
    {
        std::cout << "set record value failed, for account" << std::endl;
        return -1;
    }

    uint32  ulCBID;
    if (GORM_OK != g_global_server.SendRequest(pRequest, ulCBID))
    {
        std::cout << "send request failed." << std::endl;
        return -1;
    }

    std::cout << "sent request to gorm server" << std::endl;

    return 0;
}

int TestINCREASE()
{
    GORM_ClientRequest *pRequest = g_global_server.GetRequestForIncrease("bag");
    if (pRequest == nullptr)
    {
        std::cout << "get request failed" << std::endl;
        return -1;
    }

    GORM_Record *pRecord = nullptr;
    if (GORM_OK != pRequest->AddRecord(pRecord))
    {
        std::cout << "insert add record failed" << std::endl;
        return -1;
    }

    // 设置record
    if (GORM_OK != pRecord->SetFieldValue("uid", 100))
    {
        std::cout << "set record value failed, for id" << std::endl;
        return -1;
    }
    if (GORM_OK != pRecord->SetFieldValue("bagid", 123))
    {
        std::cout << "set record value failed, for account" << std::endl;
        return -1;
    }

    uint32  ulCBID;
    if (GORM_OK != g_global_server.SendRequest(pRequest, ulCBID))
    {
        std::cout << "send request failed." << std::endl;
        return -1;
    }

    std::cout << "sent request to gorm server" << std::endl;

    return 0;
}

int TestReplace()
{
    GORM_ClientRequest *pRequest = g_global_server.GetRequestForReplace("account");
    if (pRequest == nullptr)
    {
        std::cout << "get request failed" << std::endl;
        return -1;
    }

    GORM_Record *pRecord = nullptr;
    if (GORM_OK != pRequest->AddRecord(pRecord))
    {
        std::cout << "insert add record failed" << std::endl;
        return -1;
    }

    // 设置record
    if (GORM_OK != pRecord->SetFieldValue("id", 100))
    {
        std::cout << "set record value failed, for id" << std::endl;
        return -1;
    }
    if (GORM_OK != pRecord->SetFieldValue("account", "account"))
    {
        std::cout << "set record value failed, for account" << std::endl;
        return -1;
    }
    if (GORM_OK != pRecord->SetFieldValue("desc", "desc"))
    {
        std::cout << "set record value failed, for account" << std::endl;
        return -1;
    }

    uint32  ulCBID;
    if (GORM_OK != g_global_server.SendRequest(pRequest, ulCBID))
    {
        std::cout << "send request failed." << std::endl;
        return -1;
    }

    std::cout << "sent request to gorm server" << std::endl;

    return 0;
}

int TestBatchGet()
{
    GORM_ClientRequest *pRequest = g_global_server.GetRequestForBatchGet("account");
    if (pRequest == nullptr)
    {
        std::cout << "get request failed" << std::endl;
        return -1;
    }

    GORM_Record *pRecord = nullptr;
    if (GORM_OK != pRequest->AddRecord(pRecord))
    {
        std::cout << "insert add record failed" << std::endl;
        return -1;
    }

    // 设置record
    if (GORM_OK != pRecord->SetFieldValue("id", 100))
    {
        std::cout << "set record value failed, for id" << std::endl;
        return -1;
    }
    if (GORM_OK != pRecord->SetFieldValue("account", "account"))
    {
        std::cout << "set record value failed, for account" << std::endl;
        return -1;
    }

    if (GORM_OK != pRequest->AddRecord(pRecord))
    {
        std::cout << "insert add record failed" << std::endl;
        return -1;
    }

    // 设置record
    if (GORM_OK != pRecord->SetFieldValue("id", 101))
    {
        std::cout << "set record value failed, for id" << std::endl;
        return -1;
    }
    if (GORM_OK != pRecord->SetFieldValue("account", "account"))
    {
        std::cout << "set record value failed, for account" << std::endl;
        return -1;
    }


    uint32  ulCBID;
    if (GORM_OK != g_global_server.SendRequest(pRequest, ulCBID))
    {
        std::cout << "send request failed." << std::endl;
        return -1;
    }

    std::cout << "sent request to gorm server" << std::endl;

    return 0;
}

int TestGetByPartKey()
{
    GORM_ClientRequest *pRequest = g_global_server.GetRequestForGetByPartKey("account");
    if (pRequest == nullptr)
    {
        std::cout << "get request failed" << std::endl;
        return -1;
    }

    pRequest->AddField("id");
    vector<char*> vFields;
    vFields.push_back("account");
    vFields.push_back("desc");
    pRequest->AddField(vFields);

    GORM_Record *pRecord = nullptr;
    if (GORM_OK != pRequest->AddRecord(pRecord))
    {
        std::cout << "insert add record failed" << std::endl;
        return -1;
    }

    // 设置record
    if (GORM_OK != pRecord->SetFieldValue("id", 100))
    {
        std::cout << "set record value failed, for id" << std::endl;
        return -1;
    }
    if (GORM_OK != pRecord->SetFieldValue("account", "account"))
    {
        std::cout << "set record value failed, for account" << std::endl;
        return -1;
    }

    if (GORM_OK != pRequest->AddRecord(pRecord))
    {
        std::cout << "insert add record failed" << std::endl;
        return -1;
    }

    // 设置record
    if (GORM_OK != pRecord->SetFieldValue("id", 101))
    {
        std::cout << "set record value failed, for id" << std::endl;
        return -1;
    }
    if (GORM_OK != pRecord->SetFieldValue("account", "account"))
    {
        std::cout << "set record value failed, for account" << std::endl;
        return -1;
    }


    uint32  ulCBID;
    if (GORM_OK != g_global_server.SendRequest(pRequest, ulCBID))
    {
        std::cout << "send request failed." << std::endl;
        return -1;
    }

    std::cout << "sent request to gorm server" << std::endl;

    return 0;
}


int main()
{
    if (GORM_OK != g_global_server.Init(GORM_DefaultLog::Instance(), "", "127.0.0.1:8806"))
    {
        std::cout << "init gorm server failed." <<std::endl;
        return -1;
    }
    if (!g_global_server.Start())
    {
        std::cout << "start gorm client failed." << endl;
        return -1;
    }

    if (0 != TestGet())
    {
        return -1;
    }

    for(;;)
    {
        // 检查是否有响应
        GORM_ClientResponse *pResponse = nullptr;
        g_global_server.RecvResponse(pResponse);
        if (pResponse != nullptr)
        {
            char *pTableName = nullptr;
            pResponse->GetTableName(pTableName);
            std::cout << "response table name is:" << pTableName << std::endl;
            // 处理response
            std::cout << "got one result from gorm server." << std::endl;
            PB_MSG_PTR pPbMsg = nullptr;
            int iRet = pResponse->GetSrcPbMsg(pPbMsg);
            if (iRet != GORM_OK || pPbMsg == nullptr)
            {
                std::cout << "got src pb message failed from response." << std::endl;
                break;
            }
            gorm::GORM_PB_GET_RSP *pGetPbMsg = dynamic_cast<GORM_PB_GET_RSP*>(pPbMsg);
            /////////直接操作pGetPbMsg效率最高///////////////////////////
            
            GROM_ResponseCode *pRspCode = nullptr;
            pResponse->GetResultCode(pRspCode);
            if (pRspCode->code != GORM_OK)
            {
                std::cout <<"get data failed, code:" << pRspCode->code << ", db error number:" << pRspCode->dbError << ", db error info:" << pRspCode->dbErrorInfo << std::endl;
                break;
            }
            // 直接操作pPbMsg，效率最高
            GORM_Record *pResultRecord = nullptr;
            iRet = pResponse->GetRecord(pResultRecord);
            if (iRet != GORM_OK || pResultRecord == nullptr)
            {
                std::cout << "got record from response failed" << iRet << std::endl;
                break;
            }
            ///////////////////////不操作pb消息，直接通过接口获取结果//////////////////////////////
            int32 iAccountID = 0;
            pResultRecord->GetFieldValue("id", iAccountID);
            std::string strAccountAccField;
            pResultRecord->GetFieldValue(gorm::GORM_PB_ACCOUNT_FIELD_INDEX::GORM_PB_FIELD_ACCOUNT_ACCOUNT, strAccountAccField);
            std::cout << "got result from api, id:" << iAccountID << ", account field:" << strAccountAccField << std::endl;
            
            ///////////////////////直接操作pb消息获取结果//////////////////////////////
            PB_MSG_PTR pPbTableData = nullptr;
            pResultRecord->GetData(pPbTableData);
            // 直接使用pb消息，此为gorm-db.xml转为的gorm-db.proto协议中的GORM_PB_Table_account消息
            gorm::GORM_PB_Table_account *pAccount = dynamic_cast<GORM_PB_Table_account*>(pPbTableData);
            if (pAccount == nullptr)
            {
                std::cout << "got account from db failed." << std::endl;
                break;
            }
            std::cout << "got account, id:"<< pAccount->id() << ", account:"<< pAccount->account() << std::endl;
            break;
        }
        ThreadSleepMilliSeconds(10);
    }

    g_global_server.Fini();
    return 0;
}

