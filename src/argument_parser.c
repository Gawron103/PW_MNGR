#include <stdlib.h>

#include "argument_parser.h"
#include "types.h"

/**
 * @brief Type for checking if number of provided
 *        paremeters is correct
 * 
 */
typedef bool bCheckStatus_t;

/**
 * @brief States of check
 * 
 */
#define CHECK_FAILED ((uint8_t) 0u)
#define CHECK_PASSED ((uint8_t) 1u)

/**
 * @brief States of parse
 * 
 */
#define PARSE_NOT_OK ((uint8_t) 0u)
#define PARSE_OK     ((uint8_t) 1u)

/**
 * @brief Range of needed input parameters
 * 
 */
#define MIN_ARGS ((uint8_t) 2u)
#define MAX_ARGS ((uint8_t) 5u)

/**
 * @brief Positions of parameters in input array
 * 
 */
#define OPERATION_INDEX    ((uint8_t) 1u)
#define PARAMS_START_INDEX ((uint8_t) 2u)
#define SITE_PARAM_INDEX   ((uint8_t) 2u)
#define LOGIN_PARAM_INDEX  ((uint8_t) 3u)
#define PW_PARAM_INDEX     ((uint8_t) 4u)

/**
 * @brief Flags for possible operations
 * 
 */
#define FLAG_GET_CREDENTIALS       ((char) 'c')
#define FLAG_GET_LOGIN             ((char) 'l')
#define FLAG_GET_PW                ((char) 'p')
#define FLAG_GET_CREDENTIALS_COUNT ((char) 's')
#define FLAG_ADD_CREDENTIALS       ((char) 'n')
#define FLAG_GET_ALL_CREDENTIALS   ((char) 'a')

/**
 * @brief Number of needed parameters for each operation
 * 
 */
#define PARAMS_COUNT_FOR_GET_CREDENTIALS ((uint8_t) 3u)
#define PARAMS_COUNT_FOR_GET_LONG        ((uint8_t) 3u)
#define PARAMS_COUNT_FOR_GET_PW          ((uint8_t) 3u)
#define PARAMS_COUNT_FOR_CREDENTIALS_NUM ((uint8_t) 2u)
#define PARAMS_COUNT_FOR_NEW_CREDENTIALS ((uint8_t) 5u)
#define PARAMS_COUNT_FOR_GET_ALL         ((uint8_t) 2u)

/* Prototypes section */
static eOperation_T eGetOperation(const char cOperation);
static bCheckStatus_t bCheckIfProvidedReqParamsCount(const eOperation_T eOperation, const uint8_t u8FlagsCount);
static void vSetParamsForOperation(stRequest_T** stRequest, char** cFlags, const eOperation_T eOperation);
static void vSetParamsForGetCredentialsReq(stRequest_T** stRequest, char** cFlags);
static void vSetParamsForGetLoginReq(stRequest_T** stRequest, char** cFlags);
static void vSetParamsForGetPwReq(stRequest_T** stRequest, char** cFlags);
static void vSetParamsForGetCredentialsCountReq(stRequest_T** stRequest);
static void vSetParamsForGetAllCredentialsReq(stRequest_T** stRequest);
static void vSetParamsForAddCredentialsReq(stRequest_T** stRequest, char** cFlags);
static char* cGetSiteParamVal(char** cFlags);
static char* cGetLoginParamVal(char** cFlags);
static char* cGetPwParamVal(char** cFlags);
static void vShowHelp();

/**
 * @brief Parses input from user
 * 
 * @param u8FlagsCount -> number of parameters
 * @param cFlags -> array of input parameters
 * @param stOutRequest -> output pointer for request
 * @return bParseStatus_t -> is parsing successful
 */
