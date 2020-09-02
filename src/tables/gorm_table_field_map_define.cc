#include "gorm_table_field_map_define.h"
#include "gorm_pb_tables_inc.pb.h"
#include "gorm_pb_proto.pb.h"
#include "gorm_mempool.h"
#include "gorm_hash.h"

namespace gorm{

int GORM_SetTableCURRENCYId2Name(OUT FieldId2Name &mapId2Name);
int GORM_SetTableCURRENCYName2Id(OUT FieldName2Id &mapName2Id);
int GORM_SetTableCYCLEEVENTId2Name(OUT FieldId2Name &mapId2Name);
int GORM_SetTableCYCLEEVENTName2Id(OUT FieldName2Id &mapName2Id);
int GORM_SetTableEQUIPId2Name(OUT FieldId2Name &mapId2Name);
int GORM_SetTableEQUIPName2Id(OUT FieldName2Id &mapName2Id);
int GORM_SetTableFOODId2Name(OUT FieldId2Name &mapId2Name);
int GORM_SetTableFOODName2Id(OUT FieldName2Id &mapName2Id);
int GORM_SetTableHEROId2Name(OUT FieldId2Name &mapId2Name);
int GORM_SetTableHEROName2Id(OUT FieldName2Id &mapName2Id);
int GORM_SetTableMAILId2Name(OUT FieldId2Name &mapId2Name);
int GORM_SetTableMAILName2Id(OUT FieldName2Id &mapName2Id);
int GORM_SetTableMATERIALId2Name(OUT FieldId2Name &mapId2Name);
int GORM_SetTableMATERIALName2Id(OUT FieldName2Id &mapName2Id);
int GORM_SetTableNPCId2Name(OUT FieldId2Name &mapId2Name);
int GORM_SetTableNPCName2Id(OUT FieldName2Id &mapName2Id);
int GORM_SetTableROLEId2Name(OUT FieldId2Name &mapId2Name);
int GORM_SetTableROLEName2Id(OUT FieldName2Id &mapName2Id);
int GORM_SetTableSCENEId2Name(OUT FieldId2Name &mapId2Name);
int GORM_SetTableSCENEName2Id(OUT FieldName2Id &mapName2Id);
int GORM_SetTableSKILLId2Name(OUT FieldId2Name &mapId2Name);
int GORM_SetTableSKILLName2Id(OUT FieldName2Id &mapName2Id);
int GORM_SetTableINTERACTIONId2Name(OUT FieldId2Name &mapId2Name);
int GORM_SetTableINTERACTIONName2Id(OUT FieldName2Id &mapName2Id);
int GORM_SetTableUSERId2Name(OUT FieldId2Name &mapId2Name);
int GORM_SetTableUSERName2Id(OUT FieldName2Id &mapName2Id);
int GORM_SetTableROLESId2Name(OUT FieldId2Name &mapId2Name);
int GORM_SetTableROLESName2Id(OUT FieldName2Id &mapName2Id);


int GORM_InitTableSchemaInfo(PB_MSG_PTR pMsgPtr)
{
    GORM_PB_HAND_SHAKE_REQ *pHandShake = dynamic_cast<GORM_PB_HAND_SHAKE_REQ*>(pMsgPtr);
    if (pHandShake == nullptr)
        return GORM_ERROR;
    GORM_PB_TABLE_SCHEMA_INFO *pInfo;
    GORM_PB_TABLE_SCHEMA_INFO_COLUMN *pColumn;
    pHandShake->mutable_header();
    pHandShake->set_version(1);
    pHandShake->set_md5(0);
    // for table currency
    pInfo = pHandShake->add_schemas();
    if (pInfo == nullptr)
        return GORM_ERROR;
    pInfo->set_version(1);
    pInfo->set_tablename("currency");
    pInfo->set_tableidx(1);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("version");
    pColumn->set_typedesc("uint64");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_UINT64);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("roleid");
    pColumn->set_typedesc("int64");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT64);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("snakeid");
    pColumn->set_typedesc("int32");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT32);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("currency1");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("currency2");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("currency3");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("currency4");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    // for table cycleevent
    pInfo = pHandShake->add_schemas();
    if (pInfo == nullptr)
        return GORM_ERROR;
    pInfo->set_version(1);
    pInfo->set_tablename("cycleevent");
    pInfo->set_tableidx(2);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("version");
    pColumn->set_typedesc("uint64");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_UINT64);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("roleid");
    pColumn->set_typedesc("int64");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT64);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("events");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    // for table equip
    pInfo = pHandShake->add_schemas();
    if (pInfo == nullptr)
        return GORM_ERROR;
    pInfo->set_version(1);
    pInfo->set_tablename("equip");
    pInfo->set_tableidx(3);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("version");
    pColumn->set_typedesc("uint64");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_UINT64);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("roleid");
    pColumn->set_typedesc("int64");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT64);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("snakeid");
    pColumn->set_typedesc("int32");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT32);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("equip1");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("equip2");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("equip3");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("equip4");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    // for table food
    pInfo = pHandShake->add_schemas();
    if (pInfo == nullptr)
        return GORM_ERROR;
    pInfo->set_version(1);
    pInfo->set_tablename("food");
    pInfo->set_tableidx(4);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("version");
    pColumn->set_typedesc("uint64");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_UINT64);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("roleid");
    pColumn->set_typedesc("int64");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT64);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("snakeid");
    pColumn->set_typedesc("int32");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT32);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("food1");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("food2");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("food3");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("food4");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    // for table hero
    pInfo = pHandShake->add_schemas();
    if (pInfo == nullptr)
        return GORM_ERROR;
    pInfo->set_version(1);
    pInfo->set_tablename("hero");
    pInfo->set_tableidx(5);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("version");
    pColumn->set_typedesc("uint64");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_UINT64);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("roleid");
    pColumn->set_typedesc("int64");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT64);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("snakeid");
    pColumn->set_typedesc("int32");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT32);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("heros");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    // for table mail
    pInfo = pHandShake->add_schemas();
    if (pInfo == nullptr)
        return GORM_ERROR;
    pInfo->set_version(1);
    pInfo->set_tablename("mail");
    pInfo->set_tableidx(6);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("version");
    pColumn->set_typedesc("uint64");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_UINT64);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("roleid");
    pColumn->set_typedesc("int64");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT64);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("mail1");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("mail2");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("mail3");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("mail4");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("mail5");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("lastmailid");
    pColumn->set_typedesc("int32");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT32);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("snakeid");
    pColumn->set_typedesc("int32");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT32);
    // for table material
    pInfo = pHandShake->add_schemas();
    if (pInfo == nullptr)
        return GORM_ERROR;
    pInfo->set_version(1);
    pInfo->set_tablename("material");
    pInfo->set_tableidx(7);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("version");
    pColumn->set_typedesc("uint64");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_UINT64);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("roleid");
    pColumn->set_typedesc("int64");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT64);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("snakeid");
    pColumn->set_typedesc("int32");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT32);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("material1");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("material2");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("material3");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("material4");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    // for table npc
    pInfo = pHandShake->add_schemas();
    if (pInfo == nullptr)
        return GORM_ERROR;
    pInfo->set_version(1);
    pInfo->set_tablename("npc");
    pInfo->set_tableidx(8);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("version");
    pColumn->set_typedesc("uint64");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_UINT64);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("roleid");
    pColumn->set_typedesc("int64");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT64);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("snakeid");
    pColumn->set_typedesc("int32");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT32);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("npcs");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    // for table role
    pInfo = pHandShake->add_schemas();
    if (pInfo == nullptr)
        return GORM_ERROR;
    pInfo->set_version(1);
    pInfo->set_tablename("role");
    pInfo->set_tableidx(9);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("version");
    pColumn->set_typedesc("uint64");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_UINT64);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("roleid");
    pColumn->set_typedesc("int64");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT64);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("rolename");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("level");
    pColumn->set_typedesc("int32");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT32);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("exp");
    pColumn->set_typedesc("int64");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT64);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("characterid");
    pColumn->set_typedesc("int32");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT32);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("gold");
    pColumn->set_typedesc("int32");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT32);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("offlinetime");
    pColumn->set_typedesc("int64");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT64);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("inited");
    pColumn->set_typedesc("int32");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT32);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("createtime");
    pColumn->set_typedesc("int64");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT64);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("face");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("online");
    pColumn->set_typedesc("int64");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT64);
    // for table scene
    pInfo = pHandShake->add_schemas();
    if (pInfo == nullptr)
        return GORM_ERROR;
    pInfo->set_version(1);
    pInfo->set_tablename("scene");
    pInfo->set_tableidx(10);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("version");
    pColumn->set_typedesc("uint64");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_UINT64);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("roleid");
    pColumn->set_typedesc("int64");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT64);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("sceneid");
    pColumn->set_typedesc("int32");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT32);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("collects");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    // for table skill
    pInfo = pHandShake->add_schemas();
    if (pInfo == nullptr)
        return GORM_ERROR;
    pInfo->set_version(1);
    pInfo->set_tablename("skill");
    pInfo->set_tableidx(11);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("version");
    pColumn->set_typedesc("uint64");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_UINT64);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("roleid");
    pColumn->set_typedesc("int64");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT64);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("snakeid");
    pColumn->set_typedesc("int32");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT32);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("skill1");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("skill2");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("skill3");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("skill4");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    // for table interaction
    pInfo = pHandShake->add_schemas();
    if (pInfo == nullptr)
        return GORM_ERROR;
    pInfo->set_version(1);
    pInfo->set_tablename("interaction");
    pInfo->set_tableidx(12);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("version");
    pColumn->set_typedesc("uint64");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_UINT64);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("roleid");
    pColumn->set_typedesc("int64");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT64);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("snakeid");
    pColumn->set_typedesc("int32");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT32);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("interaction1");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("interaction2");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("interaction3");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("interaction4");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    // for table user
    pInfo = pHandShake->add_schemas();
    if (pInfo == nullptr)
        return GORM_ERROR;
    pInfo->set_version(1);
    pInfo->set_tablename("user");
    pInfo->set_tableidx(13);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("version");
    pColumn->set_typedesc("uint64");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_UINT64);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("userid");
    pColumn->set_typedesc("int64");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT64);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("ptid");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("pttype");
    pColumn->set_typedesc("int32");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT32);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("createtime");
    pColumn->set_typedesc("int64");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT64);
    // for table roles
    pInfo = pHandShake->add_schemas();
    if (pInfo == nullptr)
        return GORM_ERROR;
    pInfo->set_version(1);
    pInfo->set_tablename("roles");
    pInfo->set_tableidx(14);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("version");
    pColumn->set_typedesc("uint64");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_UINT64);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("roleid");
    pColumn->set_typedesc("int64");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT64);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("userid");
    pColumn->set_typedesc("int64");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT64);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("worldid");
    pColumn->set_typedesc("int64");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT64);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("dbid");
    pColumn->set_typedesc("int32");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT32);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("name");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("charid");
    pColumn->set_typedesc("int32");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT32);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("face");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("createtime");
    pColumn->set_typedesc("int64");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT64);
    return GORM_OK;
}
uint32 GORM_TableHash(int iTableId, const GORM_PB_TABLE &pbTable)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        if (!pbTable.has_currency())
            return 0;
        const GORM_PB_Table_currency& currency = pbTable.currency();
        int64 tmp_ROLEID = currency.roleid();
        char szSrcHash[1024];
        int iTotalLen = GORM_SafeSnprintf(szSrcHash, 1024, "%lld_" , tmp_ROLEID);
        if (iTotalLen > 1024)
            iTotalLen = 1024;
        return GORM_Hash::Crc32_1((const char*)szSrcHash, iTotalLen);
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        if (!pbTable.has_cycleevent())
            return 0;
        const GORM_PB_Table_cycleevent& cycleevent = pbTable.cycleevent();
        int64 tmp_ROLEID = cycleevent.roleid();
        char szSrcHash[1024];
        int iTotalLen = GORM_SafeSnprintf(szSrcHash, 1024, "%lld_" , tmp_ROLEID);
        if (iTotalLen > 1024)
            iTotalLen = 1024;
        return GORM_Hash::Crc32_1((const char*)szSrcHash, iTotalLen);
    }
    case GORM_PB_TABLE_IDX_EQUIP:
    {
        if (!pbTable.has_equip())
            return 0;
        const GORM_PB_Table_equip& equip = pbTable.equip();
        int64 tmp_ROLEID = equip.roleid();
        char szSrcHash[1024];
        int iTotalLen = GORM_SafeSnprintf(szSrcHash, 1024, "%lld_" , tmp_ROLEID);
        if (iTotalLen > 1024)
            iTotalLen = 1024;
        return GORM_Hash::Crc32_1((const char*)szSrcHash, iTotalLen);
    }
    case GORM_PB_TABLE_IDX_FOOD:
    {
        if (!pbTable.has_food())
            return 0;
        const GORM_PB_Table_food& food = pbTable.food();
        int64 tmp_ROLEID = food.roleid();
        char szSrcHash[1024];
        int iTotalLen = GORM_SafeSnprintf(szSrcHash, 1024, "%lld_" , tmp_ROLEID);
        if (iTotalLen > 1024)
            iTotalLen = 1024;
        return GORM_Hash::Crc32_1((const char*)szSrcHash, iTotalLen);
    }
    case GORM_PB_TABLE_IDX_HERO:
    {
        if (!pbTable.has_hero())
            return 0;
        const GORM_PB_Table_hero& hero = pbTable.hero();
        int64 tmp_ROLEID = hero.roleid();
        char szSrcHash[1024];
        int iTotalLen = GORM_SafeSnprintf(szSrcHash, 1024, "%lld_" , tmp_ROLEID);
        if (iTotalLen > 1024)
            iTotalLen = 1024;
        return GORM_Hash::Crc32_1((const char*)szSrcHash, iTotalLen);
    }
    case GORM_PB_TABLE_IDX_MAIL:
    {
        if (!pbTable.has_mail())
            return 0;
        const GORM_PB_Table_mail& mail = pbTable.mail();
        int64 tmp_ROLEID = mail.roleid();
        char szSrcHash[1024];
        int iTotalLen = GORM_SafeSnprintf(szSrcHash, 1024, "%lld_" , tmp_ROLEID);
        if (iTotalLen > 1024)
            iTotalLen = 1024;
        return GORM_Hash::Crc32_1((const char*)szSrcHash, iTotalLen);
    }
    case GORM_PB_TABLE_IDX_MATERIAL:
    {
        if (!pbTable.has_material())
            return 0;
        const GORM_PB_Table_material& material = pbTable.material();
        int64 tmp_ROLEID = material.roleid();
        char szSrcHash[1024];
        int iTotalLen = GORM_SafeSnprintf(szSrcHash, 1024, "%lld_" , tmp_ROLEID);
        if (iTotalLen > 1024)
            iTotalLen = 1024;
        return GORM_Hash::Crc32_1((const char*)szSrcHash, iTotalLen);
    }
    case GORM_PB_TABLE_IDX_NPC:
    {
        if (!pbTable.has_npc())
            return 0;
        const GORM_PB_Table_npc& npc = pbTable.npc();
        int64 tmp_ROLEID = npc.roleid();
        char szSrcHash[1024];
        int iTotalLen = GORM_SafeSnprintf(szSrcHash, 1024, "%lld_" , tmp_ROLEID);
        if (iTotalLen > 1024)
            iTotalLen = 1024;
        return GORM_Hash::Crc32_1((const char*)szSrcHash, iTotalLen);
    }
    case GORM_PB_TABLE_IDX_ROLE:
    {
        if (!pbTable.has_role())
            return 0;
        const GORM_PB_Table_role& role = pbTable.role();
        int64 tmp_ROLEID = role.roleid();
        char szSrcHash[1024];
        int iTotalLen = GORM_SafeSnprintf(szSrcHash, 1024, "%lld_" , tmp_ROLEID);
        if (iTotalLen > 1024)
            iTotalLen = 1024;
        return GORM_Hash::Crc32_1((const char*)szSrcHash, iTotalLen);
    }
    case GORM_PB_TABLE_IDX_SCENE:
    {
        if (!pbTable.has_scene())
            return 0;
        const GORM_PB_Table_scene& scene = pbTable.scene();
        int64 tmp_ROLEID = scene.roleid();
        char szSrcHash[1024];
        int iTotalLen = GORM_SafeSnprintf(szSrcHash, 1024, "%lld_" , tmp_ROLEID);
        if (iTotalLen > 1024)
            iTotalLen = 1024;
        return GORM_Hash::Crc32_1((const char*)szSrcHash, iTotalLen);
    }
    case GORM_PB_TABLE_IDX_SKILL:
    {
        if (!pbTable.has_skill())
            return 0;
        const GORM_PB_Table_skill& skill = pbTable.skill();
        int64 tmp_ROLEID = skill.roleid();
        char szSrcHash[1024];
        int iTotalLen = GORM_SafeSnprintf(szSrcHash, 1024, "%lld_" , tmp_ROLEID);
        if (iTotalLen > 1024)
            iTotalLen = 1024;
        return GORM_Hash::Crc32_1((const char*)szSrcHash, iTotalLen);
    }
    case GORM_PB_TABLE_IDX_INTERACTION:
    {
        if (!pbTable.has_interaction())
            return 0;
        const GORM_PB_Table_interaction& interaction = pbTable.interaction();
        int64 tmp_ROLEID = interaction.roleid();
        char szSrcHash[1024];
        int iTotalLen = GORM_SafeSnprintf(szSrcHash, 1024, "%lld_" , tmp_ROLEID);
        if (iTotalLen > 1024)
            iTotalLen = 1024;
        return GORM_Hash::Crc32_1((const char*)szSrcHash, iTotalLen);
    }
    case GORM_PB_TABLE_IDX_USER:
    {
        if (!pbTable.has_user())
            return 0;
        const GORM_PB_Table_user& user = pbTable.user();
        int64 tmp_USERID = user.userid();
        char szSrcHash[1024];
        int iTotalLen = GORM_SafeSnprintf(szSrcHash, 1024, "%lld_" , tmp_USERID);
        if (iTotalLen > 1024)
            iTotalLen = 1024;
        return GORM_Hash::Crc32_1((const char*)szSrcHash, iTotalLen);
    }
    case GORM_PB_TABLE_IDX_ROLES:
    {
        if (!pbTable.has_roles())
            return 0;
        const GORM_PB_Table_roles& roles = pbTable.roles();
        int64 tmp_ROLEID = roles.roleid();
        int64 tmp_USERID = roles.userid();
        char szSrcHash[1024];
        int iTotalLen = GORM_SafeSnprintf(szSrcHash, 1024, "%lld_%lld_" , tmp_ROLEID, tmp_USERID);
        if (iTotalLen > 1024)
            iTotalLen = 1024;
        return GORM_Hash::Crc32_1((const char*)szSrcHash, iTotalLen);
    }
    default:
        return 0;
    }
    return 0;
}

