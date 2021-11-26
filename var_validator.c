
#include "./include/var_validator.h"
#include "y.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VAR_NAME_LENGTH 256

#define ERROR(...)                                \
    fprintf(stderr, "\033[38;2;255;0;0mERROR: "); \
    fprintf(stderr, ##__VA_ARGS__);               \
    fprintf(stderr, "\x1b[0m\n");                 \
    ;

int error = 0;

typedef struct var_node
{
    int var_type;
    char name[MAX_VAR_NAME_LENGTH];
    int references;
    int assignations_left;
    struct var_node *next;
} var_node;

var_node *create_var_node(int type, char *name, int is_constant);
void add_to_list(var_node **list, var_node *element);
void check_and_set_variables_internal(node_t *tree, var_node **var_list);
var_node *free_list(var_node *list);
int check_if_exists(var_node *list, char *name, var_node **found);
void check_and_set_variables_rec(node_t *node, var_node **var_list);
void check_var_types_in_value(int type, variable_node *variable_node_var, var_node *var_list);
int check_var_type_in_expression(int type, node_t *expr, var_node *var_list);
int check_var_type_in_expression_rec(int type, node_t *node, var_node *var_list, node_t *parent);
int check_var_type_in_cv_ops(int type, cv_op_node_t *node, var_node *var_list);
static char *get_type_from_enum(int type);

int check_and_set_variables(node_t *tree)
{ //inicializa la lista con un pseudo nodo para no pasar null
    var_node varinit;
    varinit.references = 2;
    varinit.next = NULL;
    varinit.var_type = -1;
    var_node *var_list = &varinit;
    check_and_set_variables_internal(tree, &var_list);
    return error;
}

void check_and_set_variables_internal(node_t *tree, var_node **var_list)
{
    node_t *aux = tree;
    while (aux != NULL)
    {
        node_t *node = (node_t *)aux->next_1;
        check_and_set_variables_rec(node, var_list);
        aux = aux->next_2;
    }
    if (var_list != NULL)
    {
        (*var_list) = free_list(*var_list);
    }
}

void check_and_set_variables_rec(node_t *node, var_node **var_list)
{
    switch (node->type)
    {
    case VARIABLE_NODE:;
        var_node *found = NULL;

        variable_node *variable_node_var = (variable_node *)node;
        if (variable_node_var->declared)
        {
            if (check_if_exists(*var_list, variable_node_var->name, &found) != -1)
            {
                ERROR("Variable %s already declared \n", variable_node_var->name);
                error = -1;
            }
            add_to_list(var_list, create_var_node(variable_node_var->var_type, variable_node_var->name, variable_node_var->is_constant));
        }
        else
        {
            int type = check_if_exists(*var_list, variable_node_var->name, &found);
            if (type == -1)
            {
                ERROR("Variable %s is not declared yet\n", variable_node_var->name);
                error = -1;
            }
            else if (found->assignations_left == 0)
            {
                ERROR("Variable %s is final and yet trying to be assigned a value\n", variable_node_var->name);
                error = -1;
            }
            else if (found->assignations_left > 0)
            {
                found->assignations_left--;
            }
            variable_node_var->var_type = type;
        }
        if (variable_node_var->value != NULL)
        {
            if (!variable_node_var->declared && variable_node_var->var_type == CANVAS_TYPE)
            {
                ERROR("%s is assigned a new canvas type. Canvas types are finals and cannot be assigned\n", variable_node_var->name);
                error = -1;
            }
            check_var_types_in_value(variable_node_var->var_type, variable_node_var, *var_list);
        }
        break;
    case PRINT_NODE: //el caso donde recibis algo como write <algo>
        ;
        switch (node->next_1->type)
        {
        case VARIABLE_NODE:
            check_and_set_variables_rec((node_t *)node->next_1, var_list);
            break;

        case EXPRESSION_NODE:
            if (!check_var_type_in_expression(INTEGER_TYPE, node->next_1, *var_list))
            {
                ERROR("Variable in write is type text inside expression\n");
                error = -1;
            }
            break;

        case TEXT_NODE:
            //va vacio porque no hay variables aca dentro
            break;

        default:
            ERROR("UNKNOWN AST ERROR");
            error = -1;
            break;
        }
        break;

    case READ_NODE: //el caso donde es read <algo>
        switch (node->next_1->type)
        {
        case VARIABLE_NODE: //read variable
            check_and_set_variables_rec(node->next_1, var_list);
            int type = ((variable_node *)node->next_1)->var_type;
            if (type != INTEGER_TYPE && type != DOUBLE_TYPE)
            {
                ERROR("Variable %s in read not of type numeric \n", ((variable_node *)node->next_1)->name);
                error = -1;
            }
            break;

        default:
            ERROR("UNKNOWN AST ERROR");
            error = -1;
            break;
        }
        break;
    case PLOT_NODE:
        if (node->next_1->type == VARIABLE_NODE)
        {
            check_and_set_variables_rec(node->next_1, var_list);
            if (error != -1 && ((variable_node *)node->next_1)->var_type != CANVAS_TYPE)
            {
                ERROR("Variable %s of type %s is trying to be plotted without being a canvas \n", ((variable_node *)node->next_1)->name,
                      get_type_from_enum(((variable_node *)node->next_1)->var_type));
                error = -1;
            }
        }
        else
        {
            ERROR("UNKNOWN AST ERROR");
            error = -1;
        }
        break;
    case IF_NODE:
        if (!check_var_type_in_expression(INTEGER_TYPE, node->next_1, *var_list))
        { // miro que la condicion sea valida
            ERROR("An if condition may only be numeric\n");
            error = -1;
        }
        (*var_list)->references++;
        check_and_set_variables_internal(node->next_2->next_1, var_list); //busco variables en el bloque del if
        ;
        if (node->next_3 != NULL) //else es opcional
        {
            (*var_list)->references++;
            check_and_set_variables_internal(node->next_3->next_1, var_list); //busco variables en el bloque del else
        }

        break;
    case WHILE_NODE:
        if (!check_var_type_in_expression(INTEGER_TYPE, node->next_1, *var_list))
        { //buscar variables en condicion
            ERROR("A while condition may only be numeric\n");
            error = -1;
        }
        (*var_list)->references++;
        check_and_set_variables_internal(node->next_2->next_1, var_list); //buscar variables en el bloque
        break;
    case RETURN_NODE:
        if (!check_var_type_in_expression(INTEGER_TYPE, node->next_1, *var_list))
        { //buscar variables en condicion
            ERROR("A return statement may only be numeric\n");
            error = -1;
        }
        break;
    case CV_OP_NODE:;
        cv_op_node_t *op_node = (cv_op_node_t *)node;
        check_and_set_variables_rec(op_node->var, var_list);
        variable_node *op_node_var = (variable_node *)op_node->var;
        if (error != -1 && (op_node_var->var_type != CANVAS_TYPE))
        {
            ERROR("Variable %s of type %s is trying to be used in function %s without being a canvas \n", op_node_var->name,
                  get_type_from_enum(op_node_var->var_type), (char *)op_node->op);
            error = -1;
        }
        if (!check_var_type_in_cv_ops(INTEGER_TYPE, op_node, *var_list))
        { //buscar variables en condicion
            ERROR("Every coordenate parameter in cv operation %s should be numeric\n", (char *)op_node->op);
            error = -1;
        }
        //  *var_list=free_list(*var_list);
        break;
    default:
        ERROR("UNKNOWN NODE");
        break;
    }
}

void check_var_types_in_value(int type, variable_node *variable_node_var, var_node *var_list)
{

    switch (variable_node_var->value->type)
    {
    case TEXT_NODE:;
        if (variable_node_var->var_type != STRING_TYPE)
        {
            ERROR("Variable %s is assigned a string when its actually a %s\n",
                  variable_node_var->name, get_type_from_enum(variable_node_var->var_type));
            error = -1;
        }
        break;
    case EXPRESSION_NODE:;
        if (!check_var_type_in_expression(type, (node_t *)variable_node_var->value, var_list))
        {
            ERROR("Variable %s is trying to be assigned an expresion with non-numeral values\n", variable_node_var->name);
            error = -1;
        }
        break;
    case VARIABLE_NODE:;
        var_node *found = NULL;
        int type = check_if_exists(var_list, ((variable_node *)variable_node_var->value)->name, &found);
        if (type == -1)
        {
            ERROR("Variable %s not declared yet \n", ((variable_node *)variable_node_var->value)->name);
            error = -1;
        }
        if (variable_node_var->var_type == 0)
        {
            variable_node_var->var_type = type;
        }
        if (type != variable_node_var->var_type)
        {
            ERROR("Variable %s of type %s is trying to be assigned variable %s of type %s \n",
                  variable_node_var->name, get_type_from_enum(variable_node_var->var_type),
                  ((variable_node *)variable_node_var->value)->name, get_type_from_enum(type));
            error = -1;
        }

        break;
    default:
        ERROR("UNEXPECTED ERROR\n");
        break;
    }
}

int check_var_type_in_expression(int type, node_t *expr, var_node *var_list)
{ // expresion tiene 3 espacios que no pueden ser todos nulos, esta llamada rompe la busqueda en cada uno
    if (expr->type == VARIABLE_NODE)
    {
        return check_var_type_in_expression_rec(type, expr, var_list, expr);
    }
    return check_var_type_in_expression_rec(type, expr->next_1, var_list, expr) &&
           check_var_type_in_expression_rec(type, expr->next_2, var_list, expr) &&
           check_var_type_in_expression_rec(type, expr->next_3, var_list, expr);
}

int check_var_type_in_cv_ops(int type, cv_op_node_t *node, var_node *var_list)
{
    return check_var_type_in_expression_rec(type, node->x, var_list, (node_t *)node) &&
           check_var_type_in_expression_rec(type, node->y, var_list, (node_t *)node) &&
           check_var_type_in_expression_rec(type, node->axis, var_list, (node_t *)node) &&
           check_var_type_in_expression_rec(type, node->axis2, var_list, (node_t *)node);
}

int check_var_type_in_expression_rec(int type, node_t *node, var_node *var_list, node_t *parent)
{ //resuelve el valor de expresiones
    if (node == NULL)
    {
        return TRUE;
    }
    switch (node->type)
    {
    case VARIABLE_NODE:;
        var_node *found = NULL;
        variable_node *variable_node_var = (variable_node *)node;
        int type_var = check_if_exists(var_list, variable_node_var->name, &found);
        if (type_var == -1)
        {
            ERROR("Variable not declared yet %s\n", variable_node_var->name);
            error = -1;
        }
        variable_node_var->var_type = type_var;
        //Normalize numeric values
        if (type_var == DOUBLE_TYPE)
        {
            if ((long)parent->meta2 == 0)
                parent->meta2 = (void *)1;
            type_var = INTEGER_TYPE;
        }
        if (type == DOUBLE_TYPE)
            type = INTEGER_TYPE;
        return type_var == type;
        break;
    case TEXT_NODE:
        return STRING_TYPE == type;
        break;
    case DOUBLE_NODE:
        //Aviso que incluye un double
        if ((long)parent->meta2 == 0)
            parent->meta2 = (void *)1;
    case INTEGER_NODE:
    case OPERATION_NODE:
        //Exceptuando estas operaciones, TODO el resto asegura un resultado integer (flag en -1)
        if (strcmp(node->meta, "(") != 0 && strcmp(node->meta, ")") != 0 && strcmp(node->meta, "+") != 0 && strcmp(node->meta, "-") != 0 && strcmp(node->meta, "/") != 0 && strcmp(node->meta, "*") != 0)
        {
            parent->meta2 = (void *)-1;
        }
        return INTEGER_TYPE == type || DOUBLE_TYPE == type;
        break;
    case CANVAS_NODE:
        return CANVAS_TYPE == type;
        break;
    case EXPRESSION_NODE:;
        int ret = check_var_type_in_expression(type, node, var_list);
        if ((long)node->meta2 == 1 && (long)parent->meta2 == 0)
        {
            parent->meta2 = (void *)1;
        }
        return ret;
        break;
    default:
        ERROR("UNEXPECTED ERROR\n");
        break;
    }
    return FALSE; //SHOULD NOT BE HERE
}

var_node *create_var_node(int type, char *name, int is_constant)
{ //inicializa un nodo de la lista de variables, arranca con 0 referencias para poder ser borrado en caso de ninguna referencia adicional
    var_node *new = malloc(sizeof(var_node));
    new->var_type = type;
    strcpy(new->name, name);
    new->references = 0;
    new->next = NULL;
    new->assignations_left = is_constant ? 1 : -1;
    return new;
}

void add_to_list(var_node **list, var_node *element)
{ //pone un nuevo nodo a la cabeza de la lista
    if (*list != NULL)
    {
        element->next = *list;
    }
    *list = element;
}

var_node *free_list(var_node *list)
{ //libera nodos de la lista hasta que tengan mas de 1 referencia, en donde deja de liberar y pone el nodo en el comienzo de la lista
    if (list == NULL)
    {
        return NULL;
    }

    var_node *current = list;
    while (current != NULL && current->references < 1)
    {
        var_node *next = current->next;
        free(current);
        current = next;
    }
    if (current != NULL)
    {
        current->references--;
    }
    return current;
}

int check_if_exists(var_node *list, char *name, var_node **found)
{ //recorre la lista de variables y compara nombres, si no enuentra la variable devuelve -1
    var_node *current = list;
    while (current != NULL)
    {
        var_node *next = current->next;
        if (strcmp(current->name, name) == 0)
        {
            *found = current;
            return current->var_type;
        }
        current = next;
    }
    return -1;
}

static char *get_type_from_enum(int type)
{
    switch (type)
    {
    case STRING_TYPE:
        return "string";
    case INTEGER_TYPE:
        return "number";
    case DOUBLE_TYPE:
        return "double";
    case CANVAS_TYPE:
        return "canvas";
    default:
        return "unknown";
    }
}