#ifndef DB_HANDLER_H
#define DB_HANDLER_H

#include <stdbool.h>
#include <stdio.h>

#include "types.h"

/* typedefs */
typedef bool DB_STATUS;

/* Statuses of operations on database */
#define DB_OK     ((DB_STATUS) true)
#define DB_NOT_OK ((DB_STATUS) false)

bool db_handler_init();
bool db_handler_deinit();
DB_STATUS db_execute_request(const stRequest_T* stRequest);

#endif /* DB_HANDLER_H */
