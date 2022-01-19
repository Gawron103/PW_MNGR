#include <stdio.h>

#include "request_handler.h"

void perform_request(const stRequest_T* stRequest) {
    switch(stRequest->eOperation) {
        case eGET_CREDENTIALS: {
            fprintf(stdout, "Get credential\n");
            fprintf(stdout, "For site: %s\n", stRequest->cSite);
        }
        break;

        case eGET_LOGIN: {
            fprintf(stdout, "Get login\n");
            fprintf(stdout, "For site: %s\n", stRequest->cSite);
        }
        break;

        case eGET_PW: {
            fprintf(stdout, "Get pw\n");
            fprintf(stdout, "For site: %s\n", stRequest->cSite);
        }
        break;

        case eGET_CREDENTIALS_COUNT: {
            fprintf(stdout, "Get number of credentials\n");
        }
        break;

        case eNEW_CREDENTIALS: {
            fprintf(stdout, "Add new credentials\n");
            fprintf(stdout, "For site: %s\n", stRequest->cSite);
            fprintf(stdout, "Login: %s\n", stRequest->cLogin);
            fprintf(stdout, "Pw: %s\n", stRequest->cPw);
        }
        break;

        case eGET_ALL: {
            fprintf(stdout, "Get all credentials\n");
        }
        break;

        case eINVALID: {
            fprintf(stdout, "Invalid\n");
        }

        default: {
            fprintf(stdout, "Default\n");
        }
    }
}
