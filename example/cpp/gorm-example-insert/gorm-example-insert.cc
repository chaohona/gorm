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
    if (GORM_OK != pRecord->SetFieldValue("account", "123"))
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
    if (GORM_OK != pRecord->SetFieldValue("account", "123"))
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
    if (GORM_OK != pRecord->SetFieldValue("account", "123"))
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

    if (0 != TestInsert())
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
            // 处理response
            std::cout << "got one result from gorm server" << std::endl;
            GROM_ResponseCode *pRspCode = nullptr;
            pResponse->GetResultCode(pRspCode);
            std::cout << "insert result code:" << pRspCode->code << std::endl;
            if (pRspCode->code != GORM_OK)
            {
                std::cout <<"insert failed, code:" << pRspCode->code << ", db error number:" << pRspCode->dbError << ", db error info:" << pRspCode->dbErrorInfo << std::endl;
                break;
            }
            
            break;
        }
        ThreadSleepMilliSeconds(10);
    }

    g_global_server.Fini();
    return 0;
}

