#include <stdio.h>
#include "../includes/errorHandler.h"

char* takeMessage(int errorCode){
    switch (errorCode) {
        case ERROR_CODE:
            return "Error";
        case ERROR_INCOMPLETE_TOKEN_DUETO_BLOCKSIZE:
            return "The next token is incomplete due to the block size is not enough to contain the token.";
        default:
            return "Error";
    }
}

void errorHandler(int errorCode) {
    switch (errorCode) {
        case ERROR_CODE:
            printf("Error: %s\n", "Error");
            break;
        case ERROR_INCOMPLETE_TOKEN_DUETO_BLOCKSIZE:
            printf("Error: %s\n", takeMessage(errorCode));
            break;
        default:
            printf("Error: %s \n", "Error");
            break;
    }
}


