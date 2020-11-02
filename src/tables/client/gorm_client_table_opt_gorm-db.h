#ifndef _GORM_CLIENT_TABLE_OPT_GORM-DB_H__
#define _GORM_CLIENT_TABLE_OPT_GORM-DB_H__"
#include "gorm-db.pb.h"

class GORM_ClientTableDefCurrency
{
public:
	static GORM_ClientTableDefCurrency* Get(int64 roleid);
	static int Get(int64 roleid, int64 &cbId, int (*cb)(int64));
	int Delete(int (*cb)(int64));
	void RemoveFromLocal();
	GORM_PB_Table_currency *GetPbMsg();
	uint64 GetVersion();
	void SetVersion(uint64 version);
	int32 GetRoleid();
	void SetRoleid(int32 roleid);
	int32 GetSnakeid();
	void SetSnakeid(int32 snakeid);
	string &GetCurrency1();
	void SetCurrency1(string &currency1);
	void SetCurrency1(string &&currency1);
	void SetCurrency1(const char* currency1_value);
	void SetCurrency1(const char* currency1_value, size_t size);
	string &GetCurrency2();
	void SetCurrency2(string &currency1);
	string &GetCurrency3();
	void SetCurrency3(string &currency1);
	string &GetCurrency4();
	void SetCurrency4(string &currency1);
private:
	GORM_PB_Table_currency *pTablePbValue;
};

inline uint64 GetVersion()
{
	return this->pTablePbValue->version();
}
inline void SetVersion(uint64 version)
{
	this->pTablePbValue->set_version(version);
	return;
}
inline int32 GetRoleid();
inline void SetRoleid(int32 roleid);
inline int32 GetSnakeid();
inline void SetSnakeid(int32 snakeid);
inline string &GetCurrency1();
inline void SetCurrency1(string &currency1);
inline void SetCurrency1(string &&currency1);
inline void SetCurrency1(const char* currency1_value);
inline void SetCurrency1(const char* currency1_value, size_t size);
inline string &GetCurrency2();
inline void SetCurrency2(string &currency1);
inline string &GetCurrency3();
inline void SetCurrency3(string &currency1);
inline string &GetCurrency4();
inline void SetCurrency4(string &currency1);
	
#endif
