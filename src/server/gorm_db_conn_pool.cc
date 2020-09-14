#include "gorm_db_conn_pool.h"

GORM_DBConnPool::GORM_DBConnPool(int iMaxPool):m_iMaxPoolSize(iMaxPool)
{
}

GORM_DBConnPool::~GORM_DBConnPool()
{
}

UrlInfo::UrlInfo(char *host, char *user, char *pw, int port, char *dbName, bool supportTransactions)
    :supportTransactions(supportTransactions), url(""), hashcode(0)
{
    strncpy(this->host, host, NET_IP_STR_LEN);
    strncpy(this->user, user, GORM_DB_USER_MAX_LEN);
    strncpy(this->passwd, pw, GORM_DB_PW_MAX_LEN);
    this->port = port;
    strncpy(this->dbName, dbName, GORM_DB_MAX_LEN);
}

UrlInfo::UrlInfo(const unsigned int hashcode,const std::string &url, bool supportTransactions)
		: hashcode(hashcode),url(url),supportTransactions(supportTransactions)
{
	parseMySQLURLString();
}

UrlInfo::UrlInfo(const UrlInfo &ui)
: hashcode(ui.hashcode),url(ui.url),supportTransactions(ui.supportTransactions)
{
    parseMySQLURLString();
}
                

void UrlInfo::parseMySQLURLString()
{
	bzero(host,sizeof(host));
	bzero(user,sizeof(user));
	bzero(passwd,sizeof(passwd));
	port=3306;
	bzero(dbName,sizeof(dbName));

	char strPort[16] = "";
	int  j, k;
	size_t i;
	const char *connString = url.c_str();
	if (0 == strncmp(connString, "mysql://", strlen("mysql://")))
	{
		i = 0; j = 0; k = 0;
		for(i = strlen("mysql://"); i < strlen(connString) + 1; i++)
		{
			switch(j)
			{
				case 0:
					if (connString[i] == ':')
					{
						user[k] = '\0'; j++; k = 0;
					}
					else
						user[k++] = connString[i];
					break;
				case 1:
					if (k >= GORM_DB_PW_MAX_LEN)
					{
					    cout << "mysql password is too long" << endl;
						//Fir::logger->error("mysql password is too long");
					}
					else
					{
						if (connString[i] == '@')
						{
							passwd[k] = '\0'; j++; k = 0;
						}
						else
							passwd[k++] = connString[i];
					}
					break;
				case 2:
					if (connString[i] == ':')
					{
						host[k] = '\0'; j++; k = 0;
					}
					else
						host[k++] = connString[i];
					break;
				case 3:
					if (connString[i] == '/')
					{
						strPort[k] = '\0'; j++; k = 0;
					}
					else
						strPort[k++] = connString[i];
					break;
				case 4:
					if (connString[i] == '\0')
					{
						dbName[k] = '\0'; j++; k = 0;
					}
					else
						dbName[k++] = connString[i];
					break;
				default:
					break;
			}
		}
	}
	port=atoi(strPort);
}