int GORM_GetCustomPbMsg(PB_MSG_PTR &pMsgPtr)
{
    pMsgPtr = new GORM_PB_CUSTEM_COLUMNS();
    return GORM_OK;
}
int GetTablePbMsgDefine(int iTableId, PB_MSG_PTR &pMsgPtr)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        pMsgPtr = new GORM_PB_Table_currency();
        return GORM_OK;
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        pMsgPtr = new GORM_PB_Table_cycleevent();
        return GORM_OK;
    }
    case GORM_PB_TABLE_IDX_EQUIP:
    {
        pMsgPtr = new GORM_PB_Table_equip();
        return GORM_OK;
    }
    case GORM_PB_TABLE_IDX_FOOD:
    {
        pMsgPtr = new GORM_PB_Table_food();
        return GORM_OK;
    }
    case GORM_PB_TABLE_IDX_HERO:
    {
        pMsgPtr = new GORM_PB_Table_hero();
        return GORM_OK;
    }
    case GORM_PB_TABLE_IDX_MAIL:
    {
        pMsgPtr = new GORM_PB_Table_mail();
        return GORM_OK;
    }
    case GORM_PB_TABLE_IDX_MATERIAL:
    {
        pMsgPtr = new GORM_PB_Table_material();
        return GORM_OK;
    }
    case GORM_PB_TABLE_IDX_NPC:
    {
        pMsgPtr = new GORM_PB_Table_npc();
        return GORM_OK;
    }
    case GORM_PB_TABLE_IDX_ROLE:
    {
        pMsgPtr = new GORM_PB_Table_role();
        return GORM_OK;
    }
    case GORM_PB_TABLE_IDX_SCENE:
    {
        pMsgPtr = new GORM_PB_Table_scene();
        return GORM_OK;
    }
    case GORM_PB_TABLE_IDX_SKILL:
    {
        pMsgPtr = new GORM_PB_Table_skill();
        return GORM_OK;
    }
    case GORM_PB_TABLE_IDX_INTERACTION:
    {
        pMsgPtr = new GORM_PB_Table_interaction();
        return GORM_OK;
    }
    case GORM_PB_TABLE_IDX_USER:
    {
        pMsgPtr = new GORM_PB_Table_user();
        return GORM_OK;
    }
    case GORM_PB_TABLE_IDX_ROLES:
    {
        pMsgPtr = new GORM_PB_Table_roles();
        return GORM_OK;
    }
    }
    return GORM_INVALID_TABLE;
}
bool GORM_TableHasData(GORM_PB_TABLE *pTable, int iTableId)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
        return pTable->has_currency();
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
        return pTable->has_cycleevent();
    case GORM_PB_TABLE_IDX_EQUIP:
        return pTable->has_equip();
    case GORM_PB_TABLE_IDX_FOOD:
        return pTable->has_food();
    case GORM_PB_TABLE_IDX_HERO:
        return pTable->has_hero();
    case GORM_PB_TABLE_IDX_MAIL:
        return pTable->has_mail();
    case GORM_PB_TABLE_IDX_MATERIAL:
        return pTable->has_material();
    case GORM_PB_TABLE_IDX_NPC:
        return pTable->has_npc();
    case GORM_PB_TABLE_IDX_ROLE:
        return pTable->has_role();
    case GORM_PB_TABLE_IDX_SCENE:
        return pTable->has_scene();
    case GORM_PB_TABLE_IDX_SKILL:
        return pTable->has_skill();
    case GORM_PB_TABLE_IDX_INTERACTION:
        return pTable->has_interaction();
    case GORM_PB_TABLE_IDX_USER:
        return pTable->has_user();
    case GORM_PB_TABLE_IDX_ROLES:
        return pTable->has_roles();
    }

    return false;
}
int GORM_GetTableSrcPbMsg(int iTableId, GORM_PB_TABLE *pTable, PB_MSG_PTR &pMsgPtr)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        pMsgPtr = pTable->mutable_currency();
        return GORM_OK;
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        pMsgPtr = pTable->mutable_cycleevent();
        return GORM_OK;
    }
    case GORM_PB_TABLE_IDX_EQUIP:
    {
        pMsgPtr = pTable->mutable_equip();
        return GORM_OK;
    }
    case GORM_PB_TABLE_IDX_FOOD:
    {
        pMsgPtr = pTable->mutable_food();
        return GORM_OK;
    }
    case GORM_PB_TABLE_IDX_HERO:
    {
        pMsgPtr = pTable->mutable_hero();
        return GORM_OK;
    }
    case GORM_PB_TABLE_IDX_MAIL:
    {
        pMsgPtr = pTable->mutable_mail();
        return GORM_OK;
    }
    case GORM_PB_TABLE_IDX_MATERIAL:
    {
        pMsgPtr = pTable->mutable_material();
        return GORM_OK;
    }
    case GORM_PB_TABLE_IDX_NPC:
    {
        pMsgPtr = pTable->mutable_npc();
        return GORM_OK;
    }
    case GORM_PB_TABLE_IDX_ROLE:
    {
        pMsgPtr = pTable->mutable_role();
        return GORM_OK;
    }
    case GORM_PB_TABLE_IDX_SCENE:
    {
        pMsgPtr = pTable->mutable_scene();
        return GORM_OK;
    }
    case GORM_PB_TABLE_IDX_SKILL:
    {
        pMsgPtr = pTable->mutable_skill();
        return GORM_OK;
    }
    case GORM_PB_TABLE_IDX_INTERACTION:
    {
        pMsgPtr = pTable->mutable_interaction();
        return GORM_OK;
    }
    case GORM_PB_TABLE_IDX_USER:
    {
        pMsgPtr = pTable->mutable_user();
        return GORM_OK;
    }
    case GORM_PB_TABLE_IDX_ROLES:
    {
        pMsgPtr = pTable->mutable_roles();
        return GORM_OK;
    }
    }

    return false;
}
int GORM_AddRecordToReqPbMsgDefine(int iTableId, GORM_PB_TABLE *pPbTable, PB_MSG_PTR pPbMsg)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        GORM_PB_Table_currency *pTableMsg = dynamic_cast<GORM_PB_Table_currency*>(pPbMsg);
        pPbTable->set_allocated_currency(pTableMsg);
        return GORM_OK;
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        GORM_PB_Table_cycleevent *pTableMsg = dynamic_cast<GORM_PB_Table_cycleevent*>(pPbMsg);
        pPbTable->set_allocated_cycleevent(pTableMsg);
        return GORM_OK;
    }
    case GORM_PB_TABLE_IDX_EQUIP:
    {
        GORM_PB_Table_equip *pTableMsg = dynamic_cast<GORM_PB_Table_equip*>(pPbMsg);
        pPbTable->set_allocated_equip(pTableMsg);
        return GORM_OK;
    }
    case GORM_PB_TABLE_IDX_FOOD:
    {
        GORM_PB_Table_food *pTableMsg = dynamic_cast<GORM_PB_Table_food*>(pPbMsg);
        pPbTable->set_allocated_food(pTableMsg);
        return GORM_OK;
    }
    case GORM_PB_TABLE_IDX_HERO:
    {
        GORM_PB_Table_hero *pTableMsg = dynamic_cast<GORM_PB_Table_hero*>(pPbMsg);
        pPbTable->set_allocated_hero(pTableMsg);
        return GORM_OK;
    }
    case GORM_PB_TABLE_IDX_MAIL:
    {
        GORM_PB_Table_mail *pTableMsg = dynamic_cast<GORM_PB_Table_mail*>(pPbMsg);
        pPbTable->set_allocated_mail(pTableMsg);
        return GORM_OK;
    }
    case GORM_PB_TABLE_IDX_MATERIAL:
    {
        GORM_PB_Table_material *pTableMsg = dynamic_cast<GORM_PB_Table_material*>(pPbMsg);
        pPbTable->set_allocated_material(pTableMsg);
        return GORM_OK;
    }
    case GORM_PB_TABLE_IDX_NPC:
    {
        GORM_PB_Table_npc *pTableMsg = dynamic_cast<GORM_PB_Table_npc*>(pPbMsg);
        pPbTable->set_allocated_npc(pTableMsg);
        return GORM_OK;
    }
    case GORM_PB_TABLE_IDX_ROLE:
    {
        GORM_PB_Table_role *pTableMsg = dynamic_cast<GORM_PB_Table_role*>(pPbMsg);
        pPbTable->set_allocated_role(pTableMsg);
        return GORM_OK;
    }
    case GORM_PB_TABLE_IDX_SCENE:
    {
        GORM_PB_Table_scene *pTableMsg = dynamic_cast<GORM_PB_Table_scene*>(pPbMsg);
        pPbTable->set_allocated_scene(pTableMsg);
        return GORM_OK;
    }
    case GORM_PB_TABLE_IDX_SKILL:
    {
        GORM_PB_Table_skill *pTableMsg = dynamic_cast<GORM_PB_Table_skill*>(pPbMsg);
        pPbTable->set_allocated_skill(pTableMsg);
        return GORM_OK;
    }
    case GORM_PB_TABLE_IDX_INTERACTION:
    {
        GORM_PB_Table_interaction *pTableMsg = dynamic_cast<GORM_PB_Table_interaction*>(pPbMsg);
        pPbTable->set_allocated_interaction(pTableMsg);
        return GORM_OK;
    }
    case GORM_PB_TABLE_IDX_USER:
    {
        GORM_PB_Table_user *pTableMsg = dynamic_cast<GORM_PB_Table_user*>(pPbMsg);
        pPbTable->set_allocated_user(pTableMsg);
        return GORM_OK;
    }
    case GORM_PB_TABLE_IDX_ROLES:
    {
        GORM_PB_Table_roles *pTableMsg = dynamic_cast<GORM_PB_Table_roles*>(pPbMsg);
        pPbTable->set_allocated_roles(pTableMsg);
        return GORM_OK;
    }
    }
    return GORM_INVALID_TABLE;
}
int GORM_SetTableVersion(OUT TableVersionMap& mapTableVersion)
{
    mapTableVersion[GORM_PB_TABLE_IDX_CURRENCY] = 1;
    mapTableVersion[GORM_PB_TABLE_IDX_CYCLEEVENT] = 1;
    mapTableVersion[GORM_PB_TABLE_IDX_EQUIP] = 1;
    mapTableVersion[GORM_PB_TABLE_IDX_FOOD] = 1;
    mapTableVersion[GORM_PB_TABLE_IDX_HERO] = 1;
    mapTableVersion[GORM_PB_TABLE_IDX_MAIL] = 1;
    mapTableVersion[GORM_PB_TABLE_IDX_MATERIAL] = 1;
    mapTableVersion[GORM_PB_TABLE_IDX_NPC] = 1;
    mapTableVersion[GORM_PB_TABLE_IDX_ROLE] = 1;
    mapTableVersion[GORM_PB_TABLE_IDX_SCENE] = 1;
    mapTableVersion[GORM_PB_TABLE_IDX_SKILL] = 1;
    mapTableVersion[GORM_PB_TABLE_IDX_INTERACTION] = 1;
    mapTableVersion[GORM_PB_TABLE_IDX_USER] = 1;
    mapTableVersion[GORM_PB_TABLE_IDX_ROLES] = 1;
    return GORM_OK;
}

int GORM_SetTableName2Id(OUT TableName2Id &mapName2Id)
{
    mapName2Id["currency"] = GORM_PB_TABLE_IDX_CURRENCY;
    mapName2Id["cycleevent"] = GORM_PB_TABLE_IDX_CYCLEEVENT;
    mapName2Id["equip"] = GORM_PB_TABLE_IDX_EQUIP;
    mapName2Id["food"] = GORM_PB_TABLE_IDX_FOOD;
    mapName2Id["hero"] = GORM_PB_TABLE_IDX_HERO;
    mapName2Id["mail"] = GORM_PB_TABLE_IDX_MAIL;
    mapName2Id["material"] = GORM_PB_TABLE_IDX_MATERIAL;
    mapName2Id["npc"] = GORM_PB_TABLE_IDX_NPC;
    mapName2Id["role"] = GORM_PB_TABLE_IDX_ROLE;
    mapName2Id["scene"] = GORM_PB_TABLE_IDX_SCENE;
    mapName2Id["skill"] = GORM_PB_TABLE_IDX_SKILL;
    mapName2Id["interaction"] = GORM_PB_TABLE_IDX_INTERACTION;
    mapName2Id["user"] = GORM_PB_TABLE_IDX_USER;
    mapName2Id["roles"] = GORM_PB_TABLE_IDX_ROLES;
    return GORM_OK;
}

int GORM_SetTableId2Name(OUT TableId2Name &mapId2Name)
{
    mapId2Name[GORM_PB_TABLE_IDX_CURRENCY] = "currency";
    mapId2Name[GORM_PB_TABLE_IDX_CYCLEEVENT] = "cycleevent";
    mapId2Name[GORM_PB_TABLE_IDX_EQUIP] = "equip";
    mapId2Name[GORM_PB_TABLE_IDX_FOOD] = "food";
    mapId2Name[GORM_PB_TABLE_IDX_HERO] = "hero";
    mapId2Name[GORM_PB_TABLE_IDX_MAIL] = "mail";
    mapId2Name[GORM_PB_TABLE_IDX_MATERIAL] = "material";
    mapId2Name[GORM_PB_TABLE_IDX_NPC] = "npc";
    mapId2Name[GORM_PB_TABLE_IDX_ROLE] = "role";
    mapId2Name[GORM_PB_TABLE_IDX_SCENE] = "scene";
    mapId2Name[GORM_PB_TABLE_IDX_SKILL] = "skill";
    mapId2Name[GORM_PB_TABLE_IDX_INTERACTION] = "interaction";
    mapId2Name[GORM_PB_TABLE_IDX_USER] = "user";
    mapId2Name[GORM_PB_TABLE_IDX_ROLES] = "roles";
    return GORM_OK;
}

