#include "../includes/lexicalAnalysis.h"
#include <stdio.h>
#include <ctype.h>

/*************************************************************
 *  FACADE FOR AUTOMATONS
 *************************************************************/

void callBackActualPosition() {
    backActualPosition();
}

/*************************************************************
 *  CODE FOR SPECIAL SYMBOLS
 *************************************************************/

int codeForSpecialSymbols(const char* character){

    switch (character[0]) {
        case '*': return '*';

        case '/': return '/';

        case '.': return '.';

        case ';': return ';';

        case ',': return ',';

        case '(': return '(';

        case ')': return ')';

        case '{': return '{';

        case '}': return '}';

        case '[': return '[';

        case ']':return ']';

        case '+':
            if(character[1] == '+') return SPECIAL_SYMBOL_ADDITION;
            if(character[1] == '=') return SPECIAL_SYMBOL_ADDITION_EQUAL;
            return '+';

        case '-':
            if(character[1] == '-') return SPECIAL_SYMBOL_SUBTRACTION;
            if(character[1] == '=') return SPECIAL_SYMBOL_SUBTRACTION_EQUAL;
            return '-';

        case '<':
            if(character[1] == '=') return SPECIAL_SYMBOL_LESS_EQUAL;
            return '<';

        case '>':
            if(character[1] == '=') return SPECIAL_SYMBOL_GREATER_EQUAL;
            return '>';

        case '=':
            if(character[1] == '=') return SPECIAL_SYMBOL_EQUAL_EQUAL;
            return '=';

        case '!':
            if(character[1] == '=') return SPECIAL_SYMBOL_NOT_EQUAL;
            return '!';

        case '&':
            if(character[1] == '&') return SPECIAL_SYMBOL_AND;
            return '&';

        case '|':
            if(character[1] == '|') return SPECIAL_SYMBOL_OR;
            return '|';

        case '%':
            if(character[1] == 'f') return SPECIAL_SYMBOL_PRINT_FLOAT;
            if(character[1] == 'd') return SPECIAL_SYMBOL_PRINT_INT;
            if(character[1] == 's') return SPECIAL_SYMBOL_PRINT_STRING;
            if(character[1] == 'c') return SPECIAL_SYMBOL_PRINT_CHAR;
            return '%';
    }

    return 0;
}

/*************************************************************
 *  MANAGE/SELECT AUTOMATONS
 *************************************************************/

int selectAutomaton(char character) {

    if (isalpha(character) || character == '_') return AUTOMATON_ALPHANUMERIC;

    if (character == '/') return AUTOMATON_COMMENT;

    if (character == '"') return AUTOMATON_STRING;

    if (isdigit(character)) return AUTOMATON_NUMBER;

    if (character == EOF) return AUTOMATON_EOF;

    if (character == ' ' || character == '\t' || character == '\n') {
        updateInitialPosition();
        return AUTOMATON_END;
    }

    return AUTOMATON_SPECIAL_SYMBOL;

}

int automatonManager(int automaton, char character) {
    switch (automaton) {
        case AUTOMATON_ALPHANUMERIC:
            return alphaNumericAutomaton(character);
        case AUTOMATON_COMMENT:
            return commentAutomaton(character);
        case AUTOMATON_STRING:
            return stringAutomaton(character);
        case AUTOMATON_NUMBER:
            return numberAutomaton(character);
        case AUTOMATON_SPECIAL_SYMBOL:
            return specialSymbolAutomaton(character);
        case AUTOMATON_EOF:
            return EOF;
        default:
            return 0;
    }
}

/*************************************************************
 *  GET TOKEN
 *************************************************************/

void resultAutomatonManager(TablaHash TS, int *automaton,token *t) {
    takeWordBetweenInitialPositionAndActualPosition(t->stringToken);

    switch (*automaton) {
        case AUTOMATON_ALPHANUMERIC:
            t->codeToken = searchTokenCode(TS, t->stringToken);
            break;
        case AUTOMATON_SPECIAL_SYMBOL:
            t->codeToken = codeForSpecialSymbols(t->stringToken);
            break;
        case AUTOMATON_COMMENT:
            t->codeToken = COMMENT;
            break;

        case AUTOMATON_STRING:
            t->codeToken = STRING;
            break;

        case AUTOMATON_NUMBER:
            t->codeToken = NUMBER;
            break;

        case AUTOMATON_EOF:
            t->codeToken = EOF;
            break;
    }
    *automaton = AUTOMATON_END;
}

void generateToken(TablaHash TS, token *t) {
    int automaton = AUTOMATON_END;
    char character = ' ';
    int tmpResultAutomaton;
    while (character != EOF) {

        character = nextChar();

        if (automaton == AUTOMATON_END)
            if ((automaton = selectAutomaton(character)) == AUTOMATON_END) continue;

        //Resultado del automata
        tmpResultAutomaton = automatonManager(automaton, character);

        //Si el automata ha reconodicido que una palabra deberia analizarce con otro automata, "/" comentario o simbolos especiales
        if(tmpResultAutomaton == Swap_Automaton_To_SpecialSymbol){
            automaton = AUTOMATON_SPECIAL_SYMBOL;
            continue;
        }

        //El automata no ha terminado de reconocer la palabra
        if (!tmpResultAutomaton) continue;

        if(tmpResultAutomaton == AcceptState && automaton == AUTOMATON_COMMENT){
            updateInitialPosition();
            automaton = AUTOMATON_END;
            continue;
        }

        resultAutomatonManager(TS, &automaton, t);
        return;
    }
}

void sendTokenToParser(TablaHash TS, token *t) {
    updateInitialPosition();
    generateToken(TS, t);
}