bParseStatus_t bParseArgs(const uint8_t u8FlagsCount, char** cFlags, stRequest_T** stOutRequest)
{
    bParseStatus_t bParseStatus = PARSE_NOT_OK;
    bCheckStatus_t bParamsNumCorrect = CHECK_FAILED;
    eOperation_T eOperation = eINVALID;
    stRequest_T *stRequest = NULL;

    /* check if numebr of args is between correct amount */
    if(u8FlagsCount >= MIN_ARGS &&  u8FlagsCount <= MAX_ARGS) {
        /* get the requested operation */
        eOperation =  eGetOperation(*(cFlags[OPERATION_INDEX] + 1u));

        /* check if number of passed params is correct for requested operation */
        bParamsNumCorrect = bCheckIfProvidedReqParamsCount(eOperation, u8FlagsCount);

        if(CHECK_PASSED == bParamsNumCorrect)
        {
            fprintf(stdout, "Provided correct amount of params\n");

            stRequest = (stRequest_T*)malloc(sizeof(stRequest_T));

            /* check if memory has been allocated */
            if(NULL != stRequest)
            {
                stRequest->eOperation = eOperation;

                /* fill request with passed parameters */
                vSetParamsForOperation(&stRequest, cFlags, eOperation);

                /* returning request */
                *stOutRequest = stRequest;
                /* provided input is correct */
                bParseStatus = PARSE_OK;
            }
            else
            {
                fprintf(stderr, "Malloc failed\n");
            }
        }
        else
        {
            /* print help here */
            fprintf(stderr, "Provided wrong number of params for this operation\n");
        }
    }
    else
    {
        /* print help here */
        fprintf(stderr, "Wrong number of params\n");
    }

    return bParseStatus;
}

/* TMP FUNC*/
void printRequest(stRequest_T* stRequest)
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
 * @brief Get the requested operation
 * 
 * @param Operation -> input from parameters
 * @return eOperation_T -> type of operation
 */
static eOperation_T eGetOperation(const char cOperation)
{
    eOperation_T eOperation = eINVALID;

    switch(cOperation)
    {
        case FLAG_GET_CREDENTIALS:
            eOperation = eGET_CREDENTIALS;
        break;

        case FLAG_GET_LOGIN:
            eOperation = eGET_LOGIN;
        break;

        case FLAG_GET_PW:
            eOperation = eGET_PW;
        break;

        case FLAG_GET_CREDENTIALS_COUNT:
            eOperation = eGET_CREDENTIALS_COUNT;
        break;

        case FLAG_ADD_CREDENTIALS:
            eOperation = eNEW_CREDENTIALS;
        break;

        case FLAG_GET_ALL_CREDENTIALS:
            eOperation = eGET_ALL;
        break;

        default:
            /* do nothing */
        break;
    }

    return eOperation;
}

/**
 * @brief Check if provided requested amount of paramaters for operation
 * 
 * @param eOperation -> requested operation
 * @param uiFlagsCount -> number of passed parameters
 * @return true -> number of parameters is correct
 * @return false -> number of parameters is not correct
 */
static bCheckStatus_t bCheckIfProvidedReqParamsCount(const eOperation_T eOperation, const uint8_t u8FlagsCount)
{
    bCheckStatus_t bCheckStatus = CHECK_FAILED;

    switch(eOperation)
    {
        case eGET_CREDENTIALS:
            bCheckStatus = (u8FlagsCount == PARAMS_COUNT_FOR_GET_CREDENTIALS ? CHECK_PASSED : CHECK_FAILED);
        break;

        case eGET_LOGIN:
            bCheckStatus = (u8FlagsCount == PARAMS_COUNT_FOR_GET_LONG ? CHECK_PASSED : CHECK_FAILED);
        break;

        case eGET_PW:
            bCheckStatus = (u8FlagsCount == PARAMS_COUNT_FOR_GET_PW ? CHECK_PASSED : CHECK_FAILED);
        break;

        case eGET_CREDENTIALS_COUNT:
            bCheckStatus = (u8FlagsCount == PARAMS_COUNT_FOR_CREDENTIALS_NUM ? CHECK_PASSED : CHECK_FAILED);
        break;

        case eNEW_CREDENTIALS:
            bCheckStatus = (u8FlagsCount == PARAMS_COUNT_FOR_NEW_CREDENTIALS ? CHECK_PASSED : CHECK_FAILED);
        break;

        case eGET_ALL:
            bCheckStatus = (u8FlagsCount == PARAMS_COUNT_FOR_GET_ALL ? CHECK_PASSED : CHECK_FAILED);
        break;

        default:
            /* do nothing */
        break;
    }

    return bCheckStatus;
}

/**
 * @brief Set the values in request for wanted operation
 * 
 * @param request -> struct that holds necessary data for wanted request.
 *                   At this stage it is ensured that pointer is not NULL,
 *                   no need to do any additional checks
 * @param cFlags -> array of input parameters
 * @param eOperation -> requested operation
 */
