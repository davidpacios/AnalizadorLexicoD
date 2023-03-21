#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "../includes/hashTableRelocation.h"
#include "../includes/symbolsTable.h"

void InitHashTable(TablaHash t) {
    for (int i = 0; i < N; i++){
        t[i].stringToken = NULL;
    }
}

int hashFunction(char *key) {
    int result = 0;

    for (int i = strlen(key) - 1; i >= 0; i--) {
        result = (result * 256 + key[i]) % N;
    }

    return result;
}

int _searchPosition(TablaHash t, char *cad) {
    int position;
    int a = 1;
    int ini = hashFunction(cad);
    for (int i = 0; i < N; i++) {
        position = (ini + a * i) % N; //Recolocación Simple (a=1)

        if (t[position].stringToken == NULL) return position;

        if (!strcmp(t[position].stringToken, cad)) return position;

    }
    return ini;
}

int _insertPosition(TablaHash t, char *cad) {
    int position;
    int a = 1;
    int ini = hashFunction(cad);

    for (int i = 0; i < N; i++) {

        position = (ini + a * i) % N; //Recolocación Simple (a=1)

        if (t[position].stringToken == NULL) return position;

        if (!strcmp(t[position].stringToken, cad)) return position;
    }

    return ini;
}

int isElementOnHash(TablaHash t, char *cad) {
    int position = _searchPosition(t, cad);

    if (t[position].stringToken == NULL) return 0;

    return (!strcmp(t[position].stringToken, cad));
}

int searchHashElement(TablaHash t, char* key, token *e) {
    int position = _searchPosition(t, key);

    if (t[position].stringToken == NULL) return 0;

    if (strcmp(t[position].stringToken, key) == 0) { *e = t[position]; return 1;}

    return 0;

}

void insertHashElement(TablaHash t, token e) {
    int position = _insertPosition(t, e.stringToken);

    if (t[position].stringToken == NULL) t[position] = e;
}

void destroyHashTable(TablaHash t) {
    for (int i = 0; i < N; i++) {
        if(t[i].stringToken != NULL && t[i].codeToken == ID){
            free(t[i].stringToken);
        }
    }
}