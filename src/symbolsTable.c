#include "../includes/symbolsTable.h"
#include <stdlib.h>
#include <string.h>

//Palabras reservadas del lenguaje D (https://dlang.org/spec/lex.html)
token reservedWords[TOTAL_KEYWORDS] =
        {
        {"abstract", ABSTRACT},
        {"alias", ALIAS},
        {"align", ALIGN},
        {"asm", ASM},
        {"assert", ASSERT},
        {"auto", AUTO},
        {"body", BODY},
        {"bool", BOOL},
        {"break", BREAK},
        {"byte", BYTE},
        {"case", CASE},
        {"cast", CAST},
        {"catch", CATCH},
        {"cdouble", CDOUBLE},
        {"cent", CENT},
        {"cfloat", CFLOAT},
        {"char", CHAR},
        {"class", CLASS},
        {"const", CONST},
        {"continue", CONTINUE},
        {"creal", CREAL},
        {"dchar", DCHAR},
        {"debug", DEBUG},
        {"default", DEFAULT},
        {"delegate", DELEGATE},
        {"delete", DELETE},
        {"deprecated", DEPRECATED},
        {"do", DO},
        {"double", DOUBLE},
        {"else", ELSE},
        {"enum", ENUM},
        {"export", EXPORT},
        {"extern", EXTERN},
        {"false", FALSE},
        {"final", FINAL},
        {"finally", FINALLY},
        {"float", FLOAT},
        {"for", FOR},
        {"foreach", FOREACH},
        {"foreach_reverse", FOREACH_REVERSE},
        {"function", FUNCTION},
        {"goto", GOTO},
        {"idouble", IDOUBLE},
        {"if", IF},
        {"ifloat", IFLOAT},
        {"immutable", IMMUTABLE},
        {"import", IMPORT},
        {"in", IN},
        {"inout", INOUT},
        {"int", INT},
        {"interface", INTERFACE},
        {"invariant", INVARIANT},
        {"ireal", IREAL},
        {"is", IS},
        {"lazy", LAZY},
        {"long", LONG},
        {"macro", MACRO},
        {"mixin", MIXIN},
        {"module", MODULE},
        {"new", NEW},
        {"nothrow", NOTHROW},
        {"null", NULLD},
        {"out", OUT},
        {"override", OVERRIDE},
        {"package", PACKAGE},
        {"pragma", PRAGMA},
        {"private", PRIVATE},
        {"protected", PROTECTED},
        {"public", PUBLIC},
        {"pure", PURE},
        {"real", REAL},
        {"ref", REF},
        {"return", RETURN},
        {"scope", SCOPE},
        {"shared", SHARED},
        {"short",SHORT},
        {"static", STATIC},
        {"struct", STRUCT},
        {"super", SUPER},
        {"switch", SWITCH},
        {"synchronized", SYNCHRONIZED},
        {"template", TEMPLATE},
        {"this", THIS},
        {"throw", THROW},
        {"true", TRUE},
        {"try", TRY},
        {"typedef", TYPEDEF},
        {"typeid", TYPEID},
        {"typeof", TYPEOF},
        {"ubyte", UBYTE},
        {"ucent", UCENT},
        {"uint", UINT},
        {"ulong", ULONG},
        {"union", UNION},
        {"unittest", UNITTEST},
        {"ushort", USHORT},
        {"version", VERSION},
        {"void", VOID},
        {"volatile", VOLATILE},
        {"wchar", WCHAR},
        {"while", WHILE},
        {"with", WITH},
};


void initSymbolsTable(TablaHash TS) {
    InitHashTable(TS);
    for (int i = 0; i < TOTAL_KEYWORDS; i++) {
        insertHashElement(TS, reservedWords[i]);
    }
}

int searchTokenCode(TablaHash TS, char *key) {
    token taux;

    if(!searchHashElement(TS, key, &taux)) {
        taux.codeToken = ID;
        //Copia del String del ID para añadirlo y mantenerlo en la TS y seguir con el token del sintacticParser
        taux.stringToken = malloc(strlen(key) + 1);
        strcpy(taux.stringToken, key);
        insertHashElement(TS, taux);
        return ID;
    }
    return taux.codeToken;
}

void destroySymbolsTable(TablaHash TS){
    destroyHashTable(TS);
}