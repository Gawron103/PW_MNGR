#include <stdio.h>
#include <sqlite3.h>

#include "db_handler.h"

int main() {
    const DB_STATUS init_result = db_handler_init();

    if(DB_OK == init_result)
    {
        printf("Connection with DB established\n");
    }
    else
    {
        printf("Cannot establish connection with DB\n");
    }

    (void)db_handler_deinit();
}
