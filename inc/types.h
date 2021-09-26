#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

/**
 * @brief States of check
 * 
 */
#define CHECK_FAILED ((uint8_t) 0u)
#define CHECK_PASSED ((uint8_t) 1u)

/**
 * @brief Type for checks
 * 
 */
typedef uint8_t bCheckStatus_t;

/**
 * @brief Type of possible operations
 * 
 */
typedef enum {
    eGET_CREDENTIALS,
    eGET_LOGIN,
    eGET_PW,
    eGET_CREDENTIALS_COUNT,
    eNEW_CREDENTIALS,
    eGET_ALL,
    eINVALID
} eOperation_T;

/**
 * @brief Type of request to DB
 * 
 */
typedef struct
{
    eOperation_T eOperation;
    char* cSite;
    char* cLogin;
    char* cPw;
} stRequest_T;

#endif /* TYPES_H */
