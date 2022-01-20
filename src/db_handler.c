#include <sqlite3.h>
#include <stdbool.h>

#include "db_handler.h"

/* global objects */
static sqlite3 *stDb = NULL;

static DB_STATUS insert_credentials(char* site, char* login, char* pw, sqlite3_stmt **stmt);
static char* get_password();
static char* get_login();
static DB_STATUS get_num_of_entries(int* iCount);
static DB_STATUS get_credentials_for(char* site, char* login, char* pw, sqlite3_stmt **stmt);
static DB_STATUS get_all_credentials();

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

DB_STATUS db_execute_request(const stRequest_T* stRequest) {
    DB_STATUS bOperationResult = DB_NOT_OK;
    DB_STATUS bExecutionResult = DB_NOT_OK;
    int iRowsCount = 0;
    sqlite3_stmt *stmt = NULL;

    switch(stRequest->eOperation) {
        case eGET_CREDENTIALS:
        {
            fprintf(stdout, "Get credential\n");
            fprintf(stdout, "For site: %s\n", stRequest->cSite);
            bExecutionResult = get_credentials_for(stRequest->cSite, stRequest->cLogin, stRequest->cPw, &stmt);
        }
        break;

        case eGET_LOGIN:
        {
            fprintf(stdout, "Get login\n");
            fprintf(stdout, "For site: %s\n", stRequest->cSite);
            bExecutionResult = get_login();
        }
        break;

        case eGET_PW:
        {
            fprintf(stdout, "Get pw\n");
            fprintf(stdout, "For site: %s\n", stRequest->cSite);
            bExecutionResult = get_password();
        }
        break;

        case eGET_CREDENTIALS_COUNT:
        {
            fprintf(stdout, "Get number of credentials\n");
            bOperationResult = get_num_of_entries(&iRowsCount);
        }
        break;

        case eNEW_CREDENTIALS:
        {
            fprintf(stdout, "Add new credentials\n");
            fprintf(stdout, "For site: %s\n", stRequest->cSite);
            fprintf(stdout, "Login: %s\n", stRequest->cLogin);
            fprintf(stdout, "Pw: %s\n", stRequest->cPw);
            bOperationResult = insert_credentials(stRequest->cSite, stRequest->cLogin, stRequest->cPw, &stmt);
        }
        break;

        case eGET_ALL:
        {
            fprintf(stdout, "Get all credentials\n");
            bExecutionResult = get_all_credentials();
        }
        break;

        case eINVALID:
        {
            fprintf(stdout, "Invalid\n");
        }

        default:
        {
            fprintf(stdout, "Default\n");
        }
    }

    if(bOperationResult)
    {
        bExecutionResult = sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        fprintf(stdout, "Executed DB statement\n");
    }
    else
    {
        const char* cErrorMsg = sqlite3_errmsg(stDb);
        fprintf(stdout, "DB statement not executed. Error: %s\n", cErrorMsg);
    }

    return bExecutionResult;
}

static DB_STATUS insert_credentials(char* site, char* login, char* pw, sqlite3_stmt **stmt)
{
    DB_STATUS bResult = DB_NOT_OK;

    if(!sqlite3_prepare_v2(stDb, "INSERT INTO credential VALUES (?, ?, ?)", -1, stmt, NULL)) {
        sqlite3_bind_text(*stmt, 1, site, -1, NULL);
        sqlite3_bind_text(*stmt, 2, login, -1, NULL);
        sqlite3_bind_text(*stmt, 3, pw, -1, NULL);
        fprintf(stderr, "Insert sql statement prepared\n");
        bResult = DB_OK;
    }

    return bResult;
}

static char* get_password()
{
    // TODO: implement body
    return NULL;
}

static char* get_login()
{
    // TODO: implement body
    return NULL;
}

static DB_STATUS get_num_of_entries(int* iCount)
{
    // TODO: implement body
    return DB_NOT_OK;
}

static DB_STATUS get_credentials_for(char* site, char* login, char* pw, sqlite3_stmt **stmt)
{
    // TODO: implement body
    return DB_NOT_OK;
}

static DB_STATUS get_all_credentials()
{
    // TODO: implement body
    return DB_NOT_OK;
}
