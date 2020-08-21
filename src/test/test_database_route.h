#include "gorm_db_config.h"

int TestLoadRoute()
{
    if (GORM_OK != ReloadRoute("./config/gorm-db.yml"))
    {
        cout << "load config failed" << endl;
        return GORM_ERROR;
    }

    GORM_RouteInfo *pConfig = GetDatabaseRoute();
    return GORM_OK;
}