int GORM_SetTableFieldId2Name(int iTableType, OUT FieldId2Name &mapId2Name)
{
    switch (iTableType)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        return GORM_SetTableCURRENCYId2Name(mapId2Name);
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        return GORM_SetTableCYCLEEVENTId2Name(mapId2Name);
    }
    case GORM_PB_TABLE_IDX_EQUIP:
    {
        return GORM_SetTableEQUIPId2Name(mapId2Name);
    }
    case GORM_PB_TABLE_IDX_FOOD:
    {
        return GORM_SetTableFOODId2Name(mapId2Name);
    }
    case GORM_PB_TABLE_IDX_HERO:
    {
        return GORM_SetTableHEROId2Name(mapId2Name);
    }
    case GORM_PB_TABLE_IDX_MAIL:
    {
        return GORM_SetTableMAILId2Name(mapId2Name);
    }
    case GORM_PB_TABLE_IDX_MATERIAL:
    {
        return GORM_SetTableMATERIALId2Name(mapId2Name);
    }
    case GORM_PB_TABLE_IDX_NPC:
    {
        return GORM_SetTableNPCId2Name(mapId2Name);
    }
    case GORM_PB_TABLE_IDX_ROLE:
    {
        return GORM_SetTableROLEId2Name(mapId2Name);
    }
    case GORM_PB_TABLE_IDX_SCENE:
    {
        return GORM_SetTableSCENEId2Name(mapId2Name);
    }
    case GORM_PB_TABLE_IDX_SKILL:
    {
        return GORM_SetTableSKILLId2Name(mapId2Name);
    }
    case GORM_PB_TABLE_IDX_INTERACTION:
    {
        return GORM_SetTableINTERACTIONId2Name(mapId2Name);
    }
    case GORM_PB_TABLE_IDX_USER:
    {
        return GORM_SetTableUSERId2Name(mapId2Name);
    }
    case GORM_PB_TABLE_IDX_ROLES:
    {
        return GORM_SetTableROLESId2Name(mapId2Name);
    }
    default:
        return GORM_ERROR;
    }

    return GORM_OK;
}
int GORM_SetTableFieldName2Id(int iTableType, OUT FieldName2Id &mapName2Id)
{
    switch (iTableType)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        return GORM_SetTableCURRENCYName2Id(mapName2Id);
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        return GORM_SetTableCYCLEEVENTName2Id(mapName2Id);
    }
    case GORM_PB_TABLE_IDX_EQUIP:
    {
        return GORM_SetTableEQUIPName2Id(mapName2Id);
    }
    case GORM_PB_TABLE_IDX_FOOD:
    {
        return GORM_SetTableFOODName2Id(mapName2Id);
    }
    case GORM_PB_TABLE_IDX_HERO:
    {
        return GORM_SetTableHEROName2Id(mapName2Id);
    }
    case GORM_PB_TABLE_IDX_MAIL:
    {
        return GORM_SetTableMAILName2Id(mapName2Id);
    }
    case GORM_PB_TABLE_IDX_MATERIAL:
    {
        return GORM_SetTableMATERIALName2Id(mapName2Id);
    }
    case GORM_PB_TABLE_IDX_NPC:
    {
        return GORM_SetTableNPCName2Id(mapName2Id);
    }
    case GORM_PB_TABLE_IDX_ROLE:
    {
        return GORM_SetTableROLEName2Id(mapName2Id);
    }
    case GORM_PB_TABLE_IDX_SCENE:
    {
        return GORM_SetTableSCENEName2Id(mapName2Id);
    }
    case GORM_PB_TABLE_IDX_SKILL:
    {
        return GORM_SetTableSKILLName2Id(mapName2Id);
    }
    case GORM_PB_TABLE_IDX_INTERACTION:
    {
        return GORM_SetTableINTERACTIONName2Id(mapName2Id);
    }
    case GORM_PB_TABLE_IDX_USER:
    {
        return GORM_SetTableUSERName2Id(mapName2Id);
    }
    case GORM_PB_TABLE_IDX_ROLES:
    {
        return GORM_SetTableROLESName2Id(mapName2Id);
    }
    default:
        return GORM_ERROR;
    }

    return GORM_OK;
}
int GORM_SetTableCURRENCYId2Name(OUT FieldId2Name &mapId2Name)
{
    mapId2Name[GORM_PB_FIELD_CURRENCY_VERSION] = "version";
    mapId2Name[GORM_PB_FIELD_CURRENCY_ROLEID] = "roleid";
    mapId2Name[GORM_PB_FIELD_CURRENCY_SNAKEID] = "snakeid";
    mapId2Name[GORM_PB_FIELD_CURRENCY_CURRENCY1] = "currency1";
    mapId2Name[GORM_PB_FIELD_CURRENCY_CURRENCY2] = "currency2";
    mapId2Name[GORM_PB_FIELD_CURRENCY_CURRENCY3] = "currency3";
    mapId2Name[GORM_PB_FIELD_CURRENCY_CURRENCY4] = "currency4";
    return GORM_OK;
}
int GORM_SetTableCYCLEEVENTId2Name(OUT FieldId2Name &mapId2Name)
{
    mapId2Name[GORM_PB_FIELD_CYCLEEVENT_VERSION] = "version";
    mapId2Name[GORM_PB_FIELD_CYCLEEVENT_ROLEID] = "roleid";
    mapId2Name[GORM_PB_FIELD_CYCLEEVENT_EVENTS] = "events";
    return GORM_OK;
}
int GORM_SetTableEQUIPId2Name(OUT FieldId2Name &mapId2Name)
{
    mapId2Name[GORM_PB_FIELD_EQUIP_VERSION] = "version";
    mapId2Name[GORM_PB_FIELD_EQUIP_ROLEID] = "roleid";
    mapId2Name[GORM_PB_FIELD_EQUIP_SNAKEID] = "snakeid";
    mapId2Name[GORM_PB_FIELD_EQUIP_EQUIP1] = "equip1";
    mapId2Name[GORM_PB_FIELD_EQUIP_EQUIP2] = "equip2";
    mapId2Name[GORM_PB_FIELD_EQUIP_EQUIP3] = "equip3";
    mapId2Name[GORM_PB_FIELD_EQUIP_EQUIP4] = "equip4";
    return GORM_OK;
}
int GORM_SetTableFOODId2Name(OUT FieldId2Name &mapId2Name)
{
    mapId2Name[GORM_PB_FIELD_FOOD_VERSION] = "version";
    mapId2Name[GORM_PB_FIELD_FOOD_ROLEID] = "roleid";
    mapId2Name[GORM_PB_FIELD_FOOD_SNAKEID] = "snakeid";
    mapId2Name[GORM_PB_FIELD_FOOD_FOOD1] = "food1";
    mapId2Name[GORM_PB_FIELD_FOOD_FOOD2] = "food2";
    mapId2Name[GORM_PB_FIELD_FOOD_FOOD3] = "food3";
    mapId2Name[GORM_PB_FIELD_FOOD_FOOD4] = "food4";
    return GORM_OK;
}
int GORM_SetTableHEROId2Name(OUT FieldId2Name &mapId2Name)
{
    mapId2Name[GORM_PB_FIELD_HERO_VERSION] = "version";
    mapId2Name[GORM_PB_FIELD_HERO_ROLEID] = "roleid";
    mapId2Name[GORM_PB_FIELD_HERO_SNAKEID] = "snakeid";
    mapId2Name[GORM_PB_FIELD_HERO_HEROS] = "heros";
    return GORM_OK;
}
int GORM_SetTableMAILId2Name(OUT FieldId2Name &mapId2Name)
{
    mapId2Name[GORM_PB_FIELD_MAIL_VERSION] = "version";
    mapId2Name[GORM_PB_FIELD_MAIL_ROLEID] = "roleid";
    mapId2Name[GORM_PB_FIELD_MAIL_MAIL1] = "mail1";
    mapId2Name[GORM_PB_FIELD_MAIL_MAIL2] = "mail2";
    mapId2Name[GORM_PB_FIELD_MAIL_MAIL3] = "mail3";
    mapId2Name[GORM_PB_FIELD_MAIL_MAIL4] = "mail4";
    mapId2Name[GORM_PB_FIELD_MAIL_MAIL5] = "mail5";
    mapId2Name[GORM_PB_FIELD_MAIL_LASTMAILID] = "lastmailid";
    mapId2Name[GORM_PB_FIELD_MAIL_SNAKEID] = "snakeid";
    return GORM_OK;
}
int GORM_SetTableMATERIALId2Name(OUT FieldId2Name &mapId2Name)
{
    mapId2Name[GORM_PB_FIELD_MATERIAL_VERSION] = "version";
    mapId2Name[GORM_PB_FIELD_MATERIAL_ROLEID] = "roleid";
    mapId2Name[GORM_PB_FIELD_MATERIAL_SNAKEID] = "snakeid";
    mapId2Name[GORM_PB_FIELD_MATERIAL_MATERIAL1] = "material1";
    mapId2Name[GORM_PB_FIELD_MATERIAL_MATERIAL2] = "material2";
    mapId2Name[GORM_PB_FIELD_MATERIAL_MATERIAL3] = "material3";
    mapId2Name[GORM_PB_FIELD_MATERIAL_MATERIAL4] = "material4";
    return GORM_OK;
}
int GORM_SetTableNPCId2Name(OUT FieldId2Name &mapId2Name)
{
    mapId2Name[GORM_PB_FIELD_NPC_VERSION] = "version";
    mapId2Name[GORM_PB_FIELD_NPC_ROLEID] = "roleid";
    mapId2Name[GORM_PB_FIELD_NPC_SNAKEID] = "snakeid";
    mapId2Name[GORM_PB_FIELD_NPC_NPCS] = "npcs";
    return GORM_OK;
}
int GORM_SetTableROLEId2Name(OUT FieldId2Name &mapId2Name)
{
    mapId2Name[GORM_PB_FIELD_ROLE_VERSION] = "version";
    mapId2Name[GORM_PB_FIELD_ROLE_ROLEID] = "roleid";
    mapId2Name[GORM_PB_FIELD_ROLE_ROLENAME] = "rolename";
    mapId2Name[GORM_PB_FIELD_ROLE_LEVEL] = "level";
    mapId2Name[GORM_PB_FIELD_ROLE_EXP] = "exp";
    mapId2Name[GORM_PB_FIELD_ROLE_CHARACTERID] = "characterid";
    mapId2Name[GORM_PB_FIELD_ROLE_GOLD] = "gold";
    mapId2Name[GORM_PB_FIELD_ROLE_OFFLINETIME] = "offlinetime";
    mapId2Name[GORM_PB_FIELD_ROLE_INITED] = "inited";
    mapId2Name[GORM_PB_FIELD_ROLE_CREATETIME] = "createtime";
    mapId2Name[GORM_PB_FIELD_ROLE_FACE] = "face";
    mapId2Name[GORM_PB_FIELD_ROLE_ONLINE] = "online";
    return GORM_OK;
}
int GORM_SetTableSCENEId2Name(OUT FieldId2Name &mapId2Name)
{
    mapId2Name[GORM_PB_FIELD_SCENE_VERSION] = "version";
    mapId2Name[GORM_PB_FIELD_SCENE_ROLEID] = "roleid";
    mapId2Name[GORM_PB_FIELD_SCENE_SCENEID] = "sceneid";
    mapId2Name[GORM_PB_FIELD_SCENE_COLLECTS] = "collects";
    return GORM_OK;
}
int GORM_SetTableSKILLId2Name(OUT FieldId2Name &mapId2Name)
{
    mapId2Name[GORM_PB_FIELD_SKILL_VERSION] = "version";
    mapId2Name[GORM_PB_FIELD_SKILL_ROLEID] = "roleid";
    mapId2Name[GORM_PB_FIELD_SKILL_SNAKEID] = "snakeid";
    mapId2Name[GORM_PB_FIELD_SKILL_SKILL1] = "skill1";
    mapId2Name[GORM_PB_FIELD_SKILL_SKILL2] = "skill2";
    mapId2Name[GORM_PB_FIELD_SKILL_SKILL3] = "skill3";
    mapId2Name[GORM_PB_FIELD_SKILL_SKILL4] = "skill4";
    return GORM_OK;
}
int GORM_SetTableINTERACTIONId2Name(OUT FieldId2Name &mapId2Name)
{
    mapId2Name[GORM_PB_FIELD_INTERACTION_VERSION] = "version";
    mapId2Name[GORM_PB_FIELD_INTERACTION_ROLEID] = "roleid";
    mapId2Name[GORM_PB_FIELD_INTERACTION_SNAKEID] = "snakeid";
    mapId2Name[GORM_PB_FIELD_INTERACTION_INTERACTION1] = "interaction1";
    mapId2Name[GORM_PB_FIELD_INTERACTION_INTERACTION2] = "interaction2";
    mapId2Name[GORM_PB_FIELD_INTERACTION_INTERACTION3] = "interaction3";
    mapId2Name[GORM_PB_FIELD_INTERACTION_INTERACTION4] = "interaction4";
    return GORM_OK;
}
int GORM_SetTableUSERId2Name(OUT FieldId2Name &mapId2Name)
{
    mapId2Name[GORM_PB_FIELD_USER_VERSION] = "version";
    mapId2Name[GORM_PB_FIELD_USER_USERID] = "userid";
    mapId2Name[GORM_PB_FIELD_USER_PTID] = "ptid";
    mapId2Name[GORM_PB_FIELD_USER_PTTYPE] = "pttype";
    mapId2Name[GORM_PB_FIELD_USER_CREATETIME] = "createtime";
    return GORM_OK;
}
int GORM_SetTableROLESId2Name(OUT FieldId2Name &mapId2Name)
{
    mapId2Name[GORM_PB_FIELD_ROLES_VERSION] = "version";
    mapId2Name[GORM_PB_FIELD_ROLES_ROLEID] = "roleid";
    mapId2Name[GORM_PB_FIELD_ROLES_USERID] = "userid";
    mapId2Name[GORM_PB_FIELD_ROLES_WORLDID] = "worldid";
    mapId2Name[GORM_PB_FIELD_ROLES_DBID] = "dbid";
    mapId2Name[GORM_PB_FIELD_ROLES_NAME] = "name";
    mapId2Name[GORM_PB_FIELD_ROLES_CHARID] = "charid";
    mapId2Name[GORM_PB_FIELD_ROLES_FACE] = "face";
    mapId2Name[GORM_PB_FIELD_ROLES_CREATETIME] = "createtime";
    return GORM_OK;
}
int GORM_SetTableCURRENCYName2Id(OUT FieldName2Id &mapName2Id)
{
    mapName2Id["version"] = GORM_PB_FIELD_CURRENCY_VERSION;
    mapName2Id["roleid"] = GORM_PB_FIELD_CURRENCY_ROLEID;
    mapName2Id["snakeid"] = GORM_PB_FIELD_CURRENCY_SNAKEID;
    mapName2Id["currency1"] = GORM_PB_FIELD_CURRENCY_CURRENCY1;
    mapName2Id["currency2"] = GORM_PB_FIELD_CURRENCY_CURRENCY2;
    mapName2Id["currency3"] = GORM_PB_FIELD_CURRENCY_CURRENCY3;
    mapName2Id["currency4"] = GORM_PB_FIELD_CURRENCY_CURRENCY4;
    return GORM_OK;
}
int GORM_SetTableCYCLEEVENTName2Id(OUT FieldName2Id &mapName2Id)
{
    mapName2Id["version"] = GORM_PB_FIELD_CYCLEEVENT_VERSION;
    mapName2Id["roleid"] = GORM_PB_FIELD_CYCLEEVENT_ROLEID;
    mapName2Id["events"] = GORM_PB_FIELD_CYCLEEVENT_EVENTS;
    return GORM_OK;
}
int GORM_SetTableEQUIPName2Id(OUT FieldName2Id &mapName2Id)
{
    mapName2Id["version"] = GORM_PB_FIELD_EQUIP_VERSION;
    mapName2Id["roleid"] = GORM_PB_FIELD_EQUIP_ROLEID;
    mapName2Id["snakeid"] = GORM_PB_FIELD_EQUIP_SNAKEID;
    mapName2Id["equip1"] = GORM_PB_FIELD_EQUIP_EQUIP1;
    mapName2Id["equip2"] = GORM_PB_FIELD_EQUIP_EQUIP2;
    mapName2Id["equip3"] = GORM_PB_FIELD_EQUIP_EQUIP3;
    mapName2Id["equip4"] = GORM_PB_FIELD_EQUIP_EQUIP4;
    return GORM_OK;
}
int GORM_SetTableFOODName2Id(OUT FieldName2Id &mapName2Id)
{
    mapName2Id["version"] = GORM_PB_FIELD_FOOD_VERSION;
    mapName2Id["roleid"] = GORM_PB_FIELD_FOOD_ROLEID;
    mapName2Id["snakeid"] = GORM_PB_FIELD_FOOD_SNAKEID;
    mapName2Id["food1"] = GORM_PB_FIELD_FOOD_FOOD1;
    mapName2Id["food2"] = GORM_PB_FIELD_FOOD_FOOD2;
    mapName2Id["food3"] = GORM_PB_FIELD_FOOD_FOOD3;
    mapName2Id["food4"] = GORM_PB_FIELD_FOOD_FOOD4;
    return GORM_OK;
}
int GORM_SetTableHEROName2Id(OUT FieldName2Id &mapName2Id)
{
    mapName2Id["version"] = GORM_PB_FIELD_HERO_VERSION;
    mapName2Id["roleid"] = GORM_PB_FIELD_HERO_ROLEID;
    mapName2Id["snakeid"] = GORM_PB_FIELD_HERO_SNAKEID;
    mapName2Id["heros"] = GORM_PB_FIELD_HERO_HEROS;
    return GORM_OK;
}
int GORM_SetTableMAILName2Id(OUT FieldName2Id &mapName2Id)
{
    mapName2Id["version"] = GORM_PB_FIELD_MAIL_VERSION;
    mapName2Id["roleid"] = GORM_PB_FIELD_MAIL_ROLEID;
    mapName2Id["mail1"] = GORM_PB_FIELD_MAIL_MAIL1;
    mapName2Id["mail2"] = GORM_PB_FIELD_MAIL_MAIL2;
    mapName2Id["mail3"] = GORM_PB_FIELD_MAIL_MAIL3;
    mapName2Id["mail4"] = GORM_PB_FIELD_MAIL_MAIL4;
    mapName2Id["mail5"] = GORM_PB_FIELD_MAIL_MAIL5;
    mapName2Id["lastmailid"] = GORM_PB_FIELD_MAIL_LASTMAILID;
    mapName2Id["snakeid"] = GORM_PB_FIELD_MAIL_SNAKEID;
    return GORM_OK;
}
int GORM_SetTableMATERIALName2Id(OUT FieldName2Id &mapName2Id)
{
    mapName2Id["version"] = GORM_PB_FIELD_MATERIAL_VERSION;
    mapName2Id["roleid"] = GORM_PB_FIELD_MATERIAL_ROLEID;
    mapName2Id["snakeid"] = GORM_PB_FIELD_MATERIAL_SNAKEID;
    mapName2Id["material1"] = GORM_PB_FIELD_MATERIAL_MATERIAL1;
    mapName2Id["material2"] = GORM_PB_FIELD_MATERIAL_MATERIAL2;
    mapName2Id["material3"] = GORM_PB_FIELD_MATERIAL_MATERIAL3;
    mapName2Id["material4"] = GORM_PB_FIELD_MATERIAL_MATERIAL4;
    return GORM_OK;
}
int GORM_SetTableNPCName2Id(OUT FieldName2Id &mapName2Id)
{
    mapName2Id["version"] = GORM_PB_FIELD_NPC_VERSION;
    mapName2Id["roleid"] = GORM_PB_FIELD_NPC_ROLEID;
    mapName2Id["snakeid"] = GORM_PB_FIELD_NPC_SNAKEID;
    mapName2Id["npcs"] = GORM_PB_FIELD_NPC_NPCS;
    return GORM_OK;
}
int GORM_SetTableROLEName2Id(OUT FieldName2Id &mapName2Id)
{
    mapName2Id["version"] = GORM_PB_FIELD_ROLE_VERSION;
    mapName2Id["roleid"] = GORM_PB_FIELD_ROLE_ROLEID;
    mapName2Id["rolename"] = GORM_PB_FIELD_ROLE_ROLENAME;
    mapName2Id["level"] = GORM_PB_FIELD_ROLE_LEVEL;
    mapName2Id["exp"] = GORM_PB_FIELD_ROLE_EXP;
    mapName2Id["characterid"] = GORM_PB_FIELD_ROLE_CHARACTERID;
    mapName2Id["gold"] = GORM_PB_FIELD_ROLE_GOLD;
    mapName2Id["offlinetime"] = GORM_PB_FIELD_ROLE_OFFLINETIME;
    mapName2Id["inited"] = GORM_PB_FIELD_ROLE_INITED;
    mapName2Id["createtime"] = GORM_PB_FIELD_ROLE_CREATETIME;
    mapName2Id["face"] = GORM_PB_FIELD_ROLE_FACE;
    mapName2Id["online"] = GORM_PB_FIELD_ROLE_ONLINE;
    return GORM_OK;
}
int GORM_SetTableSCENEName2Id(OUT FieldName2Id &mapName2Id)
{
    mapName2Id["version"] = GORM_PB_FIELD_SCENE_VERSION;
    mapName2Id["roleid"] = GORM_PB_FIELD_SCENE_ROLEID;
    mapName2Id["sceneid"] = GORM_PB_FIELD_SCENE_SCENEID;
    mapName2Id["collects"] = GORM_PB_FIELD_SCENE_COLLECTS;
    return GORM_OK;
}
int GORM_SetTableSKILLName2Id(OUT FieldName2Id &mapName2Id)
{
    mapName2Id["version"] = GORM_PB_FIELD_SKILL_VERSION;
    mapName2Id["roleid"] = GORM_PB_FIELD_SKILL_ROLEID;
    mapName2Id["snakeid"] = GORM_PB_FIELD_SKILL_SNAKEID;
    mapName2Id["skill1"] = GORM_PB_FIELD_SKILL_SKILL1;
    mapName2Id["skill2"] = GORM_PB_FIELD_SKILL_SKILL2;
    mapName2Id["skill3"] = GORM_PB_FIELD_SKILL_SKILL3;
    mapName2Id["skill4"] = GORM_PB_FIELD_SKILL_SKILL4;
    return GORM_OK;
}
int GORM_SetTableINTERACTIONName2Id(OUT FieldName2Id &mapName2Id)
{
    mapName2Id["version"] = GORM_PB_FIELD_INTERACTION_VERSION;
    mapName2Id["roleid"] = GORM_PB_FIELD_INTERACTION_ROLEID;
    mapName2Id["snakeid"] = GORM_PB_FIELD_INTERACTION_SNAKEID;
    mapName2Id["interaction1"] = GORM_PB_FIELD_INTERACTION_INTERACTION1;
    mapName2Id["interaction2"] = GORM_PB_FIELD_INTERACTION_INTERACTION2;
    mapName2Id["interaction3"] = GORM_PB_FIELD_INTERACTION_INTERACTION3;
    mapName2Id["interaction4"] = GORM_PB_FIELD_INTERACTION_INTERACTION4;
    return GORM_OK;
}
int GORM_SetTableUSERName2Id(OUT FieldName2Id &mapName2Id)
{
    mapName2Id["version"] = GORM_PB_FIELD_USER_VERSION;
    mapName2Id["userid"] = GORM_PB_FIELD_USER_USERID;
    mapName2Id["ptid"] = GORM_PB_FIELD_USER_PTID;
    mapName2Id["pttype"] = GORM_PB_FIELD_USER_PTTYPE;
    mapName2Id["createtime"] = GORM_PB_FIELD_USER_CREATETIME;
    return GORM_OK;
}
int GORM_SetTableROLESName2Id(OUT FieldName2Id &mapName2Id)
{
    mapName2Id["version"] = GORM_PB_FIELD_ROLES_VERSION;
    mapName2Id["roleid"] = GORM_PB_FIELD_ROLES_ROLEID;
    mapName2Id["userid"] = GORM_PB_FIELD_ROLES_USERID;
    mapName2Id["worldid"] = GORM_PB_FIELD_ROLES_WORLDID;
    mapName2Id["dbid"] = GORM_PB_FIELD_ROLES_DBID;
    mapName2Id["name"] = GORM_PB_FIELD_ROLES_NAME;
    mapName2Id["charid"] = GORM_PB_FIELD_ROLES_CHARID;
    mapName2Id["face"] = GORM_PB_FIELD_ROLES_FACE;
    mapName2Id["createtime"] = GORM_PB_FIELD_ROLES_CREATETIME;
    return GORM_OK;
}
int GORM_InitTableColumnInfo_currency(unordered_map<string, vector<string>> &mapTablesColumnOrder, unordered_map<string, unordered_map<string, GORM_PB_COLUMN_TYPE>> &mapTablesColumnInfo)
{
    vector<string> vColumns = {"version","roleid","snakeid","currency1","currency2","currency3","currency4"};
    mapTablesColumnOrder["currency"] = vColumns;
    unordered_map<string, GORM_PB_COLUMN_TYPE> mapColumnType = {
        {"version", GORM_PB_COLUMN_TYPE_UINT},
        {"roleid", GORM_PB_COLUMN_TYPE_INT},
        {"snakeid", GORM_PB_COLUMN_TYPE_INT},
        {"currency1", GORM_PB_COLUMN_TYPE_STRING},
        {"currency2", GORM_PB_COLUMN_TYPE_STRING},
        {"currency3", GORM_PB_COLUMN_TYPE_STRING},
        {"currency4", GORM_PB_COLUMN_TYPE_STRING},
    };
    mapTablesColumnInfo["currency"] = mapColumnType;
    return GORM_OK;
}
int GORM_InitTableColumnInfo_cycleevent(unordered_map<string, vector<string>> &mapTablesColumnOrder, unordered_map<string, unordered_map<string, GORM_PB_COLUMN_TYPE>> &mapTablesColumnInfo)
{
    vector<string> vColumns = {"version","roleid","events"};
    mapTablesColumnOrder["cycleevent"] = vColumns;
    unordered_map<string, GORM_PB_COLUMN_TYPE> mapColumnType = {
        {"version", GORM_PB_COLUMN_TYPE_UINT},
        {"roleid", GORM_PB_COLUMN_TYPE_INT},
        {"events", GORM_PB_COLUMN_TYPE_STRING},
    };
    mapTablesColumnInfo["cycleevent"] = mapColumnType;
    return GORM_OK;
}
int GORM_InitTableColumnInfo_equip(unordered_map<string, vector<string>> &mapTablesColumnOrder, unordered_map<string, unordered_map<string, GORM_PB_COLUMN_TYPE>> &mapTablesColumnInfo)
{
    vector<string> vColumns = {"version","roleid","snakeid","equip1","equip2","equip3","equip4"};
    mapTablesColumnOrder["equip"] = vColumns;
    unordered_map<string, GORM_PB_COLUMN_TYPE> mapColumnType = {
        {"version", GORM_PB_COLUMN_TYPE_UINT},
        {"roleid", GORM_PB_COLUMN_TYPE_INT},
        {"snakeid", GORM_PB_COLUMN_TYPE_INT},
        {"equip1", GORM_PB_COLUMN_TYPE_STRING},
        {"equip2", GORM_PB_COLUMN_TYPE_STRING},
        {"equip3", GORM_PB_COLUMN_TYPE_STRING},
        {"equip4", GORM_PB_COLUMN_TYPE_STRING},
    };
    mapTablesColumnInfo["equip"] = mapColumnType;
    return GORM_OK;
}
int GORM_InitTableColumnInfo_food(unordered_map<string, vector<string>> &mapTablesColumnOrder, unordered_map<string, unordered_map<string, GORM_PB_COLUMN_TYPE>> &mapTablesColumnInfo)
{
    vector<string> vColumns = {"version","roleid","snakeid","food1","food2","food3","food4"};
    mapTablesColumnOrder["food"] = vColumns;
    unordered_map<string, GORM_PB_COLUMN_TYPE> mapColumnType = {
        {"version", GORM_PB_COLUMN_TYPE_UINT},
        {"roleid", GORM_PB_COLUMN_TYPE_INT},
        {"snakeid", GORM_PB_COLUMN_TYPE_INT},
        {"food1", GORM_PB_COLUMN_TYPE_STRING},
        {"food2", GORM_PB_COLUMN_TYPE_STRING},
        {"food3", GORM_PB_COLUMN_TYPE_STRING},
        {"food4", GORM_PB_COLUMN_TYPE_STRING},
    };
    mapTablesColumnInfo["food"] = mapColumnType;
    return GORM_OK;
}
int GORM_InitTableColumnInfo_hero(unordered_map<string, vector<string>> &mapTablesColumnOrder, unordered_map<string, unordered_map<string, GORM_PB_COLUMN_TYPE>> &mapTablesColumnInfo)
{
    vector<string> vColumns = {"version","roleid","snakeid","heros"};
    mapTablesColumnOrder["hero"] = vColumns;
    unordered_map<string, GORM_PB_COLUMN_TYPE> mapColumnType = {
        {"version", GORM_PB_COLUMN_TYPE_UINT},
        {"roleid", GORM_PB_COLUMN_TYPE_INT},
        {"snakeid", GORM_PB_COLUMN_TYPE_INT},
        {"heros", GORM_PB_COLUMN_TYPE_STRING},
    };
    mapTablesColumnInfo["hero"] = mapColumnType;
    return GORM_OK;
}
int GORM_InitTableColumnInfo_mail(unordered_map<string, vector<string>> &mapTablesColumnOrder, unordered_map<string, unordered_map<string, GORM_PB_COLUMN_TYPE>> &mapTablesColumnInfo)
{
    vector<string> vColumns = {"version","roleid","mail1","mail2","mail3","mail4","mail5","lastmailid","snakeid"};
    mapTablesColumnOrder["mail"] = vColumns;
    unordered_map<string, GORM_PB_COLUMN_TYPE> mapColumnType = {
        {"version", GORM_PB_COLUMN_TYPE_UINT},
        {"roleid", GORM_PB_COLUMN_TYPE_INT},
        {"mail1", GORM_PB_COLUMN_TYPE_STRING},
        {"mail2", GORM_PB_COLUMN_TYPE_STRING},
        {"mail3", GORM_PB_COLUMN_TYPE_STRING},
        {"mail4", GORM_PB_COLUMN_TYPE_STRING},
        {"mail5", GORM_PB_COLUMN_TYPE_STRING},
        {"lastmailid", GORM_PB_COLUMN_TYPE_INT},
        {"snakeid", GORM_PB_COLUMN_TYPE_INT},
    };
    mapTablesColumnInfo["mail"] = mapColumnType;
    return GORM_OK;
}
int GORM_InitTableColumnInfo_material(unordered_map<string, vector<string>> &mapTablesColumnOrder, unordered_map<string, unordered_map<string, GORM_PB_COLUMN_TYPE>> &mapTablesColumnInfo)
{
    vector<string> vColumns = {"version","roleid","snakeid","material1","material2","material3","material4"};
    mapTablesColumnOrder["material"] = vColumns;
    unordered_map<string, GORM_PB_COLUMN_TYPE> mapColumnType = {
        {"version", GORM_PB_COLUMN_TYPE_UINT},
        {"roleid", GORM_PB_COLUMN_TYPE_INT},
        {"snakeid", GORM_PB_COLUMN_TYPE_INT},
        {"material1", GORM_PB_COLUMN_TYPE_STRING},
        {"material2", GORM_PB_COLUMN_TYPE_STRING},
        {"material3", GORM_PB_COLUMN_TYPE_STRING},
        {"material4", GORM_PB_COLUMN_TYPE_STRING},
    };
    mapTablesColumnInfo["material"] = mapColumnType;
    return GORM_OK;
}
int GORM_InitTableColumnInfo_npc(unordered_map<string, vector<string>> &mapTablesColumnOrder, unordered_map<string, unordered_map<string, GORM_PB_COLUMN_TYPE>> &mapTablesColumnInfo)
{
    vector<string> vColumns = {"version","roleid","snakeid","npcs"};
    mapTablesColumnOrder["npc"] = vColumns;
    unordered_map<string, GORM_PB_COLUMN_TYPE> mapColumnType = {
        {"version", GORM_PB_COLUMN_TYPE_UINT},
        {"roleid", GORM_PB_COLUMN_TYPE_INT},
        {"snakeid", GORM_PB_COLUMN_TYPE_INT},
        {"npcs", GORM_PB_COLUMN_TYPE_STRING},
    };
    mapTablesColumnInfo["npc"] = mapColumnType;
    return GORM_OK;
}
int GORM_InitTableColumnInfo_role(unordered_map<string, vector<string>> &mapTablesColumnOrder, unordered_map<string, unordered_map<string, GORM_PB_COLUMN_TYPE>> &mapTablesColumnInfo)
{
    vector<string> vColumns = {"version","roleid","rolename","level","exp","characterid","gold","offlinetime","inited","createtime","face","online"};
    mapTablesColumnOrder["role"] = vColumns;
    unordered_map<string, GORM_PB_COLUMN_TYPE> mapColumnType = {
        {"version", GORM_PB_COLUMN_TYPE_UINT},
        {"roleid", GORM_PB_COLUMN_TYPE_INT},
        {"rolename", GORM_PB_COLUMN_TYPE_STRING},
        {"level", GORM_PB_COLUMN_TYPE_INT},
        {"exp", GORM_PB_COLUMN_TYPE_INT},
        {"characterid", GORM_PB_COLUMN_TYPE_INT},
        {"gold", GORM_PB_COLUMN_TYPE_INT},
        {"offlinetime", GORM_PB_COLUMN_TYPE_INT},
        {"inited", GORM_PB_COLUMN_TYPE_INT},
        {"createtime", GORM_PB_COLUMN_TYPE_INT},
        {"face", GORM_PB_COLUMN_TYPE_STRING},
        {"online", GORM_PB_COLUMN_TYPE_INT},
    };
    mapTablesColumnInfo["role"] = mapColumnType;
    return GORM_OK;
}
int GORM_InitTableColumnInfo_scene(unordered_map<string, vector<string>> &mapTablesColumnOrder, unordered_map<string, unordered_map<string, GORM_PB_COLUMN_TYPE>> &mapTablesColumnInfo)
{
    vector<string> vColumns = {"version","roleid","sceneid","collects"};
    mapTablesColumnOrder["scene"] = vColumns;
    unordered_map<string, GORM_PB_COLUMN_TYPE> mapColumnType = {
        {"version", GORM_PB_COLUMN_TYPE_UINT},
        {"roleid", GORM_PB_COLUMN_TYPE_INT},
        {"sceneid", GORM_PB_COLUMN_TYPE_INT},
        {"collects", GORM_PB_COLUMN_TYPE_STRING},
    };
    mapTablesColumnInfo["scene"] = mapColumnType;
    return GORM_OK;
}
int GORM_InitTableColumnInfo_skill(unordered_map<string, vector<string>> &mapTablesColumnOrder, unordered_map<string, unordered_map<string, GORM_PB_COLUMN_TYPE>> &mapTablesColumnInfo)
{
    vector<string> vColumns = {"version","roleid","snakeid","skill1","skill2","skill3","skill4"};
    mapTablesColumnOrder["skill"] = vColumns;
    unordered_map<string, GORM_PB_COLUMN_TYPE> mapColumnType = {
        {"version", GORM_PB_COLUMN_TYPE_UINT},
        {"roleid", GORM_PB_COLUMN_TYPE_INT},
        {"snakeid", GORM_PB_COLUMN_TYPE_INT},
        {"skill1", GORM_PB_COLUMN_TYPE_STRING},
        {"skill2", GORM_PB_COLUMN_TYPE_STRING},
        {"skill3", GORM_PB_COLUMN_TYPE_STRING},
        {"skill4", GORM_PB_COLUMN_TYPE_STRING},
    };
    mapTablesColumnInfo["skill"] = mapColumnType;
    return GORM_OK;
}
int GORM_InitTableColumnInfo_interaction(unordered_map<string, vector<string>> &mapTablesColumnOrder, unordered_map<string, unordered_map<string, GORM_PB_COLUMN_TYPE>> &mapTablesColumnInfo)
{
    vector<string> vColumns = {"version","roleid","snakeid","interaction1","interaction2","interaction3","interaction4"};
    mapTablesColumnOrder["interaction"] = vColumns;
    unordered_map<string, GORM_PB_COLUMN_TYPE> mapColumnType = {
        {"version", GORM_PB_COLUMN_TYPE_UINT},
        {"roleid", GORM_PB_COLUMN_TYPE_INT},
        {"snakeid", GORM_PB_COLUMN_TYPE_INT},
        {"interaction1", GORM_PB_COLUMN_TYPE_STRING},
        {"interaction2", GORM_PB_COLUMN_TYPE_STRING},
        {"interaction3", GORM_PB_COLUMN_TYPE_STRING},
        {"interaction4", GORM_PB_COLUMN_TYPE_STRING},
    };
    mapTablesColumnInfo["interaction"] = mapColumnType;
    return GORM_OK;
}
int GORM_InitTableColumnInfo_user(unordered_map<string, vector<string>> &mapTablesColumnOrder, unordered_map<string, unordered_map<string, GORM_PB_COLUMN_TYPE>> &mapTablesColumnInfo)
{
    vector<string> vColumns = {"version","userid","ptid","pttype","createtime"};
    mapTablesColumnOrder["user"] = vColumns;
    unordered_map<string, GORM_PB_COLUMN_TYPE> mapColumnType = {
        {"version", GORM_PB_COLUMN_TYPE_UINT},
        {"userid", GORM_PB_COLUMN_TYPE_INT},
        {"ptid", GORM_PB_COLUMN_TYPE_STRING},
        {"pttype", GORM_PB_COLUMN_TYPE_INT},
        {"createtime", GORM_PB_COLUMN_TYPE_INT},
    };
    mapTablesColumnInfo["user"] = mapColumnType;
    return GORM_OK;
}
int GORM_InitTableColumnInfo_roles(unordered_map<string, vector<string>> &mapTablesColumnOrder, unordered_map<string, unordered_map<string, GORM_PB_COLUMN_TYPE>> &mapTablesColumnInfo)
{
    vector<string> vColumns = {"version","roleid","userid","worldid","dbid","name","charid","face","createtime"};
    mapTablesColumnOrder["roles"] = vColumns;
    unordered_map<string, GORM_PB_COLUMN_TYPE> mapColumnType = {
        {"version", GORM_PB_COLUMN_TYPE_UINT},
        {"roleid", GORM_PB_COLUMN_TYPE_INT},
        {"userid", GORM_PB_COLUMN_TYPE_INT},
        {"worldid", GORM_PB_COLUMN_TYPE_INT},
        {"dbid", GORM_PB_COLUMN_TYPE_INT},
        {"name", GORM_PB_COLUMN_TYPE_STRING},
        {"charid", GORM_PB_COLUMN_TYPE_INT},
        {"face", GORM_PB_COLUMN_TYPE_STRING},
        {"createtime", GORM_PB_COLUMN_TYPE_INT},
    };
    mapTablesColumnInfo["roles"] = mapColumnType;
    return GORM_OK;
}
int GORM_InitTableColumnInfo(unordered_map<string, vector<string>> &mapTablesColumnOrder, unordered_map<string, unordered_map<string, GORM_PB_COLUMN_TYPE>> &mapTablesColumnInfo)
{
    if (GORM_InitTableColumnInfo_currency(mapTablesColumnOrder, mapTablesColumnInfo))
        return GORM_ERROR;
    if (GORM_InitTableColumnInfo_cycleevent(mapTablesColumnOrder, mapTablesColumnInfo))
        return GORM_ERROR;
    if (GORM_InitTableColumnInfo_equip(mapTablesColumnOrder, mapTablesColumnInfo))
        return GORM_ERROR;
    if (GORM_InitTableColumnInfo_food(mapTablesColumnOrder, mapTablesColumnInfo))
        return GORM_ERROR;
    if (GORM_InitTableColumnInfo_hero(mapTablesColumnOrder, mapTablesColumnInfo))
        return GORM_ERROR;
    if (GORM_InitTableColumnInfo_mail(mapTablesColumnOrder, mapTablesColumnInfo))
        return GORM_ERROR;
    if (GORM_InitTableColumnInfo_material(mapTablesColumnOrder, mapTablesColumnInfo))
        return GORM_ERROR;
    if (GORM_InitTableColumnInfo_npc(mapTablesColumnOrder, mapTablesColumnInfo))
        return GORM_ERROR;
    if (GORM_InitTableColumnInfo_role(mapTablesColumnOrder, mapTablesColumnInfo))
        return GORM_ERROR;
    if (GORM_InitTableColumnInfo_scene(mapTablesColumnOrder, mapTablesColumnInfo))
        return GORM_ERROR;
    if (GORM_InitTableColumnInfo_skill(mapTablesColumnOrder, mapTablesColumnInfo))
        return GORM_ERROR;
    if (GORM_InitTableColumnInfo_interaction(mapTablesColumnOrder, mapTablesColumnInfo))
        return GORM_ERROR;
    if (GORM_InitTableColumnInfo_user(mapTablesColumnOrder, mapTablesColumnInfo))
        return GORM_ERROR;
    if (GORM_InitTableColumnInfo_roles(mapTablesColumnOrder, mapTablesColumnInfo))
        return GORM_ERROR;
    return GORM_OK;
}
void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, const char * value, const size_t size)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_CURRENCY1:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_currency1((const char*)value, size);
        }
        case GORM_PB_FIELD_CURRENCY_CURRENCY2:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_currency2((const char*)value, size);
        }
        case GORM_PB_FIELD_CURRENCY_CURRENCY3:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_currency3((const char*)value, size);
        }
        case GORM_PB_FIELD_CURRENCY_CURRENCY4:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_currency4((const char*)value, size);
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_EVENTS:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            return pPbReal->set_events((const char*)value, size);
        }
        }
    }
    case GORM_PB_TABLE_IDX_EQUIP:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_EQUIP_EQUIP1:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            return pPbReal->set_equip1((const char*)value, size);
        }
        case GORM_PB_FIELD_EQUIP_EQUIP2:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            return pPbReal->set_equip2((const char*)value, size);
        }
        case GORM_PB_FIELD_EQUIP_EQUIP3:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            return pPbReal->set_equip3((const char*)value, size);
        }
        case GORM_PB_FIELD_EQUIP_EQUIP4:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            return pPbReal->set_equip4((const char*)value, size);
        }
        }
    }
    case GORM_PB_TABLE_IDX_FOOD:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_FOOD_FOOD1:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            return pPbReal->set_food1((const char*)value, size);
        }
        case GORM_PB_FIELD_FOOD_FOOD2:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            return pPbReal->set_food2((const char*)value, size);
        }
        case GORM_PB_FIELD_FOOD_FOOD3:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            return pPbReal->set_food3((const char*)value, size);
        }
        case GORM_PB_FIELD_FOOD_FOOD4:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            return pPbReal->set_food4((const char*)value, size);
        }
        }
    }
    case GORM_PB_TABLE_IDX_HERO:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_HERO_HEROS:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            return pPbReal->set_heros((const char*)value, size);
        }
        }
    }
    case GORM_PB_TABLE_IDX_MAIL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MAIL_MAIL1:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_mail1((const char*)value, size);
        }
        case GORM_PB_FIELD_MAIL_MAIL2:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_mail2((const char*)value, size);
        }
        case GORM_PB_FIELD_MAIL_MAIL3:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_mail3((const char*)value, size);
        }
        case GORM_PB_FIELD_MAIL_MAIL4:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_mail4((const char*)value, size);
        }
        case GORM_PB_FIELD_MAIL_MAIL5:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_mail5((const char*)value, size);
        }
        }
    }
    case GORM_PB_TABLE_IDX_MATERIAL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MATERIAL_MATERIAL1:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            return pPbReal->set_material1((const char*)value, size);
        }
        case GORM_PB_FIELD_MATERIAL_MATERIAL2:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            return pPbReal->set_material2((const char*)value, size);
        }
        case GORM_PB_FIELD_MATERIAL_MATERIAL3:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            return pPbReal->set_material3((const char*)value, size);
        }
        case GORM_PB_FIELD_MATERIAL_MATERIAL4:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            return pPbReal->set_material4((const char*)value, size);
        }
        }
    }
    case GORM_PB_TABLE_IDX_NPC:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_NPC_NPCS:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            return pPbReal->set_npcs((const char*)value, size);
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_ROLENAME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_rolename((const char*)value, size);
        }
        case GORM_PB_FIELD_ROLE_FACE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_face((const char*)value, size);
        }
        }
    }
    case GORM_PB_TABLE_IDX_SCENE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SCENE_COLLECTS:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            return pPbReal->set_collects((const char*)value, size);
        }
        }
    }
    case GORM_PB_TABLE_IDX_SKILL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SKILL_SKILL1:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            return pPbReal->set_skill1((const char*)value, size);
        }
        case GORM_PB_FIELD_SKILL_SKILL2:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            return pPbReal->set_skill2((const char*)value, size);
        }
        case GORM_PB_FIELD_SKILL_SKILL3:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            return pPbReal->set_skill3((const char*)value, size);
        }
        case GORM_PB_FIELD_SKILL_SKILL4:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            return pPbReal->set_skill4((const char*)value, size);
        }
        }
    }
    case GORM_PB_TABLE_IDX_INTERACTION:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_INTERACTION_INTERACTION1:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            return pPbReal->set_interaction1((const char*)value, size);
        }
        case GORM_PB_FIELD_INTERACTION_INTERACTION2:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            return pPbReal->set_interaction2((const char*)value, size);
        }
        case GORM_PB_FIELD_INTERACTION_INTERACTION3:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            return pPbReal->set_interaction3((const char*)value, size);
        }
        case GORM_PB_FIELD_INTERACTION_INTERACTION4:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            return pPbReal->set_interaction4((const char*)value, size);
        }
        }
    }
    case GORM_PB_TABLE_IDX_USER:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_USER_PTID:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            return pPbReal->set_ptid((const char*)value, size);
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLES:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLES_NAME:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_name((const char*)value, size);
        }
        case GORM_PB_FIELD_ROLES_FACE:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_face((const char*)value, size);
        }
        }
    }
    }
}

