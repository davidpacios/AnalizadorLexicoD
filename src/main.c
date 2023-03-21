#include <stdio.h>
#include "../includes/symbolsTable.h"
#include "../includes/sintacticParser.h"

void init(TablaHash TS);
void freeMemory(TablaHash TS);


int main() {

    TablaHash TS;
    
    init(TS);

    startParser(TS);

    freeMemory(TS);
}

//Inicializar la tabla de simbolos
void init(TablaHash TS){
    initInputSystem();
    initSymbolsTable(TS);
    printf("Tabla de simbolos inicializada correctamente.\n");
}

void freeMemory(TablaHash TS){
    destroySymbolsTable(TS);
    freeMemoryInputSystem();
    printf("Memoria liberada correctamente.\n");
}
