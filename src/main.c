#include <stdio.h>
#include <stdint.h>
#include <sqlite3.h>

#include "db_handler.h"
#include "argument_parser.h"
#include "types.h"

int main(int argc, char **argv) {
    stRequest_T *stRequest = NULL;
    bool parseResult = false;

    parseResult = bParseArgs((uint8_t)argc, argv, &stRequest);

    if(true == parseResult) {
        fprintf(stdout, "Parsing done correctly\n");
        printRequest(stRequest);
    }
    else
    {
        fprintf(stderr, "Parsing failed\n");
    }

    // const bool status = validate_input(argc, argv);

    // const DB_STATUS init_result = db_handler_init();

    // if(DB_OK == init_result)
    // {
    //     printf("Connection with DB established\n");
    // }
    // else
    // {
    //     printf("Cannot establish connection with DB\n");
    // }

    // (void)db_handler_deinit();
}