void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, const char * value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_CURRENCY1:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_currency1((const char*)value);
        }
        case GORM_PB_FIELD_CURRENCY_CURRENCY2:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_currency2((const char*)value);
        }
        case GORM_PB_FIELD_CURRENCY_CURRENCY3:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_currency3((const char*)value);
        }
        case GORM_PB_FIELD_CURRENCY_CURRENCY4:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_currency4((const char*)value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_EVENTS:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            return pPbReal->set_events((const char*)value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_EQUIP:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_EQUIP_EQUIP1:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            return pPbReal->set_equip1((const char*)value);
        }
        case GORM_PB_FIELD_EQUIP_EQUIP2:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            return pPbReal->set_equip2((const char*)value);
        }
        case GORM_PB_FIELD_EQUIP_EQUIP3:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            return pPbReal->set_equip3((const char*)value);
        }
        case GORM_PB_FIELD_EQUIP_EQUIP4:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            return pPbReal->set_equip4((const char*)value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_FOOD:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_FOOD_FOOD1:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            return pPbReal->set_food1((const char*)value);
        }
        case GORM_PB_FIELD_FOOD_FOOD2:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            return pPbReal->set_food2((const char*)value);
        }
        case GORM_PB_FIELD_FOOD_FOOD3:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            return pPbReal->set_food3((const char*)value);
        }
        case GORM_PB_FIELD_FOOD_FOOD4:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            return pPbReal->set_food4((const char*)value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_HERO:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_HERO_HEROS:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            return pPbReal->set_heros((const char*)value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_MAIL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MAIL_MAIL1:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_mail1((const char*)value);
        }
        case GORM_PB_FIELD_MAIL_MAIL2:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_mail2((const char*)value);
        }
        case GORM_PB_FIELD_MAIL_MAIL3:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_mail3((const char*)value);
        }
        case GORM_PB_FIELD_MAIL_MAIL4:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_mail4((const char*)value);
        }
        case GORM_PB_FIELD_MAIL_MAIL5:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_mail5((const char*)value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_MATERIAL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MATERIAL_MATERIAL1:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            return pPbReal->set_material1((const char*)value);
        }
        case GORM_PB_FIELD_MATERIAL_MATERIAL2:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            return pPbReal->set_material2((const char*)value);
        }
        case GORM_PB_FIELD_MATERIAL_MATERIAL3:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            return pPbReal->set_material3((const char*)value);
        }
        case GORM_PB_FIELD_MATERIAL_MATERIAL4:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            return pPbReal->set_material4((const char*)value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_NPC:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_NPC_NPCS:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            return pPbReal->set_npcs((const char*)value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_ROLENAME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_rolename((const char*)value);
        }
        case GORM_PB_FIELD_ROLE_FACE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_face((const char*)value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_SCENE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SCENE_COLLECTS:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            return pPbReal->set_collects((const char*)value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_SKILL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SKILL_SKILL1:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            return pPbReal->set_skill1((const char*)value);
        }
        case GORM_PB_FIELD_SKILL_SKILL2:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            return pPbReal->set_skill2((const char*)value);
        }
        case GORM_PB_FIELD_SKILL_SKILL3:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            return pPbReal->set_skill3((const char*)value);
        }
        case GORM_PB_FIELD_SKILL_SKILL4:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            return pPbReal->set_skill4((const char*)value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_INTERACTION:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_INTERACTION_INTERACTION1:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            return pPbReal->set_interaction1((const char*)value);
        }
        case GORM_PB_FIELD_INTERACTION_INTERACTION2:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            return pPbReal->set_interaction2((const char*)value);
        }
        case GORM_PB_FIELD_INTERACTION_INTERACTION3:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            return pPbReal->set_interaction3((const char*)value);
        }
        case GORM_PB_FIELD_INTERACTION_INTERACTION4:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            return pPbReal->set_interaction4((const char*)value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_USER:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_USER_PTID:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            return pPbReal->set_ptid((const char*)value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLES:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLES_NAME:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_name((const char*)value);
        }
        case GORM_PB_FIELD_ROLES_FACE:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_face((const char*)value);
        }
        }
    }
    }
}

