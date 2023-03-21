#ifndef CM1_INPUTSYSTEM_H
#define CM1_INPUTSYSTEM_H

#include "errorHandler.h"

#define BLOCK_SIZE 32
#define NUMBER_OF_BLOCKS 2
#define BUFFER_SIZE (BLOCK_SIZE*NUMBER_OF_BLOCKS + NUMBER_OF_BLOCKS)
#define FILENAME "regression.d"

/*************************************************************
 * Funciones para la inicialización del sistema de entrada.
 *************************************************************/

void initInputSystem();

/*************************************************************
 * Funciones para manejo de punteros del buffer.
 *************************************************************/

void updateInitialPosition();

void backActualPosition();

/*************************************************************
 * Funciones para la lectura del buffer.
 *************************************************************/

void takeWordBetweenInitialPositionAndActualPosition(char *buffer);

char nextChar();

/*************************************************************
 * Funciones para la liberación de la memoria del buffer.
 *************************************************************/

void freeMemoryInputSystem();

#endif //CM1_INPUTSYSTEM_H
