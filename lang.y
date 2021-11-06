%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./include/tree.h"


// Extern prototypes

extern int yylex();
void yyerror(node_t ** program, char *s);
void warning(char * s);

extern FILE * out;
extern void * malloc();

// #define WARNING(...) fprintf(stderr, "\033[38;2;255;165;0mWARNING: ");\
//     fprintf(stderr, ##__VA_ARGS__);\
//     fprintf(stderr, "\x1b[0m\n");\
//     ;

// Global variables

int yydebug = 1;
int main_init = FALSE;

%}

%union {
    char string[1024];
    double number;
    char boolean;
    struct node_t * node;
    struct node_t * list;

}

%token START EOL FIN
%token COMB PERM 
%token MEAN MEDIAN MODE STDEV RANGE QTR1 QTR3 INTER_QTR IN
%token ASSIGN WRITE READ SIZE

%token <string> IF WHILE DO END ELSE
%token <string> SYMBOL_NAME

%token <string> BIN_OP UNI_OP 
%token <string> NUMBER STRING BOOLEAN 

%token <number> STRING_TYPE NUMBER_TYPE BOOLEAN_TYPE
%token <number> NATURAL

%type <number> type
%type <node> full_declare declare assign value expression
%type <node> instruction write read if if_end while
%type <list> program block

%nonassoc IN
%left BIN_OP '-'

%parse-param {node_t ** program}

%%
program: instruction program { $$ = (*program = (node_t *)add_element_to_list($2, $1)); }
    | EOL program { $$ = $2; }
    | FIN { $$ = (*program = (node_t *)add_instruction_list_node(NULL)); };

instruction:
    full_declare    { $$ = add_instruction_node($1); }
    | assign        { $$ = add_instruction_node($1); }
    | write         { if (main_init == FALSE) {
                        //$$ = free_write($1); 
                        warning("write");
                    } else $$ = add_instruction_node($1); }
    | read          { if (main_init == FALSE) {
                       // $$ = free_read($1);
                        warning("read");
                    } else $$ = add_instruction_node($1); }
    | if            { if (main_init == FALSE) {
                        //$$ = free_if_node($1);
                        warning("if");
                    } else $$ = add_instruction_node($1); }
    | while         { if (main_init == FALSE) {
                        //$$ = free_while_node($1);
                    } else $$ = add_instruction_node($1); }
    | START         { main_init=TRUE; $$=NULL; };

block: instruction block { $$ = (node_t *)add_element_to_list($2, $1); }
    | EOL block { $$ = $2; }
    | instruction { $$ = (node_t *)add_instruction_list_node($1); }
    | EOL { $$ = (node_t *)add_instruction_list_node(NULL); };

if: IF expression DO block if_end { $$ = add_if_node($2, add_block_node($4), $5); };

while: WHILE expression DO block END { $$ = add_while_node($2, add_block_node($4)); };

if_end: END { $$ = NULL; }
    | ELSE block END { $$ = add_block_node($2); };
    
full_declare: declare               { $$ = $1; }
    | declare ASSIGN value          { $$ = add_value_variable($1, $3); };

declare: type SYMBOL_NAME           { $$ = declare_variable_node($2, $1); };
type: NUMBER_TYPE | STRING_TYPE        ;

assign: SYMBOL_NAME ASSIGN value { $$ = assign_variable_node($1, $3); };
value: expression   { $$ = $1; }
    | SYMBOL_NAME   { $$ = add_variable_reference($1); }
    | STRING        { $$ = add_text_node($1);   };


write: WRITE expression                     { $$ = add_print_node($2); }
    | WRITE SYMBOL_NAME                     { $$ = add_print_node(add_variable_reference($2)); }
    | WRITE STRING                          { $$ = add_print_node(add_text_node($2)); }

read: READ SYMBOL_NAME                      { $$ = add_read_node(add_variable_reference($2)); };

expression: '(' expression ')'              { $$ = add_expression_node(add_operation_node("("), $2, add_operation_node(")")); }
    | UNI_OP expression                     { $$ = add_expression_node(add_operation_node($1), $2, NULL); }
    | '-' expression           %prec UNI_OP { $$ = add_expression_node(add_operation_node("-"), $2, NULL); }
    | expression BIN_OP expression          { $$ = add_expression_node($1, add_operation_node($2), $3); }
    | expression '-' expression             { $$ = add_expression_node($1, add_operation_node("-"), $3); }
    | NUMBER                                { $$ = add_expression_node(add_number_node($1), NULL, NULL); }
    | '$' SYMBOL_NAME                       { $$ = add_expression_node(add_variable_reference($2), NULL, NULL); };


%%


void warning(char * s) {
    extern int yylineno;
    // WARNING("%s at line %d, will not be considered.", s, yylineno);
}