void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, int8 value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_VERSION:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_CURRENCY_ROLEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_CURRENCY_SNAKEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_VERSION:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_CYCLEEVENT_ROLEID:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_EQUIP:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_EQUIP_VERSION:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_EQUIP_ROLEID:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_EQUIP_SNAKEID:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_FOOD:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_FOOD_VERSION:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_FOOD_ROLEID:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_FOOD_SNAKEID:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_HERO:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_HERO_VERSION:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_HERO_ROLEID:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_HERO_SNAKEID:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_MAIL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MAIL_VERSION:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_MAIL_ROLEID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_MAIL_LASTMAILID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_lastmailid(value);
        }
        case GORM_PB_FIELD_MAIL_SNAKEID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_MATERIAL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MATERIAL_VERSION:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_MATERIAL_ROLEID:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_MATERIAL_SNAKEID:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_NPC:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_NPC_VERSION:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_NPC_ROLEID:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_NPC_SNAKEID:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_VERSION:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_level(value);
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_exp(value);
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_characterid(value);
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_gold(value);
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_offlinetime(value);
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_inited(value);
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_createtime(value);
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_online(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_SCENE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SCENE_VERSION:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_SCENE_ROLEID:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_SCENE_SCENEID:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            return pPbReal->set_sceneid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_SKILL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SKILL_VERSION:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_SKILL_ROLEID:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_SKILL_SNAKEID:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_INTERACTION:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_INTERACTION_VERSION:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_INTERACTION_ROLEID:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_INTERACTION_SNAKEID:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_USER:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_USER_VERSION:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_USER_USERID:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            return pPbReal->set_userid(value);
        }
        case GORM_PB_FIELD_USER_PTTYPE:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            return pPbReal->set_pttype(value);
        }
        case GORM_PB_FIELD_USER_CREATETIME:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            return pPbReal->set_createtime(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLES:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLES_VERSION:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_ROLES_ROLEID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_ROLES_USERID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_userid(value);
        }
        case GORM_PB_FIELD_ROLES_WORLDID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_worldid(value);
        }
        case GORM_PB_FIELD_ROLES_DBID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_dbid(value);
        }
        case GORM_PB_FIELD_ROLES_CHARID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_charid(value);
        }
        case GORM_PB_FIELD_ROLES_CREATETIME:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_createtime(value);
        }
        }
    }
    }
}

