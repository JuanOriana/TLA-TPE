#include "include/ast.h"
#include "include/ast_to_c.h"

#include "y.tab.h"
#include <stdlib.h>
#include <string.h>

#define P(...) fprintf(output, ##__VA_ARGS__);
FILE *output;

typedef struct canvas_ref
{
    char name[128];
    struct canvas_ref *next;
} canvas_ref;

canvas_ref *canvas_list;

void yyerror(node_t **program, char *s);

void write_to_c(node_t *node);
void read_to_c(node_t *node);
void plot_to_c(node_t *node);
void cv_op_to_c(node_t *node);
void variable_to_c(node_t *node);
void expresion_to_c(node_t *node);
void instruction_list_to_c(node_t *list);
void if_to_c(node_t *node);
void while_to_c(node_t *node);
void free_text_node(node_t *node);
void free_integer_node(node_t *node);
void free_operation_node(node_t *node);

void tree_to_c(node_t *program, FILE *file)
{

    output = file;

    instruction_list_to_c(program);

    canvas_ref *aux = canvas_list;
    while (aux != NULL)
    {
        canvas_ref *next = aux->next;
        P("free(%s.canvas_mat);\n", aux->name);
        free(aux);
        aux = next;
    }
}

void instruction_list_to_c(node_t *list)
{
    node_t *aux = list;
    while (aux != NULL)
    {
        node_t *curr = aux->next_1;
        switch (curr->type)
        {
        case VARIABLE_NODE:
            variable_to_c(curr);
            break;
        case PRINT_NODE:
            write_to_c(curr);
            break;
        case READ_NODE:
            read_to_c(curr);
            break;
        case IF_NODE:
            if_to_c(curr);
            break;
        case WHILE_NODE:
            while_to_c(curr);
            break;
        case PLOT_NODE:
            plot_to_c(curr);
            break;
        case CV_OP_NODE:
            cv_op_to_c(curr);
            break;
        case RETURN_NODE:
            P("return");
            expresion_to_c(curr->next_1);
            P(" ;");
            break;
        default:
            printf("UNEXPECTED ERROR");
            break;
        }
        free(curr);
        node_t *next = aux->next_2;
        free(aux);
        aux = next;
    }
}

void variable_to_c(node_t *node)
{
    variable_node *var = (variable_node *)node;

    if (var->declared == TRUE)
    {
        // Es una declaración
        switch (var->var_type)
        {
        case INTEGER_TYPE:
            P("int %s", var->name);
            break;
        case DOUBLE_TYPE:
            P("double %s", var->name);
            break;
        case STRING_TYPE:
            P("char * %s", var->name);
            break;
        case CANVAS_TYPE:
            P("canvas_t %s", var->name);
            canvas_ref *cv_ref = malloc(sizeof(canvas_ref));
            strcpy(cv_ref->name, var->name);
            cv_ref->next = canvas_list;
            canvas_list = cv_ref;
            break;
        default:
            break;
        }
    }
    else
    {
        // Es una asignacion/referenciación
        P("%s", (var->name));
    }
    free(var->name);

    // si la variable esta asignada
    if (var->value != NULL)
    {
        P(" = ");
        if (var->var_type == INTEGER_TYPE)
            P("(int)");
        if (var->var_type == DOUBLE_TYPE)
            P("(double)");

        if (var->value->type == EXPRESSION_NODE)
        {
            expresion_to_c(var->value);
        }
        else if (var->value->type == TEXT_NODE || var->value->type == INTEGER_NODE || var->value->type == DOUBLE_NODE)
        {
            P("%s", (char *)var->value->meta);
            free(var->value->meta);
        }
        else if (var->value->type == VARIABLE_NODE)
        {
            variable_node *var_node = (variable_node *)var->value;
            P("%s", var_node->name);
            free(var_node->name);
        }
        else if (var->value->type == CANVAS_NODE)
        {
            P("{.canvas_mat=malloc(%s*%s), .width=%s, .height=%s, .color=CV_WHITE}", (char *)var->value->meta, (char *)var->value->meta2,
              (char *)var->value->meta, (char *)var->value->meta2);
            free(var->value->meta);
            free(var->value->meta2);
        }
        free(var->value);
    }
    P(";\n");
}

void write_to_c(node_t *node)
{
    // dependiendo del tipo de contenido del print se corre una función distinta

    switch (node->next_1->type)
    {
    case VARIABLE_NODE:;
        variable_node *var = (variable_node *)(node->next_1);
        if (var->var_type == INTEGER_TYPE)
            P("printf(\"%%d\",(int)(%s));\n", var->name);
        if (var->var_type == DOUBLE_TYPE)
            P("printf(\"%%lf\",(double)(%s));\n", var->name);
        if (var->var_type == STRING_TYPE)
            P("printf(\"%%s\", %s);\n", var->name);
        free(var->name);
        break;
    case EXPRESSION_NODE:
        if ((long)node->next_1->meta2 == 1)
        {
            P("printf(\"%%f\",");
        }
        else
        {
            P("printf(\"%%d\",");
        }
        expresion_to_c(node->next_1);
        P(");\n");
        break;
    case TEXT_NODE:;
        P("printf(\"%%s\", %s);\n", (char *)node->next_1->meta);
        free(node->next_1->meta);
        break;
    default:
        break;
    }
    free(node->next_1);
}

