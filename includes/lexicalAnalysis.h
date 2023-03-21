#ifndef CM1_LEXICALANALYSIS_H
#define CM1_LEXICALANALYSIS_H

#include "inputSystem.h"
#include "symbolsTable.h"
#include "automatons.h"

#define AUTOMATON_END 0
#define AUTOMATON_EOF 1
#define AUTOMATON_ALPHANUMERIC 2
#define AUTOMATON_COMMENT 3
#define AUTOMATON_STRING 4
#define AUTOMATON_NUMBER 5
#define AUTOMATON_SPECIAL_SYMBOL 6


/****************************************************************************************
 *  GET TOKEN
 ****************************************************************************************/

void sendTokenToParser(TablaHash TS, token *t);

/****************************************************************************************
 *  FACADE FOR AUTOMATONS
 ****************************************************************************************/

void callBackActualPosition();

#endif //CM1_LEXICALANALYSIS_H
