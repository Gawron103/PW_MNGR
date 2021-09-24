#include "argument_parser.h"
#include "types.h"

#include <stdlib.h>

#define OPERATION_INDEX 1u
#define PARAMS_START_INDEX 2u
#define LOGIN_PARAM_INDEX 3u
#define PW_PARAM_INDEX 4u
#define SITE_PARAM_INDEX 2u

#define MIN_ARGS 2u
#define MAX_ARGS 5u

/* number of parameters for each operation */
#define PARAMS_COUNT_FOR_GET_CREDENTIALS 3u
#define PARAMS_COUNT_FOR_GET_LONG 3u
#define PARAMS_COUNT_FOR_GET_PW 3u
#define PARAMS_COUNT_FOR_CREDENTIALS_NUM 2u
#define PARAMS_COUNT_FOR_NEW_CREDENTIALS 5u
#define PARAMS_COUNT_FOR_GET_ALL 2u

static eOperation_T eGetOperation(const char cOperation);
static bool checkIfProvidedReqParamsCount(const eOperation_T eOperation, const size_t uiFlagsCount);

static bool assignParamsForOperation(stRequest_T **request, char** flags, const eOperation_T eOperation);
static bool setParamsForGetCredentialsReq(stRequest_T **request, char **flags);
static bool setParamsForGetLoginReq(stRequest_T **request, char **flags);
static bool setParamsForGetPwReq(stRequest_T **request, char **flags);
static bool setParamsForGetCredentialsCountReq(stRequest_T **request, char **flags);
static bool setParamsForgetAllCredentialsReq(stRequest_T **request, char **flags);
static bool setParamsForAddCredentialsReq(stRequest_T **request, char **flags);

static char* getSiteParamVal(char** flags);
static char* getLoginParamVal(char** flags);
static char* getPwParamVal(char** flags);

bool parseArgs(const size_t uiFlagsCount, char **flags, stRequest_T **request)
{
    bool retVal = false;
    bool paramsNumCorrect = false;
    bool assignResult = false;
    eOperation_T eOperation = eNONE;
    stRequest_T *stRequest = NULL;

    /* first check if numebr of args is between correct amount */
    if(uiFlagsCount >= MIN_ARGS &&  uiFlagsCount <= MAX_ARGS) {
        /* get the requested operation */
        eOperation =  eGetOperation(*(flags[OPERATION_INDEX] + 1));

        /* check if provided required amount of params */
        paramsNumCorrect = checkIfProvidedReqParamsCount(eOperation, uiFlagsCount);

        if(true == paramsNumCorrect)
        {
            fprintf(stdout, "Provided correct amount of params\n");

            stRequest = (stRequest_T*)malloc(sizeof(stRequest_T));
            stRequest->eOperation = eOperation;

            assignResult = assignParamsForOperation(&stRequest, flags, eOperation);

            if(true == assignResult)
            {
                fprintf(stdout, "Request created correctly\n");

                // printRequest(stRequest);

                *request = stRequest;

                retVal = true;
            }
            else
            {
                fprintf(stderr, "Error creating request\n");
            }

        }
        else
        {
            fprintf(stderr, "Provided wrong number of params for this operation\n");
        }
    }

    return retVal;
}

/* TMP FUNC*/
void printRequest(stRequest_T *stRequest)
{
    printf("Request operation num: %d\n", stRequest->eOperation);

    if(NULL != stRequest->cSite)
    {
        printf("Request site: %s\n", stRequest->cSite);
    }
    
    if(NULL != stRequest->cLogin)
    {
        printf("Request login: %s\n", stRequest->cLogin);
    }

    if(NULL != stRequest->cPw)
    {
        printf("Request pw: %s\n", stRequest->cPw);
    }
}


/**
 * @brief Get the Operation object
 * 
 * @param Operation 
 * @return eOperation_T 
 */
static eOperation_T eGetOperation(const char cOperation)
{
    eOperation_T eOperation = eNONE;

    switch(cOperation)
    {
        case 'c':
            eOperation = eGET_CREDENTIALS;
        break;

        case 'l':
            eOperation = eGET_LOGIN;
        break;

        case 'p':
            eOperation = eGET_PW;
        break;

        case 's':
            eOperation = eGET_CREDENTIALS_COUNT;
        break;

        case 'n':
            eOperation = eNEW_CREDENTIALS;
        break;

        case 'a':
            eOperation = eGET_ALL;
        break;

        default:
            eOperation = eINVALID;
        break;
    }

    return eOperation;
}

/**
 * @brief Check if provided requested amount of paramaters for operation
 * 
 * @param eOperation 
 * @param uiFlagsCount 
 * @return true 
 * @return false 
 */
