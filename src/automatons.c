#include "../includes/automatons.h"
#include <ctype.h>


char state = 0;
int nested = 0; //Para los comentarios anidados

int acceptState(short needToCallBack){
    if(needToCallBack) callBackActualPosition();
    state = 0;
    return AcceptState;
}

int alphaNumericAutomaton(char character){
    switch (state) {
        case 0:
            if(isalpha(character) || character == '_' || isdigit(character)){
                state = 0;
                return 0;
            }
            state = 1;
        case 1:
            return acceptState(1);
        default:
            return RejectState;
    }
}

int specialSymbolAutomaton(char character){
    if(character == '*' || character == '/'|| character == '.' || character == ';' || character == ',' || character == '(' || character == ')' || character == '{' || character == '}' || character == '[' || character == ']'){
        return acceptState(0);
    }
    switch (state) {
        case 0:
            switch (character) {
                case '+':
                    state = 1;
                    return RejectState;
                case '-':
                    state = 2;
                    return RejectState;
                case '>': case '<': case '=': case '!':
                    state = 3;
                    return RejectState;
                case '&':
                    state = 4;
                    return RejectState;
                case '|':
                    state = 5;
                    return RejectState;

                default: return RejectState;
            }

        case 1:
            switch (character) {
                case '+': case '=': return acceptState(0);

                default: return acceptState(1);
            }

        case 2:
            switch (character) {
                case '-': case '=': return acceptState(0);

                default: return acceptState(1);
            }

        case 3:
            if(character == '=') return acceptState(0);
            return acceptState(1);

        case 4:
            if(character == '&') return acceptState(0);
            return acceptState(1);

        case 5:
            if(character == '|') return acceptState(0);
            return acceptState(1);

        default: return RejectState;
    }
}

int stringAutomaton(char character){
    switch (state) {

        //Estado inicial -> comprobar si es una comilla
        case 0:
            if(character == '"') state = 1;
            return RejectState;

        //Estado 1 -> generar todos los caracteres hasta que se encuentre una comilla y si se encuentra una barra invertida se pasa al estado 2
        case 1:
            switch (character) {
                case '"': return acceptState(0);
                case '\\':
                    state = 2;
                    return RejectState;

                default: return RejectState;
            }

        //Estado 2 -> Despues de barra invertida se pueden encontrar caracteres especiales
        case 2:
            switch (character) {
                case '\'':case '"':case '?':case '\\':case '0':case 'a':case 'b':case 'f':
                case 'n':case 'r':case 't':case 'v':
                    state = 1;
                    return RejectState;

                default: return RejectState;
            }

        default: return RejectState;
    }
    return RejectState;
}

int numberAutomaton(char character){
    switch (state) {

        case 0:
            if(character == '0'){state = 1; return 0;}
            if(isdigit(character))state = 3;
            return RejectState;

        case 1:
            if(character == 'b') { state = 2; return 0;}

            return acceptState(1);

        case 2:
            if(character == '0' || character == '1'){
                state = 2;
                return RejectState;
            }

            return acceptState(1);

        case 3:
            //Genera numero decimal
            if(isdigit(character) || character == '_'){
                state = 3;
                return RejectState;
            }

            //Genera numero float
            if(character == '.'){
                state = 4;
                return RejectState;
            }

            if(character == 'e' || character == 'E'){
                state = 5;
                return RejectState;
            }

            return acceptState(1);


        case 4:
            if(isdigit(character)){
                state = 4;
                return RejectState;
            }

            if(character == 'e' || character == 'E'){
                state = 5;
                return RejectState;
            }

            return acceptState(1);

        case 5:
            if(character == '+' || character == '-') {
                state = 6;
                return RejectState;
            }

        case 6:
            if(isdigit(character) || character == '_'){
                state = 5;
                return RejectState;
            }

            return acceptState(1);

        default: return RejectState;
    }
}

int commentAutomaton(char character){
    switch (state) {

        //Estado inicial -> Comienza con /
        case 0:
            if(character == '/') state = 1;
            return RejectState;

        //Estado 1 -> Comienza con //, /* o +/(anidado)
        case 1:
            switch (character) {
                case '/':
                    state = 2;
                    return RejectState;

                case '*':
                    state = 3;
                    return RejectState;

                case '+':
                    nested++;
                    state = 5;
                    return RejectState;

                default:
                    state = 0;
                    callBackActualPosition();
                    callBackActualPosition();
                    return Swap_Automaton_To_SpecialSymbol;
            }

        //Estado 2 -> Comienza con //, se espera un salto de linea para terminar el comentario
        case 2:
            if(character == '\n') return acceptState(0);
            return RejectState;

        //Estado 3 -> Comienza con /*, se espera un * para pasar al estado 4
        case 3:
            if(character == '*') state = 4;
            return RejectState;

        //Estado 4 -> Tenemos * se espera un / para terminar el comentario
        case 4:
            if(character == '/') return acceptState(0);
            return RejectState;

        //Estado 5 -> Comienza con +/, se espera un / para anidar un comentario o un + para salir de un comentario anidado
        case 5:
            switch (character) {
                case '/':
                    state = 6;
                    return RejectState;
                case '+':
                    state = 7;
                    return RejectState;
                default: return RejectState;
            }

        //Estado 6 -> Tenemos un /, se espera un + para anidar un comentario
        case 6:
            if(character == '+') nested++;
            state = 5;
            return RejectState;

        //Estado 7 -> Tenemos un +, se espera un / para salir de un comentario anidado
        case 7:
            if(character == '/') nested--;
            if(nested == 0) return acceptState(0);
            state = 5;
            return RejectState;

        default: return RejectState;

    }
}

