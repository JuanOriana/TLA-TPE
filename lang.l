%{
#include "./include/tree.h"
#include "y.tab.h"
#include <stdio.h>

int fileno(FILE * stream);

void put_trimmed(char * str) {
    int i; for(i=0; str[i]!=' '; i++);
    memcpy(yylval.string, str, i);
    yylval.string[i] = 0;
}

extern int reduced;

%}

%option yylineno

INTEGER [0-9]+
SP      [ \t\r\n]+

%%
int         { yylval.integer = INTEGER_TYPE; return INTEGER_TYPE; }
string     { yylval.integer = STRING_TYPE; return STRING_TYPE; }
boolean    { yylval.integer = BOOLEAN_TYPE; return BOOLEAN_TYPE; }
canvas     { yylval.integer = CANVAS_TYPE; return CANVAS_TYPE; }
write      { return WRITE; }
read       { return READ; }
plot       {return PLOT;}
main:      {return MAIN;}


'[\x00-\x7F]'                 { strcpy(yylval.string, yytext); return ASCII; }
\"[^\"]+\"                  { strcpy(yylval.string, yytext); return STRING; }
{INTEGER}                   { strcpy(yylval.string, yytext); return INTEGER; }
=                           { return ASSIGN;     }
;                           { return DELIMETER;     }

!=|<=|>=|==|<|>|%           { strcpy(yylval.string, yytext); return BIN_OP; }  
&&		                    { strcpy(yylval.string, "&&"); return BIN_OP; }
\|\|	                    { strcpy(yylval.string, "||"); return BIN_OP; }
\+|\*|\/		            { strcpy(yylval.string, yytext); return BIN_OP; }
!		                    { strcpy(yylval.string, "!"); return UNI_OP; }

fill                        { strcpy(yylval.string, yytext); return QUAD_CV_OP_CHAR; }
hor|vert                    { strcpy(yylval.string, yytext); return TRI_CV_OP; }
dot                         {strcpy(yylval.string, yytext); return BIN_CV_OP; }
char                        { strcpy(yylval.string, yytext); return BIN_CV_OP_CHAR; }
color                       { strcpy(yylval.string, yytext); return UNI_CV_OP; }


if                          { strcpy(yylval.string, yytext); return IF; }
else                        { strcpy(yylval.string, yytext); return ELSE; }
while                       { strcpy(yylval.string, yytext); return WHILE; }
return                       { strcpy(yylval.string, yytext); return RETURN; }

\{                           { return BRACK_OPEN; }
\}                           { return BRACK_CLOSE; }

[a-zA-Z_][a-zA-Z0-9_]*      { strcpy(yylval.string, yytext); return SYMBOL_NAME; }

#.*                         ; // Ignore comments 
{SP}                        ; // Ignore whitespaces
<<EOF>>                     { static int once = 0; return once++ ? 0 : FIN; }

.                           { return yytext[0]; };

%%