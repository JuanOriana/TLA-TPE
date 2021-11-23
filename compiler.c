#include "include/tree.h"
#include "include/var_validator.h"
#include "y.tab.h"
#include <stdio.h>
#include <stdlib.h>

int yyparse(node_t **program);
extern int yylineno;

extern FILE *yyin;
FILE *out;
node_t *program;

// #define ERROR(...)
//     fprintf(stderr, "\033[38;2;255;0;0mERROR: ");
//     fprintf(stderr, ##__VA_ARGS__);
//     fprintf(stderr, "\x1b[0m\n");
//     ;

int main(int argc, char **argv)
{

    if (argc == 1)
    {
        printf("Reading program from stdin\n");
    }
    else if (argc == 2)
    {
        yyin = fopen(argv[1], "r");
        if (yyin == NULL)
        {
            perror("Error opening input file");
            exit(-1);
        }
    }
    else
    {
        printf("Usage: %s [file]\n", argv[0]);
        exit(-1);
    }

    out = fopen("temp.c", "w+");
    if (out == NULL)
    {
        perror("Error creating temporary file");
        exit(-1);
    }

    fprintf(out, "int main() {\n");
    yyparse(&program);

    if (program && program->next_1 == NULL)
    {
        free(program);
        program = NULL;
    }
    if (check_and_set_variables(program)==-1) {
        exit(-1);
    }

    // read_tree(program, out);

    fprintf(out, "return 0;\n");
    fprintf(out, "\n}");
    fclose(out);

    system("gcc temp.c -lm -o program");

#if YYDEBUG == 0
    system("rm -rf temp.c");
#endif

    printf("\nSuccesfully parsed\n");
}

void yyerror(node_t **param, char *s)
{
    printf("%s at line %d", s, yylineno);

    exit(1);
}
