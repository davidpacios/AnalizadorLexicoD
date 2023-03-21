#ifndef CM1_AUTOMATONS_H
#define CM1_AUTOMATONS_H

#include "lexicalAnalysis.h"

#define RejectState 0
#define AcceptState 1
#define Swap_Automaton_To_SpecialSymbol 2

/****************************************************************************************
 *  AUTOMATONS
 ****************************************************************************************/

int alphaNumericAutomaton(char character);

int specialSymbolAutomaton(char character);

int numberAutomaton(char character);

int stringAutomaton(char character);

int commentAutomaton(char character);

#endif //CM1_AUTOMATONS_H
