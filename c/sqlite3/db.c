#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "sqlite3.h"

#define VPN_DB_FILEPATH "/usr/data/key.dat"

static void sqlite_insert();
//static void sqlite_query();

static void sqlite_query_all()
{
    sqlite3			*sqlitedb = NULL;
    sqlite3_stmt	*sqlitestmt = NULL;

	int rc = sqlite3_open_v2(VPN_DB_FILEPATH, &sqlitedb, SQLITE_OPEN_READWRITE, NULL);
	if (rc)
	{
		//LogErr("Can't open database: %s :%s \n", sqlite3_errmsg(s_sqlitedb),DBFile);
		//sqlite3_close(s_sqlitedb);

		//不存在则生成空数据库表
		//CreateDB(DBFile);
		//sqlite3_open_v2(DBFile, &s_sqlitedb, SQLITE_OPEN_READWRITE,NULL);	
	}

	//insert map
	const char *sql = "select * from r_mme_s11_s1_ip";
	sqlite3_prepare_v2(sqlitedb, sql, strlen(sql), &sqlitestmt, NULL);
	rc = sqlite3_step(sqlitestmt);

	while(rc == SQLITE_ROW)
	{
		//key = mme_s1
        unsigned char *usr  = sqlite3_column_text(sqlitestmt, 0);
        unsigned char *key  = sqlite3_column_text(sqlitestmt, 1);

		rc = sqlite3_step(sqlitestmt);
		//if (count%1000 == 0)
		//{
		//	USLEEP(10);
		//}
	}
	sqlite3_finalize(sqlitestmt);
	//LogGroup(LOG_BASE,"load mme_s11_s1_ip completed.Total:%d\n",count);
}

int main()
{
    sqlite_query_all();    
    return 0;
}
