#include "include/ast.h"
#include "include/var_validator.h"
#include "include/ast_to_c.h"
#include <getopt.h>

#include "y.tab.h"
#include <stdio.h>
#include <stdlib.h>

int yyparse(node_t **program);
extern int yylineno;

extern FILE *yyin;
FILE *out;
node_t *program;
char *out_file = "program";

extern char *optarg;
extern int optind, opterr, optopt;

int main(int argc, char **argv)
{
    int c;
    while (1)
    {
        c = getopt(argc, argv, "o:");
        if (c == -1)
            break;
        if (c == 'o')
        {
            out_file = optarg;
        }
    }
    if (optind >= argc)
    {
        printf("Reading program from STDIN\n");
    }
    else if (optind < argc - 1)
    {
        if (optind < argc - 1)
        {
            fprintf(stderr, "Usage: %s [-o] [in.file]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        yyin = fopen(argv[optind], "r");
        if (yyin == NULL)
        {
            perror("File can not be opened");
            exit(EXIT_FAILURE);
        }
    }

    // Evaluacion semantica y construccion de AST
    yyparse(&program);

    if (program && program->next_1 == NULL)
    {
        free(program);
        program = NULL;
    }

    // Validacion simbolica
    if (validate_vars(program) == -1)
    {
        exit(-1);
    }

    // Llevado del AST a un .c
    out = fopen("aux.c", "w+");
    if (out == NULL)
    {
        perror("Error creating auxiliary file");
        exit(EXIT_FAILURE);
    }

    fprintf(out, "#include <stdio.h>\n#include \"./include/canvas_utils.h\"\nint main() {\n");

    tree_to_c(program, out);
    fprintf(out, "return 0;\n");
    fprintf(out, "\n}");
    fclose(out);

    // Compilacion del .c
    char compiling_line[512];
    sprintf(compiling_line, "gcc aux.c canvas_utils.c -lm -o %s", out_file);
    system(compiling_line);
    system("rm aux.c");

    printf("\nParsed successfully\n");
}

void yyerror(node_t **param, char *err_msg)
{
    printf("%s at line %d", err_msg, yylineno);
    exit(1);
}
