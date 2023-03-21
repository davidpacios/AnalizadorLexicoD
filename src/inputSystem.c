#include <bits/types/FILE.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../includes/inputSystem.h"

FILE *fileInput;

struct cacheSystem{
    char buffer[BUFFER_SIZE];
    char *initialPosition;
    char *actualPosition;
};

struct cacheSystem cache;

int sizeBlockError = 0;

/*************************************************************
 * Funciones para la inicialización del sistema de entrada.
 *************************************************************/

void initBuffer(){
    printf("Reserva de memoria para el buffer\n");

    for(int i = 0; i < BLOCK_SIZE * 2 + 2; i++){
        if(i == BLOCK_SIZE || i == (BLOCK_SIZE * 2) + 1){
            cache.buffer[i] = EOF;
        }
    }

    cache.initialPosition = cache.buffer;
    cache.actualPosition = cache.buffer;

    fread(cache.buffer, sizeof(char), BLOCK_SIZE, fileInput);
}

void initInputSystem(){
    fileInput = fopen(FILENAME, "r");
    if(fileInput == NULL){
        printf("Error al abrir el archivo de entrada.\n");
        exit(1);
    }
    initBuffer();
}

/*************************************************************
 * Funciones para manejo de punteros del buffer.
 *************************************************************/

void updateInitialPosition(){
    cache.initialPosition = cache.actualPosition;
    sizeBlockError = 0;
}

void backActualPosition(){
    cache.actualPosition--;
}

int whatBlockIs(const char* pointer){
    if(pointer <= cache.buffer + BLOCK_SIZE){
        return 0;
    }
    return 1;
}


/*************************************************************
 * Funciones para la lectura del buffer.
 *************************************************************/

void takeWord(char* buffer,long size){
    int i = 0;
    while(cache.initialPosition != cache.actualPosition){
        if(cache.initialPosition == (cache.buffer + BLOCK_SIZE)){
            cache.initialPosition++;
            continue;
        }
        if(cache.initialPosition == cache.buffer + (BLOCK_SIZE * 2) + 1){
            cache.initialPosition = cache.buffer;
            continue;
        }
        *(buffer+i) = *cache.initialPosition;
        cache.initialPosition++;
        i++;
    }

    buffer[size] = '\0';

    if(sizeBlockError) errorHandler(ERROR_INCOMPLETE_TOKEN_DUETO_BLOCKSIZE);

}

void takeWordBetweenInitialPositionAndActualPosition(char *buffer){

    //Si inicial es mayor que actual.
    if(cache.initialPosition > cache.actualPosition){
        long size = (cache.buffer + BUFFER_SIZE) - cache.initialPosition;
        size += cache.actualPosition - cache.buffer - abs(whatBlockIs(cache.actualPosition) -
                                                          whatBlockIs(cache.initialPosition)); //Para que no cuente los EOF.
        takeWord(buffer,size);
        return;
    }

    //Si inicial es menor que actual.
    if(cache.initialPosition < cache.actualPosition){
        takeWord(buffer,cache.actualPosition - cache.initialPosition - abs(whatBlockIs(cache.actualPosition) -
                                                                          whatBlockIs(cache.initialPosition)));
        return;
    }

}

unsigned int loadBlock(int block){
    char* position = cache.buffer + block*(BLOCK_SIZE + 1);
    unsigned int finalCharacters = fread(position, sizeof(char), BLOCK_SIZE, fileInput);
    cache.actualPosition = position;
    if(whatBlockIs(cache.initialPosition) == block) sizeBlockError = 1;
    return finalCharacters;
}

char nextChar(){
    unsigned int finalCharacters;
    char c = *cache.actualPosition; //Leo el caracter actual.
    int block = whatBlockIs(cache.actualPosition);
    cache.actualPosition++;

    //Compara en que bloque estoy
    if(c == EOF){//
        //Si leo EOF estoy en la posicion de EOF y en el siguiente bloque --> Si estoy en el bloque 1, leo el bloque 2...
        //Lo mismo que .cache.buffer + BLOCK_SIZE + 1 ||cache.actualPosition == cache.buffer + BUFFER_SIZE
        if(cache.actualPosition == cache.buffer + (block + 1) * (BLOCK_SIZE + 1)){
            finalCharacters = loadBlock((block + 1) % NUMBER_OF_BLOCKS);
            if(finalCharacters < BLOCK_SIZE) *(cache.actualPosition + finalCharacters) = EOF;
            c = *cache.actualPosition;
            cache.actualPosition++;
        }
    }
    return c;
}

/*************************************************************
 * Funciones para liberar la memoria del buffer.
 *************************************************************/

void freeMemoryInputSystem(){
    fclose(fileInput);
}

