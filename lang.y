%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/ast.h"


// Extern prototypes

extern int yylex();
void yyerror(node_t ** program, char *s);
void warning(char * s);

extern FILE * out;
extern void * malloc();

int yydebug = 1;
int in_main = FALSE;

%}

%union {
    char string[1024];
    int integer;
    double floating;
    struct node_t * node;
    struct node_t * list;

}

%token FINAL_EOF DELIMETER CURLY_OPEN CURLY_CLOSE PARENTH_OPEN PARENTH_CLOSE ASSIGN
%token MAIN WRITE READ SIZE PLOT RETURN FINAL

%token <string> IF WHILE ELSE
%token <string> SYMBOL_ID

%token <string> BIN_OP UNI_OP BIN_CV_OP TRI_CV_OP BIN_CV_OP_CHAR UNI_CV_OP QUAD_CV_OP_CHAR
%token <string> INTEGER STRING DOUBLE ASCII

%token <integer> STRING_TYPE INTEGER_TYPE DOUBLE_TYPE CANVAS_TYPE
%token <integer> NATURAL

%type <integer> type
%type <node> full_declare declare final_declare assign value expression full_cv_declare cv_declare cv_value return
%type <node> program block instruction write read if if_end while plot cv_op 

%nonassoc IN
%left BIN_OP '-'
%left UNI_OP

%parse-param {node_t ** program}

%%
program: instruction program { $$ = (*program = (node_t *)add_element_to_list($2, $1));}
    | FINAL_EOF { $$ = (*program = (node_t *)add_instruction_list_node(NULL)); };

instruction:
    full_declare DELIMETER    { $$ = add_instruction_node($1); }
    | full_cv_declare DELIMETER {$$ = add_instruction_node($1);}
    | assign DELIMETER        { $$ = add_instruction_node($1); }
    | write DELIMETER         { if (in_main==FALSE){yyerror(program,"Syntax error calling write previous main");}else{$$ = add_instruction_node($1);} }
    | read  DELIMETER         { if (in_main==FALSE){yyerror(program,"Syntax error calling read previous main");}else{$$ = add_instruction_node($1);} }
    | if                      { if (in_main==FALSE){yyerror(program,"Syntax error calling if previous main");}else{$$ = add_instruction_node($1);} }
    | while                   { if (in_main==FALSE){yyerror(program,"Syntax error calling while previous main");}else{$$ = add_instruction_node($1);} }
    | plot  DELIMETER        { if (in_main==FALSE){yyerror(program,"Syntax error calling plot previous main");}else{$$ = add_instruction_node($1);} }
    | cv_op DELIMETER        { if (in_main==FALSE){yyerror(program,"Syntax error calling cv_op previous main");}else{$$ = add_instruction_node($1);} }
    | return DELIMETER        { if (in_main==FALSE){yyerror(program,"Syntax error returning outside of main");}else{$$ = add_instruction_node($1);} }
    | MAIN          { if (in_main==TRUE){yyerror(program,"Syntax error calling mains after previous main entry");}else{in_main=TRUE; $$=NULL; }};

block: instruction block { $$ = add_element_to_list($2, $1); }
    | instruction { $$ = $1; };

if: IF PARENTH_OPEN expression PARENTH_CLOSE CURLY_OPEN block if_end {$$ = add_if_node($3, add_block_node($6), $7); };

while: WHILE PARENTH_OPEN expression PARENTH_CLOSE CURLY_OPEN block CURLY_CLOSE { $$ = add_while_node($3, add_block_node($6)); };

return: RETURN expression {$$ = add_return_node($2);};

if_end: CURLY_CLOSE { $$ = NULL; }
    | CURLY_CLOSE ELSE CURLY_OPEN block CURLY_CLOSE { $$ = add_block_node($4); };
    
full_declare: declare               { $$ = $1; }
    | declare ASSIGN value          { $$ = add_value_variable($1, $3); }
    | final_declare ASSIGN value    {if (in_main==TRUE){yyerror(program,"Syntax error defining constant inside of main");}else{$$ = add_value_variable($1, $3);}};

full_cv_declare: cv_declare ASSIGN cv_value {$$ = add_value_variable($1, $3);};

declare: type SYMBOL_ID           { $$ = declare_variable_node($2, $1); };

final_declare: FINAL type SYMBOL_ID { $$ = declare_constant_variable_node($3, $2); };

cv_declare: CANVAS_TYPE SYMBOL_ID {$$ = declare_variable_node($2,$1);};

type: INTEGER_TYPE | STRING_TYPE | DOUBLE_TYPE;

assign: SYMBOL_ID ASSIGN value { $$ = assign_variable_node($1, $3); };

value: expression   { $$ = $1; }
    | STRING        { $$ = add_text_node($1);};

cv_value: CURLY_OPEN INTEGER ',' INTEGER CURLY_CLOSE {$$ = add_canvas_node($2,$4);};

write: WRITE PARENTH_OPEN expression PARENTH_CLOSE                   { $$ = add_print_node($3); }
    | WRITE PARENTH_OPEN STRING PARENTH_CLOSE                        { $$ = add_print_node(add_text_node($3));};

read: READ PARENTH_OPEN SYMBOL_ID PARENTH_CLOSE                     { $$ = add_read_node(add_variable_reference($3)); };

plot: PLOT PARENTH_OPEN SYMBOL_ID PARENTH_CLOSE                      { $$ = add_plot_node(add_variable_reference($3)); };

cv_op: SYMBOL_ID BIN_CV_OP CURLY_OPEN expression ',' expression CURLY_CLOSE { $$ = add_generic_cv_op_node(add_variable_reference($1),$2,0,$4,$6,0,0); }
    | SYMBOL_ID BIN_CV_OP_CHAR CURLY_OPEN expression ',' expression ',' ASCII CURLY_CLOSE { $$ = add_generic_cv_op_node(add_variable_reference($1),$2,$8,$4,$6,0,0); }
    | SYMBOL_ID TRI_CV_OP CURLY_OPEN expression ',' expression ',' expression CURLY_CLOSE { $$ = add_generic_cv_op_node(add_variable_reference($1),$2,0,$4,$6,$8,0); }
    | SYMBOL_ID UNI_CV_OP CURLY_OPEN expression CURLY_CLOSE { $$ = add_generic_cv_op_node(add_variable_reference($1),$2,0,$4,0,0,0); }
    | SYMBOL_ID QUAD_CV_OP_CHAR CURLY_OPEN expression ',' expression ','expression ',' expression ',' ASCII CURLY_CLOSE { $$ = add_generic_cv_op_node(add_variable_reference($1),$2,$12,$4,$6,$8,$10); }


expression: PARENTH_OPEN expression PARENTH_CLOSE              { $$ = add_expression_node(add_operation_node("("), $2, add_operation_node(")")); }
    | UNI_OP expression                     { $$ = add_expression_node(add_operation_node($1), $2, NULL); }
    | '-' expression           %prec UNI_OP { $$ = add_expression_node(add_operation_node("-"), $2, NULL); }
    | expression BIN_OP expression          { $$ = add_expression_node($1, add_operation_node($2), $3); }
    | expression '-' expression             { $$ = add_expression_node($1, add_operation_node("-"), $3); }
    | INTEGER                                { $$ = add_expression_node(add_integer_node($1), NULL, NULL); }
    | DOUBLE                                 { $$ = add_expression_node(add_double_node($1), NULL, NULL); }
    | SYMBOL_ID                           { $$ = add_variable_reference($1); }


%%