void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, int16 value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_VERSION:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_CURRENCY_ROLEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_CURRENCY_SNAKEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_VERSION:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_CYCLEEVENT_ROLEID:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_EQUIP:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_EQUIP_VERSION:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_EQUIP_ROLEID:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_EQUIP_SNAKEID:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_FOOD:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_FOOD_VERSION:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_FOOD_ROLEID:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_FOOD_SNAKEID:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_HERO:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_HERO_VERSION:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_HERO_ROLEID:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_HERO_SNAKEID:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_MAIL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MAIL_VERSION:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_MAIL_ROLEID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_MAIL_LASTMAILID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_lastmailid(value);
        }
        case GORM_PB_FIELD_MAIL_SNAKEID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_MATERIAL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MATERIAL_VERSION:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_MATERIAL_ROLEID:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_MATERIAL_SNAKEID:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_NPC:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_NPC_VERSION:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_NPC_ROLEID:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_NPC_SNAKEID:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_VERSION:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_level(value);
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_exp(value);
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_characterid(value);
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_gold(value);
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_offlinetime(value);
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_inited(value);
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_createtime(value);
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_online(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_SCENE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SCENE_VERSION:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_SCENE_ROLEID:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_SCENE_SCENEID:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            return pPbReal->set_sceneid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_SKILL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SKILL_VERSION:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_SKILL_ROLEID:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_SKILL_SNAKEID:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_INTERACTION:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_INTERACTION_VERSION:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_INTERACTION_ROLEID:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_INTERACTION_SNAKEID:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_USER:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_USER_VERSION:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_USER_USERID:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            return pPbReal->set_userid(value);
        }
        case GORM_PB_FIELD_USER_PTTYPE:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            return pPbReal->set_pttype(value);
        }
        case GORM_PB_FIELD_USER_CREATETIME:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            return pPbReal->set_createtime(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLES:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLES_VERSION:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_ROLES_ROLEID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_ROLES_USERID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_userid(value);
        }
        case GORM_PB_FIELD_ROLES_WORLDID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_worldid(value);
        }
        case GORM_PB_FIELD_ROLES_DBID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_dbid(value);
        }
        case GORM_PB_FIELD_ROLES_CHARID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_charid(value);
        }
        case GORM_PB_FIELD_ROLES_CREATETIME:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_createtime(value);
        }
        }
    }
    }
}

void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, int32 value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_VERSION:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_CURRENCY_ROLEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_CURRENCY_SNAKEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_VERSION:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_CYCLEEVENT_ROLEID:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_EQUIP:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_EQUIP_VERSION:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_EQUIP_ROLEID:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_EQUIP_SNAKEID:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_FOOD:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_FOOD_VERSION:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_FOOD_ROLEID:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_FOOD_SNAKEID:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_HERO:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_HERO_VERSION:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_HERO_ROLEID:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_HERO_SNAKEID:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_MAIL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MAIL_VERSION:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_MAIL_ROLEID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_MAIL_LASTMAILID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_lastmailid(value);
        }
        case GORM_PB_FIELD_MAIL_SNAKEID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_MATERIAL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MATERIAL_VERSION:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_MATERIAL_ROLEID:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_MATERIAL_SNAKEID:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_NPC:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_NPC_VERSION:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_NPC_ROLEID:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_NPC_SNAKEID:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_VERSION:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_level(value);
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_exp(value);
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_characterid(value);
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_gold(value);
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_offlinetime(value);
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_inited(value);
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_createtime(value);
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_online(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_SCENE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SCENE_VERSION:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_SCENE_ROLEID:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_SCENE_SCENEID:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            return pPbReal->set_sceneid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_SKILL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SKILL_VERSION:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_SKILL_ROLEID:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_SKILL_SNAKEID:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_INTERACTION:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_INTERACTION_VERSION:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_INTERACTION_ROLEID:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_INTERACTION_SNAKEID:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_USER:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_USER_VERSION:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_USER_USERID:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            return pPbReal->set_userid(value);
        }
        case GORM_PB_FIELD_USER_PTTYPE:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            return pPbReal->set_pttype(value);
        }
        case GORM_PB_FIELD_USER_CREATETIME:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            return pPbReal->set_createtime(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLES:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLES_VERSION:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_ROLES_ROLEID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_ROLES_USERID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_userid(value);
        }
        case GORM_PB_FIELD_ROLES_WORLDID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_worldid(value);
        }
        case GORM_PB_FIELD_ROLES_DBID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_dbid(value);
        }
        case GORM_PB_FIELD_ROLES_CHARID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_charid(value);
        }
        case GORM_PB_FIELD_ROLES_CREATETIME:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_createtime(value);
        }
        }
    }
    }
}

void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, int64 value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_VERSION:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_CURRENCY_ROLEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_CURRENCY_SNAKEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_VERSION:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_CYCLEEVENT_ROLEID:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_EQUIP:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_EQUIP_VERSION:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_EQUIP_ROLEID:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_EQUIP_SNAKEID:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_FOOD:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_FOOD_VERSION:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_FOOD_ROLEID:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_FOOD_SNAKEID:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_HERO:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_HERO_VERSION:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_HERO_ROLEID:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_HERO_SNAKEID:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_MAIL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MAIL_VERSION:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_MAIL_ROLEID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_MAIL_LASTMAILID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_lastmailid(value);
        }
        case GORM_PB_FIELD_MAIL_SNAKEID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_MATERIAL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MATERIAL_VERSION:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_MATERIAL_ROLEID:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_MATERIAL_SNAKEID:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_NPC:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_NPC_VERSION:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_NPC_ROLEID:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_NPC_SNAKEID:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_VERSION:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_level(value);
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_exp(value);
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_characterid(value);
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_gold(value);
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_offlinetime(value);
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_inited(value);
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_createtime(value);
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_online(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_SCENE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SCENE_VERSION:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_SCENE_ROLEID:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_SCENE_SCENEID:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            return pPbReal->set_sceneid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_SKILL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SKILL_VERSION:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_SKILL_ROLEID:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_SKILL_SNAKEID:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_INTERACTION:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_INTERACTION_VERSION:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_INTERACTION_ROLEID:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_INTERACTION_SNAKEID:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_USER:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_USER_VERSION:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_USER_USERID:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            return pPbReal->set_userid(value);
        }
        case GORM_PB_FIELD_USER_PTTYPE:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            return pPbReal->set_pttype(value);
        }
        case GORM_PB_FIELD_USER_CREATETIME:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            return pPbReal->set_createtime(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLES:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLES_VERSION:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_ROLES_ROLEID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_ROLES_USERID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_userid(value);
        }
        case GORM_PB_FIELD_ROLES_WORLDID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_worldid(value);
        }
        case GORM_PB_FIELD_ROLES_DBID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_dbid(value);
        }
        case GORM_PB_FIELD_ROLES_CHARID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_charid(value);
        }
        case GORM_PB_FIELD_ROLES_CREATETIME:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_createtime(value);
        }
        }
    }
    }
}

void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, double value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_VERSION:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_CURRENCY_ROLEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_CURRENCY_SNAKEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_VERSION:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_CYCLEEVENT_ROLEID:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_EQUIP:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_EQUIP_VERSION:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_EQUIP_ROLEID:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_EQUIP_SNAKEID:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_FOOD:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_FOOD_VERSION:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_FOOD_ROLEID:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_FOOD_SNAKEID:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_HERO:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_HERO_VERSION:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_HERO_ROLEID:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_HERO_SNAKEID:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_MAIL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MAIL_VERSION:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_MAIL_ROLEID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_MAIL_LASTMAILID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_lastmailid(value);
        }
        case GORM_PB_FIELD_MAIL_SNAKEID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_MATERIAL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MATERIAL_VERSION:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_MATERIAL_ROLEID:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_MATERIAL_SNAKEID:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_NPC:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_NPC_VERSION:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_NPC_ROLEID:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_NPC_SNAKEID:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_VERSION:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_level(value);
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_exp(value);
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_characterid(value);
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_gold(value);
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_offlinetime(value);
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_inited(value);
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_createtime(value);
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_online(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_SCENE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SCENE_VERSION:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_SCENE_ROLEID:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_SCENE_SCENEID:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            return pPbReal->set_sceneid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_SKILL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SKILL_VERSION:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_SKILL_ROLEID:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_SKILL_SNAKEID:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_INTERACTION:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_INTERACTION_VERSION:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_INTERACTION_ROLEID:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_INTERACTION_SNAKEID:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_USER:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_USER_VERSION:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_USER_USERID:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            return pPbReal->set_userid(value);
        }
        case GORM_PB_FIELD_USER_PTTYPE:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            return pPbReal->set_pttype(value);
        }
        case GORM_PB_FIELD_USER_CREATETIME:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            return pPbReal->set_createtime(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLES:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLES_VERSION:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_ROLES_ROLEID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_ROLES_USERID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_userid(value);
        }
        case GORM_PB_FIELD_ROLES_WORLDID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_worldid(value);
        }
        case GORM_PB_FIELD_ROLES_DBID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_dbid(value);
        }
        case GORM_PB_FIELD_ROLES_CHARID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_charid(value);
        }
        case GORM_PB_FIELD_ROLES_CREATETIME:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_createtime(value);
        }
        }
    }
    }
}

void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, uint8 value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_VERSION:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_CURRENCY_ROLEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_CURRENCY_SNAKEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_VERSION:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_CYCLEEVENT_ROLEID:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_EQUIP:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_EQUIP_VERSION:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_EQUIP_ROLEID:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_EQUIP_SNAKEID:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_FOOD:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_FOOD_VERSION:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_FOOD_ROLEID:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_FOOD_SNAKEID:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_HERO:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_HERO_VERSION:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_HERO_ROLEID:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_HERO_SNAKEID:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_MAIL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MAIL_VERSION:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_MAIL_ROLEID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_MAIL_LASTMAILID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_lastmailid(value);
        }
        case GORM_PB_FIELD_MAIL_SNAKEID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_MATERIAL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MATERIAL_VERSION:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_MATERIAL_ROLEID:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_MATERIAL_SNAKEID:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_NPC:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_NPC_VERSION:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_NPC_ROLEID:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_NPC_SNAKEID:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_VERSION:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_level(value);
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_exp(value);
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_characterid(value);
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_gold(value);
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_offlinetime(value);
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_inited(value);
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_createtime(value);
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_online(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_SCENE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SCENE_VERSION:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_SCENE_ROLEID:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_SCENE_SCENEID:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            return pPbReal->set_sceneid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_SKILL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SKILL_VERSION:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_SKILL_ROLEID:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_SKILL_SNAKEID:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_INTERACTION:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_INTERACTION_VERSION:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_INTERACTION_ROLEID:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_INTERACTION_SNAKEID:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_USER:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_USER_VERSION:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_USER_USERID:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            return pPbReal->set_userid(value);
        }
        case GORM_PB_FIELD_USER_PTTYPE:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            return pPbReal->set_pttype(value);
        }
        case GORM_PB_FIELD_USER_CREATETIME:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            return pPbReal->set_createtime(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLES:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLES_VERSION:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_ROLES_ROLEID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_ROLES_USERID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_userid(value);
        }
        case GORM_PB_FIELD_ROLES_WORLDID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_worldid(value);
        }
        case GORM_PB_FIELD_ROLES_DBID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_dbid(value);
        }
        case GORM_PB_FIELD_ROLES_CHARID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_charid(value);
        }
        case GORM_PB_FIELD_ROLES_CREATETIME:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_createtime(value);
        }
        }
    }
    }
}

