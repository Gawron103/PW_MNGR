#include <stdio.h>
#include <stdint.h>
#include <sqlite3.h>

#include "db_handler.h"
#include "argument_parser.h"
#include "types.h"

int main(int argc, char **argv) {
    stRequest_T *stRequest = NULL;
    DB_STATUS bDbConnectionStatus = DB_NOT_OK;
    DB_STATUS bDbRequestExecResult = DB_NOT_OK;
    bool parseResult = false;

    parseResult = bParseArgs((uint8_t)argc, argv, &stRequest);

    if(true == parseResult && NULL != stRequest) {
        fprintf(stdout, "Parsing done correctly\n");
        fprintf(stdout, "Request NOT null\n");

        // Init DB connection
        bDbConnectionStatus = db_handler_init();

        if(DB_OK == bDbConnectionStatus) {
            fprintf(stdout, "Connected to DB\n");
            // perform_request(stRequest);
            bDbRequestExecResult = db_execute_request(stRequest);

            if(DB_NOT_OK == bDbRequestExecResult)
            {
                fprintf(stderr, "DB operation NOT successful\n");
            }

            bDbConnectionStatus = db_handler_deinit();

            if(DB_OK == bDbConnectionStatus) {
                fprintf(stdout, "DB connection closed\n");
            }
        }
        else {
            fprintf(stderr, "Cannot connect to DB\n");
        }
    }
    else
    {
        fprintf(stderr, "Parsing failed\n");
    }
}
