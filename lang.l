%{
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
SP      [ \t]+

%%
start      { return START;}
number     { yylval.number = NUMBER_TYPE; return NUMBER_TYPE; }
string     { yylval.number = STRING_TYPE; return STRING_TYPE; }
boolean    { yylval.number = BOOLEAN_TYPE; return BOOLEAN_TYPE; }
write      { return WRITE; }
read       { return READ; }
size       { return SIZE; }


\"[^\"]+\"                  { strcpy(yylval.string, yytext); return STRING; }
{INTEGER}                   { strcpy(yylval.string, yytext); return NUMBER; }
=                           { return ASSIGN;     }

!=|<=|>=|==                 { strcpy(yylval.string, yytext); return BIN_OP; }
&&		                    { strcpy(yylval.string, "&&"); return BIN_OP; }
\|\|		                    { strcpy(yylval.string, "||"); return BIN_OP; }
!		                    { strcpy(yylval.string, "!"); return UNI_OP; }


if                          { strcpy(yylval.string, yytext); return IF; }
else                        { strcpy(yylval.string, yytext); return ELSE; }
while                       { strcpy(yylval.string, yytext); return WHILE; }
do                          { strcpy(yylval.string, yytext); return DO; }
end                         { return END; }

[a-zA-Z_][a-zA-Z0-9_]*      { strcpy(yylval.string, yytext); return SYMBOL_NAME; }

#.*                         ; // Ignore comments
{SP}                        ; // Ignore whitespaces
<<EOF>>                     { static int once = 0; return once++ ? 0 : FIN; }

.           { return yytext[0]; };
[\n]        { return EOL; };

%%