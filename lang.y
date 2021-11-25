%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/tree.h"


// Extern prototypes

extern int yylex();
void yyerror(node_t ** program, char *s);
void warning(char * s);

extern FILE * out;
extern void * malloc();

// #define WARNING(...) fprintf(stderr, "\033[38;2;255;165;0mWARNING: ");
//     fprintf(stderr, ##__VA_ARGS__);
//     fprintf(stderr, "\x1b[0m\n");
//     ;

// Global variables

int yydebug = 1;
int main_init = FALSE;

%}

%union {
    char string[1024];
    int integer;
    double floating;
    struct node_t * node;
    struct node_t * list;

}

%token MAIN EOL FIN DELIMETER BRACK_OPEN BRACK_CLOSE RETURN
%token ASSIGN WRITE READ SIZE PLOT

%token <string> IF WHILE ELSE
%token <string> SYMBOL_NAME

%token <string> BIN_OP UNI_OP BIN_CV_OP TRI_CV_OP BIN_CV_OP_CHAR UNI_CV_OP QUAD_CV_OP_CHAR
%token <string> INTEGER STRING DOUBLE ASCII

%token <integer> STRING_TYPE INTEGER_TYPE DOUBLE_TYPE CANVAS_TYPE
%token <integer> NATURAL

%type <integer> type
%type <node> full_declare declare assign value expression full_cv_declare cv_declare cv_value return
%type <node> instruction write read if if_end while plot cv_op 
%type <list> program block

%nonassoc IN
%left BIN_OP '-'
%left UNI_OP

%parse-param {node_t ** program}

%%
program: instruction program { $$ = (*program = (node_t *)add_element_to_list($2, $1));}
    | FIN { $$ = (*program = (node_t *)add_instruction_list_node(NULL)); };

instruction:
    full_declare DELIMETER    { $$ = add_instruction_node($1); }
    | full_cv_declare DELIMETER {$$ = add_instruction_node($1);}
    | assign DELIMETER        { $$ = add_instruction_node($1); }
    | write DELIMETER         { if (main_init==FALSE){yyerror(program,"Syntax error calling write previous main");}else{$$ = add_instruction_node($1);} }
    | read  DELIMETER         { if (main_init==FALSE){yyerror(program,"Syntax error calling read previous main");}else{$$ = add_instruction_node($1);} }
    | if                      { if (main_init==FALSE){yyerror(program,"Syntax error calling if previous main");}else{$$ = add_instruction_node($1);} }
    | while                   { if (main_init==FALSE){yyerror(program,"Syntax error calling while previous main");}else{$$ = add_instruction_node($1);} }
    | plot  DELIMETER        { if (main_init==FALSE){yyerror(program,"Syntax error calling plot previous main");}else{$$ = add_instruction_node($1);} }
    | cv_op DELIMETER        { if (main_init==FALSE){yyerror(program,"Syntax error calling cv_op previous main");}else{$$ = add_instruction_node($1);} }
    | return DELIMETER        { if (main_init==FALSE){yyerror(program,"Syntax error returning outside of main");}else{$$ = add_instruction_node($1);} }
    | MAIN          { if (main_init==TRUE){yyerror(program,"Syntax error calling mains after previous main entry");}else{main_init=TRUE; $$=NULL; }};

block: instruction block { $$ = (node_t *)add_element_to_list($2, $1); }
    | instruction { $$ = $1; }

if: IF '(' expression ')' BRACK_OPEN block if_end { $$ = add_if_node($3, add_block_node($6), $7); };

while: WHILE '(' expression ')' BRACK_OPEN block BRACK_CLOSE { $$ = add_while_node($3, add_block_node($6)); };

return: RETURN expression {$$ = add_return_node($2);};

if_end: BRACK_CLOSE { $$ = NULL; }
    | BRACK_CLOSE ELSE BRACK_OPEN block BRACK_CLOSE { $$ = add_block_node($4); };
    
full_declare: declare               { $$ = $1; }
    | declare ASSIGN value          { $$ = add_value_variable($1, $3); };

full_cv_declare: cv_declare ASSIGN cv_value {$$ = add_value_variable($1, $3);};

declare: type SYMBOL_NAME           { $$ = declare_variable_node($2, $1); };

cv_declare: CANVAS_TYPE SYMBOL_NAME {$$ = declare_variable_node($2,$1);};

type: INTEGER_TYPE | STRING_TYPE | DOUBLE_TYPE;

assign: SYMBOL_NAME ASSIGN value { $$ = assign_variable_node($1, $3); };

value: expression   { $$ = $1; }
    | STRING        { $$ = add_text_node($1);   };

cv_value: BRACK_OPEN INTEGER ',' INTEGER BRACK_CLOSE {$$ = add_canvas_node($2,$4);};

write: WRITE expression                     { $$ = add_print_node($2); }
    | WRITE STRING                          { $$ = add_print_node(add_text_node($2)); }

read: READ SYMBOL_NAME                      { $$ = add_read_node(add_variable_reference($2)); };

plot: PLOT SYMBOL_NAME                      { $$ = add_plot_node(add_variable_reference($2)); };

cv_op: SYMBOL_NAME BIN_CV_OP BRACK_OPEN expression ',' expression BRACK_CLOSE { $$ = add_generic_cv_op_node(add_variable_reference($1),$2,0,$4,$6,0,0); }
    | SYMBOL_NAME BIN_CV_OP_CHAR BRACK_OPEN expression ',' expression ',' ASCII BRACK_CLOSE { $$ = add_generic_cv_op_node(add_variable_reference($1),$2,$8,$4,$6,0,0); }
    | SYMBOL_NAME TRI_CV_OP BRACK_OPEN expression ',' expression ',' expression BRACK_CLOSE { $$ = add_generic_cv_op_node(add_variable_reference($1),$2,0,$4,$6,$8,0); }
    | SYMBOL_NAME UNI_CV_OP BRACK_OPEN expression BRACK_CLOSE { $$ = add_generic_cv_op_node(add_variable_reference($1),$2,0,$4,0,0,0); }
    | SYMBOL_NAME QUAD_CV_OP_CHAR BRACK_OPEN expression ',' expression ','expression ',' expression ',' ASCII BRACK_CLOSE { $$ = add_generic_cv_op_node(add_variable_reference($1),$2,$12,$4,$6,$8,$10); }


expression: '(' expression ')'              { $$ = add_expression_node(add_operation_node("("), $2, add_operation_node(")")); }
    | UNI_OP expression                     { $$ = add_expression_node(add_operation_node($1), $2, NULL); }
    | '-' expression           %prec UNI_OP { $$ = add_expression_node(add_operation_node("-"), $2, NULL); }
    | expression BIN_OP expression          { $$ = add_expression_node($1, add_operation_node($2), $3); }
    | expression '-' expression             { $$ = add_expression_node($1, add_operation_node("-"), $3); }
    | INTEGER                                { $$ = add_expression_node(add_integer_node($1), NULL, NULL); }
    | DOUBLE                                 { $$ = add_expression_node(add_double_node($1), NULL, NULL); }
    | SYMBOL_NAME                           { $$ = add_variable_reference($1); }


%%


void warning(char * s) {
    extern int yylineno;
    // WARNING("%s at line %d, will not be considered.", s, yylineno);
}