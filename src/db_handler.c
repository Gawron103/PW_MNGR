#include "db_handler.h"

#include <sqlite3.h>

/* global objects */
static sqlite3 *stDb = NULL;

/**
 * @brief Enables connection with database
 * 
 * @return DB_STATUS - DB_OK when connection has been established
 *                     DB_NOT_OK when connection has been not established
 */
DB_STATUS db_handler_init()
{
    const int iOpenCode = sqlite3_open_v2("file:../db/CredentialsDB.db", &stDb, SQLITE_OPEN_READWRITE, NULL);
    DB_STATUS bStatus = DB_NOT_OK;

    if(SQLITE_OK == iOpenCode)
    {
        fprintf(stdout, "Connected to database\n");
        bStatus = DB_OK;
    }
    else
    {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(stDb));
        sqlite3_close_v2(stDb);
    }

    return bStatus;
}

/**
 * @brief Closes the connection with database
 * 
 * @return DB_STATUS - DB_OK when connection with database has been closed
 *                     DB_NOT_OK when cannot close the connection with database
 */
DB_STATUS db_handler_deinit()
{
    const int iCloseCode = sqlite3_close_v2(stDb);
    DB_STATUS bStatus = DB_NOT_OK;

    if(SQLITE_OK == iCloseCode)
    {
        fprintf(stdout, "Connection with database closed\n");
        bStatus = DB_OK;
    }
    else
    {
        fprintf(stderr, "Cannot close connection with database: %s\n", sqlite3_errmsg(stDb));
    }

    return bStatus;
}

DB_STATUS insert_credentials(char* site, char* login, char* pw)
{
    // TODO: implement body
    return true;
}

char* get_password()
{
    // TODO: implement body
    return NULL;
}

char* get_username()
{
    // TODO: implement body
    return NULL;
}

size_t get_num_of_entries()
{
    // TODO: implement body
    return 0u;
}

void get_credentials_for(char* site, char* login, char* pw)
{
    // TODO: implement body
}
