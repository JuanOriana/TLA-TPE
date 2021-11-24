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
start      { return START;}
number     { yylval.number = NUMBER_TYPE; return NUMBER_TYPE; }
string     { yylval.number = STRING_TYPE; return STRING_TYPE; }
boolean    { yylval.number = BOOLEAN_TYPE; return BOOLEAN_TYPE; }
canvas     { yylval.number = CANVAS_TYPE; return CANVAS_TYPE; }
write      { return WRITE; }
read       { return READ; }

'[\x00-\x7F]'                 { strcpy(yylval.string, yytext); return ASCII; }
\"[^\"]+\"                  { strcpy(yylval.string, yytext); return STRING; }
{INTEGER}                   { strcpy(yylval.string, yytext); return NUMBER; }
=                           { return ASSIGN;     }
;                           { return DELIMETER;     }

!=|<=|>=|==                 { strcpy(yylval.string, yytext); return BIN_OP; }
&&		                    { strcpy(yylval.string, "&&"); return BIN_OP; }
\|\|	                    { strcpy(yylval.string, "||"); return BIN_OP; }
\+|\*|\/		                { strcpy(yylval.string, yytext); return BIN_OP; }
!		                    { strcpy(yylval.string, "!"); return UNI_OP; }

hor|vert                    { strcpy(yylval.string, yytext); return TRI_CV_OP; }
dot                         {strcpy(yylval.string, yytext); return QUAD_CV_OP; }
char                        { strcpy(yylval.string, yytext); return PENT_CV_OP; }

plot                        {return PLOT;}
if                          { strcpy(yylval.string, yytext); return IF; }
else                        { strcpy(yylval.string, yytext); return ELSE; }
while                       { strcpy(yylval.string, yytext); return WHILE; }
\{                           { return BRACK_OPEN; }
\}                           { return BRACK_CLOSE; }

[a-zA-Z_][a-zA-Z0-9_]*      { strcpy(yylval.string, yytext); return SYMBOL_NAME; }

#.*                         ; // Ignore comments
{SP}                        ; // Ignore whitespaces
<<EOF>>                     { static int once = 0; return once++ ? 0 : FIN; }

.                           { return yytext[0]; };

%%