void read_to_c(node_t *node)
{
    // solo se puede leer tipos númericos
    if (node->next_1->type == VARIABLE_NODE)
    {
        variable_node *var = (variable_node *)(node->next_1);
        if (var->var_type == INTEGER_TYPE)
        {
            P("scanf(\"%%d\", &%s);", var->name);
        }
        else if (var->var_type == DOUBLE_TYPE)
        {
            P("scanf(\"%%lf\", &%s);", var->name);
        }
        free(var->name);
    }
    free(node->next_1);
}

void plot_to_c(node_t *node)
{
    if (node->next_1->type == VARIABLE_NODE)
    {
        variable_node *var = (variable_node *)(node->next_1);
        P("canvas_plot(%s);\n", var->name);
        free(var->name);
    }
    free(node->next_1);
}

void cv_op_to_c(node_t *node)
{
    cv_op_node_t *op_node = (cv_op_node_t *)node;
    variable_node *var = (variable_node *)(op_node->var);
    //x e y coords.
    if (strcmp(op_node->op, "dot") == 0)
    {
        P("cv_set_char_in_coords(%s,'*',", var->name);
        expresion_to_c(op_node->x);
        P(",");
        expresion_to_c(op_node->y);
        P(");")
    }
    else if (strcmp(op_node->op, "char") == 0)
    {
        P("cv_set_char_in_coords(%s,%s,", var->name, op_node->data);
        expresion_to_c(op_node->x);
        P(",");
        expresion_to_c(op_node->y);
        P(");")
    }
    //X = left_bound Y = right_bound
    else if (strcmp(op_node->op, "hor") == 0)
    {
        P("cv_horizontal_line(%s,", var->name);
        expresion_to_c(op_node->x);
        P(",");
        expresion_to_c(op_node->y);
        P(",");
        expresion_to_c(op_node->axis);
        P(");")
    }
    //X = low_bound Y = high_bound
    else if (strcmp(op_node->op, "vert") == 0)
    {
        P("cv_vertical_line(%s,", var->name);
        expresion_to_c(op_node->x);
        P(",");
        expresion_to_c(op_node->y);
        P(",");
        expresion_to_c(op_node->axis);
        P(");")
    }
    //X = color
    else if (strcmp(op_node->op, "color") == 0)
    {
        P("cv_set_color(&%s,", var->name);
        expresion_to_c(op_node->x);
        P(");")
    }
    // X=x1 Y=y1 axis= x2 axis2 = y2
    else if (strcmp(op_node->op, "fill") == 0)
    {
        P("cv_fill_area(%s,%s,", var->name, op_node->data);
        expresion_to_c(op_node->x);
        P(",");
        expresion_to_c(op_node->y);
        P(",");
        expresion_to_c(op_node->axis);
        P(",");
        expresion_to_c(op_node->axis2);
        P(");")
    }
    P("\n");
    free(op_node->var);
}
void switch_expresion_to_c(node_t *node)
{
    switch (node->type)
    {
    case EXPRESSION_NODE:
        expresion_to_c(node);
        break;
    case VARIABLE_NODE:;
        variable_node *var = (variable_node *)node;
        P(" %s ", var->name);
        free(var->name);
        break;
    case TEXT_NODE:
    case INTEGER_NODE:
    case DOUBLE_NODE:
    case OPERATION_NODE:
        P(" %s ", (char *)node->meta);
        free(node->meta);
        break;
    default:
        break;
    }
}

void expresion_to_c(node_t *exp)
{
    //May not be an expression! beware
    if (exp->type == VARIABLE_NODE)
    {
        switch_expresion_to_c(exp);
        return;
    }
    int integral = 0;
    if (exp && exp->next_2 && exp->next_2->meta)
    {
        char *meta_str = (char *)exp->next_2->meta;
        integral = strcmp(meta_str, "%") == 0;
    }
    if (exp->next_1 != NULL)
    {
        if (integral)
            P("(int)");
        switch_expresion_to_c(exp->next_1);
        free(exp->next_1);
    }

    if (exp->next_2 != NULL)
    {
        switch_expresion_to_c(exp->next_2);
        free(exp->next_2);
    }

    if (exp->next_3 != NULL)
    {
        if (integral)
            P("(int)");
        switch_expresion_to_c(exp->next_3);
        free(exp->next_3);
    }
}

void if_to_c(node_t *node)
{
    P("if (");
    // se imprime la expression
    expresion_to_c(node->next_1);
    free(node->next_1);
    P(") {\n");
    node_t *block = node->next_2;
    // se imprime la lista de instrucciones dentro del bloque del then del if
    instruction_list_to_c(block->next_1);
    free(block);
    // si tiene un else
    if (node->next_3 != NULL)
    {
        P("\n} else {\n");
        block = node->next_3;
        // se imprime la lista de instrucciones dentro del bloque del otherwise del if
        instruction_list_to_c(block->next_1);
        free(block);
    }
    P("}\n");
}

void while_to_c(node_t *node)
{
    P("while (");
    // se imprime la expression
    expresion_to_c(node->next_1);
    free(node->next_1);
    P(") {\n");
    // se imprime la lista de instrucciones dentro del bloque del then del while
    instruction_list_to_c(node->next_2->next_1);
    free(node->next_2);
    P("}\n");
}
