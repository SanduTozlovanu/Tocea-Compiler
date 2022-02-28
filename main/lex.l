%{
#include "yacc.tab.h"
#include <stdlib.h>
#include <string.h>
int line_number = 1;
%}
%option noyywrap
%%

"begin main" { return MAIN; }
"constant" { return CONST; }
"int" { return INT; }
"float" { return FLOAT; }
"char" { return CHAR; }
"string" { return STRING; }
"bool" { return BOOL; }
"void" { return VOID; }
"list" {return LIST; }
"if" { return IF; }
"then->" { return THEN; }
"else->" { return ELSE; }
"elif" { return ELIF; }
"while" { return WHILE; }
"var" {return VARDEF; }
"function:" { return FUNCDEF; }
"blob" { return BLOB; }
"print->" { return PRINT; }
"doubleprint" { return EVAL; }
"return" { return RETURN; }
"<=" { return LESSEQUAL; }
">=" { return GREATEREQUAL; }
"!=" { return NOTEQUAL; }
"==" { return EQUAL; }
"AND"|"and"|"&&" { return ANDL; }
"OR"|"or"|"||" { return ORL; }
"execute" {return FUNCALL; }
"true"|"TRUE" {
    yylval.boolValue = 1;
    return CONSTANT_BOOL;
}
"false"|"FALSE" {
    yylval.boolValue = 0;
    return CONSTANT_BOOL;
}
[ \t\r]  {}
[\n] { line_number++; }
[a-zA-Z_][a-zA-Z0-9_]* {
    yylval.stringValue = strdup(yytext);
    return VAR;
}
0|-?[1-9][0-9]* {
    yylval.intValue = atoi(yytext);
    return CONSTANT_INT;
}
\'[a-zA-Z0-9]\' {
    yylval.charValue = yytext[1];
    return CONSTANT_CHAR;
}

\"[a-z A-Z0-9!\?,\.-]*\" {
    int length = strlen(yytext);
    yylval.stringValue = (char *)malloc(sizeof(char) * (length + 1));
    memcpy(yylval.stringValue, yytext + 1, length - 2);
    yylval.stringValue[length] = '\0';
    return CONSTANT_STRING;
}
-?(0|[1-9][0-9]*)\.[0-9]+ {
    yylval.floatValue = atof(yytext);
    return CONSTANT_FLOAT;
}
[-+()=/*{};,<>\[\]%] { return yytext[0]; }
%%