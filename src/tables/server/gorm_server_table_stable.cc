#include "gorm_server_table_stable.h"
#include "gorm_mysql_conn_pool.h"

const char *GORM_GetColumnType(const GORM_PB_COLUMN_VALUE &columnValue)
{
    switch (columnValue.type())
    {
    case GORM_PB_COLUMN_TYPE_INT:
    {
        return "bigint";
    }
    case GORM_PB_COLUMN_TYPE_UINT:
    {
        return "bigint";
    }
    case GORM_PB_COLUMN_TYPE_DOUBLE:
    {
        return "double";
    }
    case GORM_PB_COLUMN_TYPE_STRING:
    {
        return "mediumtext";
    }
    }

    return "";
}

#define GORM_ADD_COLUMN_SQL "alter table `%s` add ("
// debug环境动态更新表结构
int GORM_MySQLUpdateTableSchema(GORM_MySQLEvent* pMySQLEvent, const char *szTable, const GORM_PB_CUSTEM_COLUMNS &pbColumns)
{
#ifndef GORM_DEBUG
    return GORM_OK;
#endif

    string strTable = szTable;
    if (pbColumns.columns_size() == 0)
        return GORM_OK;
    
    unordered_map<string, GORM_PB_COLUMN_TYPE> mapColumns = pMySQLEvent->m_mapTablesColumnInfo[strTable];
    bool bNeedAdd = false;
    int iSQLLen = 1024;
    for(int i=0; i<pbColumns.columns_size(); i++)
    {
        const GORM_PB_COLUMN &pbColumn = pbColumns.columns(i);
        auto itr = mapColumns.find(pbColumn.name());
        if (itr != mapColumns.end())
            continue;

        // 增加列
        bNeedAdd = true;
        iSQLLen += pbColumn.name().length() + 16;
    }

    if (!bNeedAdd)
        return GORM_OK;

    shared_ptr<char> szSQL(new char[iSQLLen], std::default_delete<char[]>());
    int iLen = snprintf(szSQL.get(), iSQLLen, GORM_ADD_COLUMN_SQL, (char*)strTable.c_str());
    for(int i=0; i<pbColumns.columns_size(); i++)
    {
        const GORM_PB_COLUMN &pbColumn = pbColumns.columns(i);
        auto itr = mapColumns.find(pbColumn.name());
        if (itr != mapColumns.end())
            continue;

        mapColumns[pbColumn.name()] = pbColumn.value().type();
        if (i != 0)
            iLen += snprintf(szSQL.get()+iLen, iSQLLen-iLen, ",");
        iLen += snprintf(szSQL.get()+iLen, iSQLLen-iLen, "`%s` %s", pbColumn.name().c_str(), GORM_GetColumnType(pbColumn.value()));
        pMySQLEvent->m_mapTablesColumnOrder[strTable].push_back(pbColumn.name());
    }
    iLen += snprintf(szSQL.get()+iLen, iSQLLen-iLen, ")");
    pMySQLEvent->MySQLSyncQuery(szSQL.get(), iLen);

    pMySQLEvent->m_mapTablesColumnInfo[strTable] = mapColumns;
    return GORM_OK;
}

