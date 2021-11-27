#include "include/ast.h"
#include "include/var_validator.h"
#include "include/ast_to_c.h"

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
        printf("Leyendo de entrada estandar\n");
    }
    else if (argc == 2)
    {
        yyin = fopen(argv[1], "r");
        if (yyin == NULL)
        {
            perror("No se pudo abrir el archivo");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        printf("Uso: %s [archivo.can]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    out = fopen("aux.c", "w+");
    if (out == NULL)
    {
        perror("Error creando el archivo temporal");
        exit(EXIT_FAILURE);
    }

    fprintf(out, "#include <stdio.h>\n#include \"./include/canvas_utils.h\"\nint main() {\n");

    yyparse(&program);

    if (program && program->next_1 == NULL)
    {
        free(program);
        program = NULL;
    }

    if (check_and_set_variables(program) == -1)
    {
        exit(-1);
    }

    tree_to_c(program, out);

    fprintf(out, "return 0;\n");
    fprintf(out, "\n}");
    fclose(out);

    system("gcc aux.c canvas_utils.c -lm -o program");
    system("rm aux.c");

    printf("\nSuccesfully parsed\n");
}

void yyerror(node_t **param, char *err_msg)
{
    printf("%s at line %d", err_msg, yylineno);
    exit(1);
}