void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, uint16 value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_VERSION:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_CURRENCY_ROLEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_CURRENCY_SNAKEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_VERSION:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_CYCLEEVENT_ROLEID:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_EQUIP:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_EQUIP_VERSION:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_EQUIP_ROLEID:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_EQUIP_SNAKEID:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_FOOD:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_FOOD_VERSION:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_FOOD_ROLEID:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_FOOD_SNAKEID:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_HERO:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_HERO_VERSION:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_HERO_ROLEID:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_HERO_SNAKEID:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_MAIL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MAIL_VERSION:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_MAIL_ROLEID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_MAIL_LASTMAILID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_lastmailid(value);
        }
        case GORM_PB_FIELD_MAIL_SNAKEID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_MATERIAL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MATERIAL_VERSION:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_MATERIAL_ROLEID:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_MATERIAL_SNAKEID:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_NPC:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_NPC_VERSION:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_NPC_ROLEID:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_NPC_SNAKEID:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_VERSION:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_level(value);
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_exp(value);
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_characterid(value);
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_gold(value);
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_offlinetime(value);
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_inited(value);
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_createtime(value);
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_online(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_SCENE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SCENE_VERSION:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_SCENE_ROLEID:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_SCENE_SCENEID:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            return pPbReal->set_sceneid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_SKILL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SKILL_VERSION:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_SKILL_ROLEID:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_SKILL_SNAKEID:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_INTERACTION:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_INTERACTION_VERSION:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_INTERACTION_ROLEID:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_INTERACTION_SNAKEID:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_USER:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_USER_VERSION:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_USER_USERID:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            return pPbReal->set_userid(value);
        }
        case GORM_PB_FIELD_USER_PTTYPE:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            return pPbReal->set_pttype(value);
        }
        case GORM_PB_FIELD_USER_CREATETIME:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            return pPbReal->set_createtime(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLES:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLES_VERSION:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_ROLES_ROLEID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_ROLES_USERID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_userid(value);
        }
        case GORM_PB_FIELD_ROLES_WORLDID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_worldid(value);
        }
        case GORM_PB_FIELD_ROLES_DBID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_dbid(value);
        }
        case GORM_PB_FIELD_ROLES_CHARID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_charid(value);
        }
        case GORM_PB_FIELD_ROLES_CREATETIME:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_createtime(value);
        }
        }
    }
    }
}

void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, uint32 value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_VERSION:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_CURRENCY_ROLEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_CURRENCY_SNAKEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_VERSION:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_CYCLEEVENT_ROLEID:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_EQUIP:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_EQUIP_VERSION:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_EQUIP_ROLEID:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_EQUIP_SNAKEID:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_FOOD:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_FOOD_VERSION:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_FOOD_ROLEID:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_FOOD_SNAKEID:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_HERO:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_HERO_VERSION:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_HERO_ROLEID:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_HERO_SNAKEID:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_MAIL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MAIL_VERSION:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_MAIL_ROLEID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_MAIL_LASTMAILID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_lastmailid(value);
        }
        case GORM_PB_FIELD_MAIL_SNAKEID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_MATERIAL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MATERIAL_VERSION:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_MATERIAL_ROLEID:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_MATERIAL_SNAKEID:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_NPC:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_NPC_VERSION:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_NPC_ROLEID:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_NPC_SNAKEID:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_VERSION:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_level(value);
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_exp(value);
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_characterid(value);
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_gold(value);
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_offlinetime(value);
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_inited(value);
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_createtime(value);
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_online(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_SCENE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SCENE_VERSION:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_SCENE_ROLEID:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_SCENE_SCENEID:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            return pPbReal->set_sceneid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_SKILL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SKILL_VERSION:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_SKILL_ROLEID:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_SKILL_SNAKEID:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_INTERACTION:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_INTERACTION_VERSION:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_INTERACTION_ROLEID:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_INTERACTION_SNAKEID:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_USER:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_USER_VERSION:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_USER_USERID:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            return pPbReal->set_userid(value);
        }
        case GORM_PB_FIELD_USER_PTTYPE:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            return pPbReal->set_pttype(value);
        }
        case GORM_PB_FIELD_USER_CREATETIME:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            return pPbReal->set_createtime(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLES:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLES_VERSION:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_ROLES_ROLEID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_ROLES_USERID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_userid(value);
        }
        case GORM_PB_FIELD_ROLES_WORLDID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_worldid(value);
        }
        case GORM_PB_FIELD_ROLES_DBID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_dbid(value);
        }
        case GORM_PB_FIELD_ROLES_CHARID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_charid(value);
        }
        case GORM_PB_FIELD_ROLES_CREATETIME:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_createtime(value);
        }
        }
    }
    }
}

void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, uint64 value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_VERSION:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_CURRENCY_ROLEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_CURRENCY_SNAKEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_VERSION:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_CYCLEEVENT_ROLEID:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_EQUIP:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_EQUIP_VERSION:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_EQUIP_ROLEID:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_EQUIP_SNAKEID:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_FOOD:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_FOOD_VERSION:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_FOOD_ROLEID:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_FOOD_SNAKEID:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_HERO:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_HERO_VERSION:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_HERO_ROLEID:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_HERO_SNAKEID:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_MAIL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MAIL_VERSION:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_MAIL_ROLEID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_MAIL_LASTMAILID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_lastmailid(value);
        }
        case GORM_PB_FIELD_MAIL_SNAKEID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_MATERIAL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MATERIAL_VERSION:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_MATERIAL_ROLEID:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_MATERIAL_SNAKEID:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_NPC:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_NPC_VERSION:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_NPC_ROLEID:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_NPC_SNAKEID:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_VERSION:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_level(value);
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_exp(value);
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_characterid(value);
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_gold(value);
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_offlinetime(value);
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_inited(value);
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_createtime(value);
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_online(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_SCENE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SCENE_VERSION:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_SCENE_ROLEID:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_SCENE_SCENEID:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            return pPbReal->set_sceneid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_SKILL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SKILL_VERSION:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_SKILL_ROLEID:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_SKILL_SNAKEID:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_INTERACTION:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_INTERACTION_VERSION:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_INTERACTION_ROLEID:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_INTERACTION_SNAKEID:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_USER:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_USER_VERSION:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_USER_USERID:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            return pPbReal->set_userid(value);
        }
        case GORM_PB_FIELD_USER_PTTYPE:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            return pPbReal->set_pttype(value);
        }
        case GORM_PB_FIELD_USER_CREATETIME:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            return pPbReal->set_createtime(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLES:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLES_VERSION:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_ROLES_ROLEID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_ROLES_USERID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_userid(value);
        }
        case GORM_PB_FIELD_ROLES_WORLDID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_worldid(value);
        }
        case GORM_PB_FIELD_ROLES_DBID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_dbid(value);
        }
        case GORM_PB_FIELD_ROLES_CHARID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_charid(value);
        }
        case GORM_PB_FIELD_ROLES_CREATETIME:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            return pPbReal->set_createtime(value);
        }
        }
    }
    }
}

int GORM_GetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, string &value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_CURRENCY1:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->currency1();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_CURRENCY2:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->currency2();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_CURRENCY3:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->currency3();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_CURRENCY4:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->currency4();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_EVENTS:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            value = pPbReal->events();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_EQUIP:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_EQUIP_EQUIP1:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            value = pPbReal->equip1();
            return GORM_OK;
        }
        case GORM_PB_FIELD_EQUIP_EQUIP2:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            value = pPbReal->equip2();
            return GORM_OK;
        }
        case GORM_PB_FIELD_EQUIP_EQUIP3:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            value = pPbReal->equip3();
            return GORM_OK;
        }
        case GORM_PB_FIELD_EQUIP_EQUIP4:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            value = pPbReal->equip4();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_FOOD:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_FOOD_FOOD1:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            value = pPbReal->food1();
            return GORM_OK;
        }
        case GORM_PB_FIELD_FOOD_FOOD2:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            value = pPbReal->food2();
            return GORM_OK;
        }
        case GORM_PB_FIELD_FOOD_FOOD3:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            value = pPbReal->food3();
            return GORM_OK;
        }
        case GORM_PB_FIELD_FOOD_FOOD4:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            value = pPbReal->food4();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_HERO:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_HERO_HEROS:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            value = pPbReal->heros();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_MAIL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MAIL_MAIL1:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            value = pPbReal->mail1();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MAIL_MAIL2:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            value = pPbReal->mail2();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MAIL_MAIL3:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            value = pPbReal->mail3();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MAIL_MAIL4:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            value = pPbReal->mail4();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MAIL_MAIL5:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            value = pPbReal->mail5();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_MATERIAL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MATERIAL_MATERIAL1:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            value = pPbReal->material1();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MATERIAL_MATERIAL2:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            value = pPbReal->material2();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MATERIAL_MATERIAL3:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            value = pPbReal->material3();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MATERIAL_MATERIAL4:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            value = pPbReal->material4();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_NPC:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_NPC_NPCS:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            value = pPbReal->npcs();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_ROLENAME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->rolename();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_FACE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->face();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_SCENE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SCENE_COLLECTS:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            value = pPbReal->collects();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_SKILL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SKILL_SKILL1:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            value = pPbReal->skill1();
            return GORM_OK;
        }
        case GORM_PB_FIELD_SKILL_SKILL2:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            value = pPbReal->skill2();
            return GORM_OK;
        }
        case GORM_PB_FIELD_SKILL_SKILL3:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            value = pPbReal->skill3();
            return GORM_OK;
        }
        case GORM_PB_FIELD_SKILL_SKILL4:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            value = pPbReal->skill4();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_INTERACTION:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_INTERACTION_INTERACTION1:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            value = pPbReal->interaction1();
            return GORM_OK;
        }
        case GORM_PB_FIELD_INTERACTION_INTERACTION2:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            value = pPbReal->interaction2();
            return GORM_OK;
        }
        case GORM_PB_FIELD_INTERACTION_INTERACTION3:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            value = pPbReal->interaction3();
            return GORM_OK;
        }
        case GORM_PB_FIELD_INTERACTION_INTERACTION4:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            value = pPbReal->interaction4();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_USER:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_USER_PTID:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            value = pPbReal->ptid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLES:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLES_NAME:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->name();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_FACE:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->face();
            return GORM_OK;
        }
        }
    }
    }

    return GORM_ERROR;
}

int GORM_GetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, uint8 *&value, size_t &size)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_CURRENCY1:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            string strValue = pPbReal->currency1();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_CURRENCY2:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            string strValue = pPbReal->currency2();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_CURRENCY3:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            string strValue = pPbReal->currency3();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_CURRENCY4:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            string strValue = pPbReal->currency4();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_EVENTS:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            string strValue = pPbReal->events();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_EQUIP:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_EQUIP_EQUIP1:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            string strValue = pPbReal->equip1();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        case GORM_PB_FIELD_EQUIP_EQUIP2:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            string strValue = pPbReal->equip2();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        case GORM_PB_FIELD_EQUIP_EQUIP3:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            string strValue = pPbReal->equip3();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        case GORM_PB_FIELD_EQUIP_EQUIP4:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            string strValue = pPbReal->equip4();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_FOOD:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_FOOD_FOOD1:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            string strValue = pPbReal->food1();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        case GORM_PB_FIELD_FOOD_FOOD2:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            string strValue = pPbReal->food2();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        case GORM_PB_FIELD_FOOD_FOOD3:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            string strValue = pPbReal->food3();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        case GORM_PB_FIELD_FOOD_FOOD4:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            string strValue = pPbReal->food4();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_HERO:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_HERO_HEROS:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            string strValue = pPbReal->heros();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_MAIL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MAIL_MAIL1:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            string strValue = pPbReal->mail1();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MAIL_MAIL2:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            string strValue = pPbReal->mail2();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MAIL_MAIL3:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            string strValue = pPbReal->mail3();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MAIL_MAIL4:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            string strValue = pPbReal->mail4();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MAIL_MAIL5:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            string strValue = pPbReal->mail5();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_MATERIAL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MATERIAL_MATERIAL1:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            string strValue = pPbReal->material1();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MATERIAL_MATERIAL2:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            string strValue = pPbReal->material2();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MATERIAL_MATERIAL3:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            string strValue = pPbReal->material3();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MATERIAL_MATERIAL4:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            string strValue = pPbReal->material4();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_NPC:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_NPC_NPCS:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            string strValue = pPbReal->npcs();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_ROLENAME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            string strValue = pPbReal->rolename();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_FACE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            string strValue = pPbReal->face();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_SCENE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SCENE_COLLECTS:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            string strValue = pPbReal->collects();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_SKILL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SKILL_SKILL1:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            string strValue = pPbReal->skill1();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        case GORM_PB_FIELD_SKILL_SKILL2:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            string strValue = pPbReal->skill2();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        case GORM_PB_FIELD_SKILL_SKILL3:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            string strValue = pPbReal->skill3();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        case GORM_PB_FIELD_SKILL_SKILL4:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            string strValue = pPbReal->skill4();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_INTERACTION:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_INTERACTION_INTERACTION1:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            string strValue = pPbReal->interaction1();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        case GORM_PB_FIELD_INTERACTION_INTERACTION2:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            string strValue = pPbReal->interaction2();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        case GORM_PB_FIELD_INTERACTION_INTERACTION3:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            string strValue = pPbReal->interaction3();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        case GORM_PB_FIELD_INTERACTION_INTERACTION4:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            string strValue = pPbReal->interaction4();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_USER:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_USER_PTID:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            string strValue = pPbReal->ptid();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLES:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLES_NAME:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            string strValue = pPbReal->name();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_FACE:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            string strValue = pPbReal->face();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        }
    }
    }

    return GORM_ERROR;
}

int GORM_GetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, int8 &value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_VERSION:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_ROLEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_SNAKEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_VERSION:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CYCLEEVENT_ROLEID:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_EQUIP:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_EQUIP_VERSION:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_EQUIP_ROLEID:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_EQUIP_SNAKEID:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_FOOD:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_FOOD_VERSION:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_FOOD_ROLEID:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_FOOD_SNAKEID:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_HERO:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_HERO_VERSION:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_HERO_ROLEID:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_HERO_SNAKEID:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_MAIL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MAIL_VERSION:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MAIL_ROLEID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MAIL_LASTMAILID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            value = pPbReal->lastmailid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MAIL_SNAKEID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_MATERIAL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MATERIAL_VERSION:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MATERIAL_ROLEID:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MATERIAL_SNAKEID:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_NPC:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_NPC_VERSION:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_NPC_ROLEID:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_NPC_SNAKEID:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_VERSION:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->level();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->exp();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->characterid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->gold();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->offlinetime();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->inited();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->createtime();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->online();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_SCENE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SCENE_VERSION:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_SCENE_ROLEID:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_SCENE_SCENEID:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            value = pPbReal->sceneid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_SKILL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SKILL_VERSION:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_SKILL_ROLEID:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_SKILL_SNAKEID:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_INTERACTION:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_INTERACTION_VERSION:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_INTERACTION_ROLEID:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_INTERACTION_SNAKEID:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_USER:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_USER_VERSION:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_USER_USERID:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            value = pPbReal->userid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_USER_PTTYPE:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            value = pPbReal->pttype();
            return GORM_OK;
        }
        case GORM_PB_FIELD_USER_CREATETIME:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            value = pPbReal->createtime();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLES:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLES_VERSION:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_ROLEID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_USERID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->userid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_WORLDID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->worldid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_DBID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->dbid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_CHARID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->charid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_CREATETIME:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->createtime();
            return GORM_OK;
        }
        }
    }
    }

    return GORM_ERROR;
}

