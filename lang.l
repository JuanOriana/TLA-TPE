%{
#include "./include/ast.h"
#include "y.tab.h"
#include <stdio.h>

int fileno(FILE * stream);

// void put_trimmed(char * str) {
//     int i; for(i=0; str[i]!=' '; i++);
//     memcpy(yylval.string, str, i);
//     yylval.string[i] = 0;
// }

// extern int reduced;

%}

%option yylineno

INTEGER [0-9]+
DOUBLE f[0-9]+.[0-9]+

SP      [ \t\r\n]+

%%
int         { yylval.integer = INTEGER_TYPE; return INTEGER_TYPE; }
string     { yylval.integer = STRING_TYPE; return STRING_TYPE; }
double     { yylval.integer = DOUBLE_TYPE; return DOUBLE_TYPE; }
canvas     { yylval.integer = CANVAS_TYPE; return CANVAS_TYPE; }
write      { return WRITE; }
read       { return READ; }
plot       {return PLOT;}
main:      {return MAIN;}
if                          { return IF; }
else                        {return ELSE; }
while                       { return WHILE; }
return                       { return RETURN; }


'[\x00-\x7F]'                 { strcpy(yylval.string, yytext); return ASCII; }
\"[^\"]+\"                  { strcpy(yylval.string, yytext); return STRING; }
{INTEGER}                   { strcpy(yylval.string, yytext); return INTEGER; }
{DOUBLE}                    { strcpy(yylval.string, yytext); return DOUBLE; }

=                           { return ASSIGN;     }
;                           { return DELIMETER;     }

!=|<=|>=|==|<|>            { strcpy(yylval.string, yytext); return BIN_OP; }  
&&|\|\|		                { strcpy(yylval.string, yytext); return BIN_OP; }
\+|\*|\/|%		            { strcpy(yylval.string, yytext); return BIN_OP; }
!		                    { strcpy(yylval.string, "!"); return UNI_OP; }

fill                        { strcpy(yylval.string, yytext); return QUAD_CV_OP_CHAR; }
hor|vert                    { strcpy(yylval.string, yytext); return TRI_CV_OP; }
dot                         {strcpy(yylval.string, yytext); return BIN_CV_OP; }
char                        { strcpy(yylval.string, yytext); return BIN_CV_OP_CHAR; }
color                       { strcpy(yylval.string, yytext); return UNI_CV_OP; }

\{                           { return CURLY_OPEN; }
\}                           { return CURLY_CLOSE; }
\(                           { return PARENTH_OPEN; }
\)                           { return PARENTH_CLOSE; }
final                        { return FINAL; }

[a-zA-Z_][a-zA-Z0-9_]*      { strcpy(yylval.string, yytext); return SYMBOL_ID; }

\/\/.*                         ; // Ignore single line comments 
{SP}                           ; // Ignore whitespaces
<<EOF>>                     { static int once = 0; return once++ ? 0 : FINAL_EOF; }

.                           { return yytext[0]; };

%%