static void vSetParamsForOperation(stRequest_T** stRequest, char** cFlags, const eOperation_T eOperation)
{
    switch(eOperation)
    {
        case eGET_CREDENTIALS:
            vSetParamsForGetCredentialsReq(stRequest, cFlags);
        break;

        case eGET_LOGIN:
            vSetParamsForGetLoginReq(stRequest, cFlags);
        break;

        case eGET_PW:
            vSetParamsForGetPwReq(stRequest, cFlags);
        break;

        case eGET_CREDENTIALS_COUNT:
            vSetParamsForGetCredentialsCountReq(stRequest);
        break;

        case eNEW_CREDENTIALS:
            vSetParamsForAddCredentialsReq(stRequest, cFlags);
        break;

        case eGET_ALL:
            vSetParamsForGetAllCredentialsReq(stRequest);
        break;

        default:
            /* do nothing */
        break;
    }
}

/**
 * @brief Set the values in request for getting credentials for specific site
 * 
 * @param request -> struct that holds necessary data for wanted request
 * @param cFlags -> array of input parameters
 */
static void vSetParamsForGetCredentialsReq(stRequest_T** stRequest, char** cFlags)
{
    (*stRequest)->cSite = cGetSiteParamVal(cFlags);
    (*stRequest)->cLogin = NULL;
    (*stRequest)->cPw = NULL;
}

/**
 * @brief Set the values in request for getting login for specific site
 * 
 * @param request -> struct that holds necessary data for wanted request
 * @param cFlags -> array of input parameters
 */
static void vSetParamsForGetLoginReq(stRequest_T** stRequest, char** cFlags)
{
    (*stRequest)->cSite = cGetSiteParamVal(cFlags);
    (*stRequest)->cLogin = NULL;
    (*stRequest)->cPw = NULL;
}

/**
 * @brief Set the values in request for getting password for specific site
 * 
 * @param request -> struct that holds necessary data for wanted request
 * @param cFlags -> array of input parameters
 */
static void vSetParamsForGetPwReq(stRequest_T** stRequest, char** cFlags)
{
    (*stRequest)->cSite = cGetSiteParamVal(cFlags);
    (*stRequest)->cLogin = NULL;
    (*stRequest)->cPw = NULL;
}

/**
 * @brief Set the values in request for getting the number of saved credentials
 * 
 * @param request -> struct that holds necessary data for wanted request
 * @param cFlags -> array of input parameters
 */
static void vSetParamsForGetCredentialsCountReq(stRequest_T** stRequest)
{
    (*stRequest)->cSite = NULL;
    (*stRequest)->cLogin = NULL;
    (*stRequest)->cPw = NULL;
}

/**
 * @brief Set the values in request for getting all credentials
 * 
 * @param request -> struct that holds necessary data for wanted request
 * @param cFlags -> array of input parameters
 */
static void vSetParamsForGetAllCredentialsReq(stRequest_T** stRequest)
{
    (*stRequest)->cSite = NULL;
    (*stRequest)->cLogin = NULL;
    (*stRequest)->cPw = NULL;
}

/**
 * @brief Set the values in request for adding new credentials operation
 * 
 * @param request -> struct that holds necessary data for wanted request
 * @param cFlags -> array of input parameters
 */
static void vSetParamsForAddCredentialsReq(stRequest_T** stRequest, char** cFlags)
{
    (*stRequest)->cSite = cGetSiteParamVal(cFlags);
    (*stRequest)->cLogin = cGetLoginParamVal(cFlags);
    (*stRequest)->cPw = cGetPwParamVal(cFlags);
}

/**
 * @brief Get the value of site from provided parameters
 * 
 * @param cFlags -> array of input parameters
 * @return char* -> provided site
 */
static char* cGetSiteParamVal(char** cFlags)
{
    return cFlags[SITE_PARAM_INDEX];
}

/**
 * @brief Get the value of login from provided parameters
 * 
 * @param cFlags -> array of input parameters
 * @return char* -> provided login
 */
static char* cGetLoginParamVal(char** cFlags)
{
    return cFlags[LOGIN_PARAM_INDEX];
}

/**
 * @brief Get the value of password from provided parameters
 * 
 * @param cFlags -> array of input parameters
 * @return char* -> provided password
 */
static char* cGetPwParamVal(char** cFlags)
{
    return cFlags[PW_PARAM_INDEX];
}

static void vShowHelp()
{
    fprintf(stderr, "");
}
