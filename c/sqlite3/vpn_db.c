#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "sqlite3.h"
#define VPN_DB_FILEPATH "/usr/data/key.dat"

static inline int my_sqlite3_exec(char *sql)
{
    sqlite3      *sqlitedb   = NULL;
	int rc;
    int ret = -1;

	if (0 != (rc = sqlite3_open_v2(VPN_DB_FILEPATH, &sqlitedb, SQLITE_OPEN_READWRITE, NULL))) {
		printf("Can't open database: %s :%s \n", sqlite3_errmsg(sqlitedb), VPN_DB_FILEPATH);
        return -1;
	}

	if (0 != (rc = sqlite3_exec(sqlitedb, sql, NULL, NULL, NULL))) {
		printf("sqlite3_stop false: %s :%s \n", sqlite3_errmsg(sqlitedb), VPN_DB_FILEPATH);
        ret = -1;
        goto end;
    }
	
    ret = 0;
    
  end:
    sqlite3_close(sqlitedb);
    return ret;
}

typedef int my_sqlite3_query_cb(unsigned char *, unsigned char *);

int my_sqlite3_query_arg2(char *sql, my_sqlite3_query_cb *cb)
{
    sqlite3       *sqlitedb   = NULL;
    sqlite3_stmt  *sqlitestmt = NULL;
	int            rc;
    int            ret = -1;
    unsigned char *arg1  = NULL;
    unsigned char *arg2  = NULL;

	if (0 != (rc = sqlite3_open_v2(VPN_DB_FILEPATH, &sqlitedb, SQLITE_OPEN_READWRITE, NULL))) {
		printf("Can't open database: %s :%s \n", sqlite3_errmsg(sqlitedb), VPN_DB_FILEPATH);
        return -1;
	}

	if (0 != (rc = sqlite3_prepare_v2(sqlitedb, sql, strlen(sql), &sqlitestmt, NULL))) {
		printf("sqlite3_prepare_v2 false: %s :%s \n", sqlite3_errmsg(sqlitedb), VPN_DB_FILEPATH);
        ret = -1;
        goto end;
    }

    rc = sqlite3_step(sqlitestmt);
	while (rc == SQLITE_ROW) {
        arg1 = (unsigned char *)sqlite3_column_text(sqlitestmt, 0);
        arg2 = (unsigned char *)sqlite3_column_text(sqlitestmt, 1);
        if (cb) cb(arg1, arg2);
		rc = sqlite3_step(sqlitestmt);
	}
	
    sqlite3_finalize(sqlitestmt);
    ret = 0;
    
  end:
    sqlite3_close(sqlitedb);
    return ret;
}

int vpn_db_init()
{
    static char buf[1024];

    if (0 == my_sqlite3_query_arg2("select * from vpn_usr_key limit 1;", NULL)) {
        return 0; 
    }

    sprintf(buf, 
            "sqlite3 %s 'CREATE TABLE vpn_usr_key(usr STRING NOT NULL , key STRING NOT NULL , PRIMARY KEY (usr, key));'",
            VPN_DB_FILEPATH);
    if (0 != system(buf)) {
        return -1;
    }
    return 0;
}

int vpn_db_query_one_usr(unsigned char *usr, unsigned char *key)
{
    printf("usr: %s, key: %s\n", usr, key);
}

int vpn_db_insert(unsigned char *usr, unsigned char *key)
{
    static char buf[1024];

    if (strlen(usr) == 0 || strlen(key) == 0) {
        return -1;
    }

    sprintf(buf, "INSERT OR IGNORE INTO vpn_usr_key VALUES('%s','%s');", usr, key);

    return my_sqlite3_exec(buf);
}

int vpn_db_query_all()
{
	char *sql = "select * from vpn_usr_key;";
    return my_sqlite3_query_arg2(sql, vpn_db_query_one_usr);    
}

//int main()
//{
//    if (0 != vpn_db_init()) {
//        printf("vpn_db_init err.\n");
//        return -1;
//    }
//    if (0 != vpn_db_insert("usrname", "7983D8B98AD93A7E99BE4B54F4127AAB")) {
//        printf("vpn_db_insert err.\n");
//    }
//    if (0 != vpn_db_insert("usrname", "7983D8B98AD93A7E99BE4B54F4127AAB")) {
//        printf("vpn_db_insert err.\n");
//    }
//
//    vpn_db_query_all();    
//    return 0;
//}
