#include <stdio.h>
#include <stdlib.h>
#include "../includes/sintacticParser.h"

void startParser(TablaHash TS){
    short indexStack = 0;
    token tokenAux;
    tokenAux.stringToken = (char *) malloc (sizeof(char) * BUFFER_SIZE);
    sendTokenToParser(TS, &tokenAux);

    while (tokenAux.codeToken != EOF){
        indexStack++;

        printf("<%s, %d>\n", tokenAux.stringToken, tokenAux.codeToken);

        sendTokenToParser(TS, &tokenAux);
    }

    free (tokenAux.stringToken);

    printf("Fin del analisis sintactico.\n");
}