static bool checkIfProvidedReqParamsCount(const eOperation_T eOperation, const size_t uiFlagsCount)
{
    bool retVal = false;

    switch(eOperation)
    {
        case eGET_CREDENTIALS:
            retVal = (uiFlagsCount == PARAMS_COUNT_FOR_GET_CREDENTIALS ? true : false);
        break;

        case eGET_LOGIN:
            retVal = (uiFlagsCount == PARAMS_COUNT_FOR_GET_LONG ? true : false);
        break;

        case eGET_PW:
            retVal = (uiFlagsCount == PARAMS_COUNT_FOR_GET_PW ? true : false);
        break;

        case eGET_CREDENTIALS_COUNT:
            retVal = (uiFlagsCount == PARAMS_COUNT_FOR_CREDENTIALS_NUM ? true : false);
        break;

        case eNEW_CREDENTIALS:
            retVal = (uiFlagsCount == PARAMS_COUNT_FOR_NEW_CREDENTIALS ? true : false);
        break;

        case eGET_ALL:
            retVal = (uiFlagsCount == PARAMS_COUNT_FOR_GET_ALL ? true : false);
        break;

        default:
            /* do nothing */
        break;
    }

    return retVal;
}

static bool assignParamsForOperation(stRequest_T **request, char** flags, const eOperation_T eOperation)
{
    bool noError = false;

    switch(eOperation)
    {
        case eGET_CREDENTIALS:
            noError = setParamsForGetCredentialsReq(request, flags);
        break;

        case eGET_LOGIN:
            noError = setParamsForGetLoginReq(request, flags);
        break;

        case eGET_PW:
            noError = setParamsForGetPwReq(request, flags);
        break;

        case eGET_CREDENTIALS_COUNT:
            noError = setParamsForGetCredentialsCountReq(request, flags);
        break;

        case eNEW_CREDENTIALS:
            noError = setParamsForAddCredentialsReq(request, flags);
        break;

        case eGET_ALL:
            noError = setParamsForgetAllCredentialsReq(request, flags);
        break;

        default:
            /* do nothing */
        break;
    }

    return noError;
    // if(true != noError)
    // {
    //     fprintf(stderr, "Error assigning params to request\n");
    // }
}

static bool setParamsForGetCredentialsReq(stRequest_T **request, char** flags)
{
    bool retVal = false;

    if(NULL != *request)
    {
        (*request)->cSite = getSiteParamVal(flags);
        (*request)->cLogin = NULL;
        (*request)->cPw = NULL;
        retVal = true;
    }

    return retVal;
}

static bool setParamsForGetLoginReq(stRequest_T **request, char** flags)
{
    bool retVal = false;

    if(NULL != *request)
    {
        (*request)->cSite = getSiteParamVal(flags);
        (*request)->cLogin = NULL;
        (*request)->cPw = NULL;
        retVal = true;
    }

    return retVal;
}

static bool setParamsForGetPwReq(stRequest_T **request, char** flags)
{
    bool retVal = false;

    if(NULL != *request)
    {
        (*request)->cSite = getSiteParamVal(flags);
        (*request)->cLogin = NULL;
        (*request)->cPw = NULL;
        retVal = true;
    }

    return retVal;
}

static bool setParamsForGetCredentialsCountReq(stRequest_T **request, char** flags)
{
    bool retVal = false;

    if(NULL != *request)
    {
        (*request)->cSite = NULL;
        (*request)->cLogin = NULL;
        (*request)->cPw = NULL;
        retVal = true;
    }

    return retVal;
}

static bool setParamsForgetAllCredentialsReq(stRequest_T **request, char** flags)
{
    bool retVal = false;

    if(NULL != *request)
    {
        (*request)->cSite = NULL;
        (*request)->cLogin = NULL;
        (*request)->cPw = NULL;
        retVal = true;
    }

    return retVal;
}

static bool setParamsForAddCredentialsReq(stRequest_T **request, char** flags)
{
    bool retVal = false;

    if(NULL != *request)
    {
        (*request)->cSite = getSiteParamVal(flags);
        (*request)->cLogin = getLoginParamVal(flags);
        (*request)->cPw = getPwParamVal(flags);
        retVal = true;
    }

    return retVal;
}

static char* getSiteParamVal(char** flags)
{
    return flags[SITE_PARAM_INDEX];
}

static char* getLoginParamVal(char** flags)
{
    return flags[LOGIN_PARAM_INDEX];
}

static char* getPwParamVal(char** flags)
{
    return flags[PW_PARAM_INDEX];
}