int GORM_GetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, int16 &value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_VERSION:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_ROLEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_SNAKEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_VERSION:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CYCLEEVENT_ROLEID:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_EQUIP:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_EQUIP_VERSION:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_EQUIP_ROLEID:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_EQUIP_SNAKEID:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_FOOD:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_FOOD_VERSION:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_FOOD_ROLEID:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_FOOD_SNAKEID:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_HERO:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_HERO_VERSION:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_HERO_ROLEID:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_HERO_SNAKEID:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_MAIL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MAIL_VERSION:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MAIL_ROLEID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MAIL_LASTMAILID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            value = pPbReal->lastmailid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MAIL_SNAKEID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_MATERIAL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MATERIAL_VERSION:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MATERIAL_ROLEID:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MATERIAL_SNAKEID:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_NPC:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_NPC_VERSION:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_NPC_ROLEID:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_NPC_SNAKEID:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_VERSION:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->level();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->exp();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->characterid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->gold();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->offlinetime();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->inited();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->createtime();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->online();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_SCENE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SCENE_VERSION:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_SCENE_ROLEID:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_SCENE_SCENEID:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            value = pPbReal->sceneid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_SKILL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SKILL_VERSION:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_SKILL_ROLEID:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_SKILL_SNAKEID:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_INTERACTION:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_INTERACTION_VERSION:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_INTERACTION_ROLEID:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_INTERACTION_SNAKEID:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_USER:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_USER_VERSION:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_USER_USERID:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            value = pPbReal->userid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_USER_PTTYPE:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            value = pPbReal->pttype();
            return GORM_OK;
        }
        case GORM_PB_FIELD_USER_CREATETIME:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            value = pPbReal->createtime();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLES:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLES_VERSION:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_ROLEID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_USERID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->userid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_WORLDID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->worldid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_DBID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->dbid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_CHARID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->charid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_CREATETIME:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->createtime();
            return GORM_OK;
        }
        }
    }
    }

    return GORM_ERROR;
}

int GORM_GetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, int32 &value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_VERSION:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_ROLEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_SNAKEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_VERSION:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CYCLEEVENT_ROLEID:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_EQUIP:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_EQUIP_VERSION:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_EQUIP_ROLEID:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_EQUIP_SNAKEID:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_FOOD:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_FOOD_VERSION:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_FOOD_ROLEID:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_FOOD_SNAKEID:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_HERO:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_HERO_VERSION:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_HERO_ROLEID:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_HERO_SNAKEID:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_MAIL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MAIL_VERSION:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MAIL_ROLEID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MAIL_LASTMAILID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            value = pPbReal->lastmailid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MAIL_SNAKEID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_MATERIAL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MATERIAL_VERSION:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MATERIAL_ROLEID:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MATERIAL_SNAKEID:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_NPC:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_NPC_VERSION:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_NPC_ROLEID:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_NPC_SNAKEID:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_VERSION:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->level();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->exp();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->characterid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->gold();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->offlinetime();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->inited();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->createtime();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->online();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_SCENE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SCENE_VERSION:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_SCENE_ROLEID:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_SCENE_SCENEID:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            value = pPbReal->sceneid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_SKILL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SKILL_VERSION:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_SKILL_ROLEID:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_SKILL_SNAKEID:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_INTERACTION:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_INTERACTION_VERSION:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_INTERACTION_ROLEID:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_INTERACTION_SNAKEID:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_USER:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_USER_VERSION:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_USER_USERID:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            value = pPbReal->userid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_USER_PTTYPE:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            value = pPbReal->pttype();
            return GORM_OK;
        }
        case GORM_PB_FIELD_USER_CREATETIME:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            value = pPbReal->createtime();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLES:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLES_VERSION:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_ROLEID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_USERID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->userid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_WORLDID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->worldid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_DBID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->dbid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_CHARID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->charid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_CREATETIME:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->createtime();
            return GORM_OK;
        }
        }
    }
    }

    return GORM_ERROR;
}

int GORM_GetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, int64 &value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_VERSION:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_ROLEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_SNAKEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_VERSION:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CYCLEEVENT_ROLEID:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_EQUIP:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_EQUIP_VERSION:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_EQUIP_ROLEID:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_EQUIP_SNAKEID:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_FOOD:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_FOOD_VERSION:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_FOOD_ROLEID:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_FOOD_SNAKEID:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_HERO:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_HERO_VERSION:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_HERO_ROLEID:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_HERO_SNAKEID:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_MAIL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MAIL_VERSION:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MAIL_ROLEID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MAIL_LASTMAILID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            value = pPbReal->lastmailid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MAIL_SNAKEID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_MATERIAL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MATERIAL_VERSION:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MATERIAL_ROLEID:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MATERIAL_SNAKEID:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_NPC:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_NPC_VERSION:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_NPC_ROLEID:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_NPC_SNAKEID:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_VERSION:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->level();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->exp();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->characterid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->gold();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->offlinetime();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->inited();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->createtime();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->online();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_SCENE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SCENE_VERSION:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_SCENE_ROLEID:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_SCENE_SCENEID:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            value = pPbReal->sceneid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_SKILL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SKILL_VERSION:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_SKILL_ROLEID:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_SKILL_SNAKEID:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_INTERACTION:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_INTERACTION_VERSION:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_INTERACTION_ROLEID:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_INTERACTION_SNAKEID:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_USER:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_USER_VERSION:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_USER_USERID:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            value = pPbReal->userid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_USER_PTTYPE:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            value = pPbReal->pttype();
            return GORM_OK;
        }
        case GORM_PB_FIELD_USER_CREATETIME:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            value = pPbReal->createtime();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLES:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLES_VERSION:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_ROLEID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_USERID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->userid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_WORLDID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->worldid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_DBID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->dbid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_CHARID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->charid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_CREATETIME:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->createtime();
            return GORM_OK;
        }
        }
    }
    }

    return GORM_ERROR;
}

int GORM_GetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, double &value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_VERSION:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_ROLEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_SNAKEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_VERSION:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CYCLEEVENT_ROLEID:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_EQUIP:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_EQUIP_VERSION:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_EQUIP_ROLEID:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_EQUIP_SNAKEID:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_FOOD:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_FOOD_VERSION:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_FOOD_ROLEID:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_FOOD_SNAKEID:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_HERO:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_HERO_VERSION:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_HERO_ROLEID:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_HERO_SNAKEID:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_MAIL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MAIL_VERSION:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MAIL_ROLEID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MAIL_LASTMAILID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            value = pPbReal->lastmailid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MAIL_SNAKEID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_MATERIAL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MATERIAL_VERSION:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MATERIAL_ROLEID:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MATERIAL_SNAKEID:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_NPC:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_NPC_VERSION:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_NPC_ROLEID:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_NPC_SNAKEID:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_VERSION:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->level();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->exp();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->characterid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->gold();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->offlinetime();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->inited();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->createtime();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->online();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_SCENE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SCENE_VERSION:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_SCENE_ROLEID:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_SCENE_SCENEID:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            value = pPbReal->sceneid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_SKILL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SKILL_VERSION:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_SKILL_ROLEID:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_SKILL_SNAKEID:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_INTERACTION:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_INTERACTION_VERSION:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_INTERACTION_ROLEID:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_INTERACTION_SNAKEID:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_USER:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_USER_VERSION:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_USER_USERID:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            value = pPbReal->userid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_USER_PTTYPE:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            value = pPbReal->pttype();
            return GORM_OK;
        }
        case GORM_PB_FIELD_USER_CREATETIME:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            value = pPbReal->createtime();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLES:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLES_VERSION:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_ROLEID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_USERID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->userid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_WORLDID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->worldid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_DBID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->dbid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_CHARID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->charid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_CREATETIME:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->createtime();
            return GORM_OK;
        }
        }
    }
    }

    return GORM_ERROR;
}

int GORM_GetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, uint8 &value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_VERSION:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_ROLEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_SNAKEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_VERSION:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CYCLEEVENT_ROLEID:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_EQUIP:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_EQUIP_VERSION:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_EQUIP_ROLEID:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_EQUIP_SNAKEID:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_FOOD:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_FOOD_VERSION:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_FOOD_ROLEID:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_FOOD_SNAKEID:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_HERO:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_HERO_VERSION:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_HERO_ROLEID:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_HERO_SNAKEID:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_MAIL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MAIL_VERSION:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MAIL_ROLEID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MAIL_LASTMAILID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            value = pPbReal->lastmailid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MAIL_SNAKEID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_MATERIAL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MATERIAL_VERSION:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MATERIAL_ROLEID:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MATERIAL_SNAKEID:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_NPC:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_NPC_VERSION:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_NPC_ROLEID:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_NPC_SNAKEID:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_VERSION:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->level();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->exp();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->characterid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->gold();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->offlinetime();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->inited();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->createtime();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->online();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_SCENE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SCENE_VERSION:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_SCENE_ROLEID:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_SCENE_SCENEID:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            value = pPbReal->sceneid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_SKILL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SKILL_VERSION:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_SKILL_ROLEID:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_SKILL_SNAKEID:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_INTERACTION:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_INTERACTION_VERSION:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_INTERACTION_ROLEID:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_INTERACTION_SNAKEID:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_USER:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_USER_VERSION:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_USER_USERID:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            value = pPbReal->userid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_USER_PTTYPE:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            value = pPbReal->pttype();
            return GORM_OK;
        }
        case GORM_PB_FIELD_USER_CREATETIME:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            value = pPbReal->createtime();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLES:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLES_VERSION:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_ROLEID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_USERID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->userid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_WORLDID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->worldid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_DBID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->dbid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_CHARID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->charid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_CREATETIME:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->createtime();
            return GORM_OK;
        }
        }
    }
    }

    return GORM_ERROR;
}

int GORM_GetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, uint16 &value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_VERSION:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_ROLEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_SNAKEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_VERSION:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CYCLEEVENT_ROLEID:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_EQUIP:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_EQUIP_VERSION:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_EQUIP_ROLEID:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_EQUIP_SNAKEID:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_FOOD:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_FOOD_VERSION:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_FOOD_ROLEID:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_FOOD_SNAKEID:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_HERO:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_HERO_VERSION:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_HERO_ROLEID:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_HERO_SNAKEID:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_MAIL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MAIL_VERSION:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MAIL_ROLEID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MAIL_LASTMAILID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            value = pPbReal->lastmailid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MAIL_SNAKEID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_MATERIAL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MATERIAL_VERSION:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MATERIAL_ROLEID:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MATERIAL_SNAKEID:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_NPC:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_NPC_VERSION:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_NPC_ROLEID:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_NPC_SNAKEID:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_VERSION:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->level();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->exp();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->characterid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->gold();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->offlinetime();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->inited();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->createtime();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->online();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_SCENE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SCENE_VERSION:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_SCENE_ROLEID:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_SCENE_SCENEID:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            value = pPbReal->sceneid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_SKILL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SKILL_VERSION:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_SKILL_ROLEID:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_SKILL_SNAKEID:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_INTERACTION:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_INTERACTION_VERSION:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_INTERACTION_ROLEID:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_INTERACTION_SNAKEID:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_USER:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_USER_VERSION:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_USER_USERID:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            value = pPbReal->userid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_USER_PTTYPE:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            value = pPbReal->pttype();
            return GORM_OK;
        }
        case GORM_PB_FIELD_USER_CREATETIME:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            value = pPbReal->createtime();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLES:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLES_VERSION:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_ROLEID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_USERID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->userid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_WORLDID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->worldid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_DBID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->dbid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_CHARID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->charid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_CREATETIME:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->createtime();
            return GORM_OK;
        }
        }
    }
    }

    return GORM_ERROR;
}

int GORM_GetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, uint32 &value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_VERSION:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_ROLEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_SNAKEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_VERSION:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CYCLEEVENT_ROLEID:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_EQUIP:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_EQUIP_VERSION:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_EQUIP_ROLEID:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_EQUIP_SNAKEID:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_FOOD:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_FOOD_VERSION:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_FOOD_ROLEID:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_FOOD_SNAKEID:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_HERO:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_HERO_VERSION:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_HERO_ROLEID:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_HERO_SNAKEID:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_MAIL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MAIL_VERSION:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MAIL_ROLEID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MAIL_LASTMAILID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            value = pPbReal->lastmailid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MAIL_SNAKEID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_MATERIAL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MATERIAL_VERSION:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MATERIAL_ROLEID:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MATERIAL_SNAKEID:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_NPC:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_NPC_VERSION:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_NPC_ROLEID:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_NPC_SNAKEID:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_VERSION:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->level();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->exp();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->characterid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->gold();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->offlinetime();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->inited();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->createtime();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->online();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_SCENE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SCENE_VERSION:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_SCENE_ROLEID:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_SCENE_SCENEID:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            value = pPbReal->sceneid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_SKILL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SKILL_VERSION:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_SKILL_ROLEID:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_SKILL_SNAKEID:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_INTERACTION:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_INTERACTION_VERSION:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_INTERACTION_ROLEID:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_INTERACTION_SNAKEID:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_USER:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_USER_VERSION:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_USER_USERID:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            value = pPbReal->userid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_USER_PTTYPE:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            value = pPbReal->pttype();
            return GORM_OK;
        }
        case GORM_PB_FIELD_USER_CREATETIME:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            value = pPbReal->createtime();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLES:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLES_VERSION:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_ROLEID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_USERID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->userid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_WORLDID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->worldid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_DBID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->dbid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_CHARID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->charid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_CREATETIME:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->createtime();
            return GORM_OK;
        }
        }
    }
    }

    return GORM_ERROR;
}

int GORM_GetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, uint64 &value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_VERSION:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_ROLEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_SNAKEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_VERSION:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CYCLEEVENT_ROLEID:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_EQUIP:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_EQUIP_VERSION:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_EQUIP_ROLEID:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_EQUIP_SNAKEID:
        {
            GORM_PB_Table_equip* pPbReal = dynamic_cast<GORM_PB_Table_equip*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_FOOD:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_FOOD_VERSION:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_FOOD_ROLEID:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_FOOD_SNAKEID:
        {
            GORM_PB_Table_food* pPbReal = dynamic_cast<GORM_PB_Table_food*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_HERO:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_HERO_VERSION:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_HERO_ROLEID:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_HERO_SNAKEID:
        {
            GORM_PB_Table_hero* pPbReal = dynamic_cast<GORM_PB_Table_hero*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_MAIL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MAIL_VERSION:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MAIL_ROLEID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MAIL_LASTMAILID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            value = pPbReal->lastmailid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MAIL_SNAKEID:
        {
            GORM_PB_Table_mail* pPbReal = dynamic_cast<GORM_PB_Table_mail*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_MATERIAL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MATERIAL_VERSION:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MATERIAL_ROLEID:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_MATERIAL_SNAKEID:
        {
            GORM_PB_Table_material* pPbReal = dynamic_cast<GORM_PB_Table_material*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_NPC:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_NPC_VERSION:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_NPC_ROLEID:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_NPC_SNAKEID:
        {
            GORM_PB_Table_npc* pPbReal = dynamic_cast<GORM_PB_Table_npc*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_VERSION:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->level();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->exp();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->characterid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->gold();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->offlinetime();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->inited();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->createtime();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->online();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_SCENE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SCENE_VERSION:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_SCENE_ROLEID:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_SCENE_SCENEID:
        {
            GORM_PB_Table_scene* pPbReal = dynamic_cast<GORM_PB_Table_scene*>(pMsg);
            value = pPbReal->sceneid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_SKILL:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SKILL_VERSION:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_SKILL_ROLEID:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_SKILL_SNAKEID:
        {
            GORM_PB_Table_skill* pPbReal = dynamic_cast<GORM_PB_Table_skill*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_INTERACTION:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_INTERACTION_VERSION:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_INTERACTION_ROLEID:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_INTERACTION_SNAKEID:
        {
            GORM_PB_Table_interaction* pPbReal = dynamic_cast<GORM_PB_Table_interaction*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_USER:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_USER_VERSION:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_USER_USERID:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            value = pPbReal->userid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_USER_PTTYPE:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            value = pPbReal->pttype();
            return GORM_OK;
        }
        case GORM_PB_FIELD_USER_CREATETIME:
        {
            GORM_PB_Table_user* pPbReal = dynamic_cast<GORM_PB_Table_user*>(pMsg);
            value = pPbReal->createtime();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_ROLES:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLES_VERSION:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_ROLEID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_USERID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->userid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_WORLDID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->worldid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_DBID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->dbid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_CHARID:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->charid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLES_CREATETIME:
        {
            GORM_PB_Table_roles* pPbReal = dynamic_cast<GORM_PB_Table_roles*>(pMsg);
            value = pPbReal->createtime();
            return GORM_OK;
        }
        }
    }
    }

    return GORM_ERROR;
}


}