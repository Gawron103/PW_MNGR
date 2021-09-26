#ifndef TYPES_H
#define TYPES_H

typedef enum {
    eGET_CREDENTIALS,
    eGET_LOGIN,
    eGET_PW,
    eGET_CREDENTIALS_COUNT,
    eNEW_CREDENTIALS,
    eGET_ALL,
    eINVALID
} eOperation_T;

typedef struct
{
    eOperation_T eOperation;
    char* cSite;
    char* cLogin;
    char* cPw;
} stRequest_T;

#endif /* TYPES_H */