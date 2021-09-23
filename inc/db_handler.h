#ifndef DB_HANDLER_H
#define DB_HANDLER_H

#include <stdbool.h>
#include <stdio.h>

/* typedefs */
typedef bool DB_STATUS;

/* Statuses of operations on database */
#define DB_OK     ((DB_STATUS) true)
#define DB_NOT_OK ((DB_STATUS) false)

bool db_handler_init();
bool db_handler_deinit();
bool insert_credentials(char* site, char* login, char* pw);
char* get_password();
char* get_username();
size_t get_num_of_entries();
void get_credentials_for(char* site, char* login, char* pw);

#endif /* DB_HANDLER_H */
