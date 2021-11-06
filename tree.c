#include "./include/tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

node_t *add_generic_node(node_type node_type, char *meta, node_t *n1, node_t *n2, node_t *n3)
{
    node_t *node = malloc(sizeof(node));
    if (node == NULL)
    {
        printf("Hubo un error en el malloc");
        return NULL;
    }
    if (meta != NULL)
    {
        node->meta = malloc(strlen(meta) + 1);
        if (node->meta == NULL)
        {
            free(node);
            printf("Hubo un error en el malloc");
            return NULL;
        }
        strcpy(node->meta, meta);
    }
    else
    {
        node->meta = NULL;
    }
    node->type = node_type;
    node->next_1 = n1;
    node->next_2 = n2;
    node->next_3 = n3;

    return (node_t *)node;
}

node_t *add_expression_node(node_t *first, node_t *second, node_t *third)
{
    return add_generic_node(EXPRESSION_NODE, NULL, first, second, third);
}

node_t *declare_variable_node(char *name, int var_type)
{
    variable_node *node = calloc(1, sizeof(variable_node));
    if (node == NULL)
    {
        printf("Hubo un error en el malloc");
        return NULL;
    }
    node->type = VARIABLE_NODE;
    node->name = malloc(strlen(name) + 1);
    if (node->name == NULL)
    {
        free(node);
        printf("Hubo un error en el malloc");
        return NULL;
    }
    node->var_type = var_type;
    node->declared = TRUE;
    strcpy(node->name, name);

    return (node_t *)node;
}

node_t *add_value_variable(node_t *past_node, node_t *expression)
{
    variable_node *var_node = (variable_node *)past_node;
    variable_node *node = malloc(sizeof(variable_node));
    if (node == NULL)
    {
        printf("Hubo un error en el malloc");
        return NULL;
    }
    node->name = malloc(strlen(var_node->name) + 1);
    if (node->name == NULL)
    {
        free(node);
        printf("Hubo un error en el malloc");
        return NULL;
    }
    strcpy(node->name, var_node->name);
    node->value = expression;
    node->declared = TRUE;
    node->type = VARIABLE_NODE;
    node->var_type = var_node->var_type;

    free(var_node->name);
    free(var_node);
    return (node_t *)node;
}

node_t *add_variable_reference(char *name)
{
    variable_node *node = calloc(1, sizeof(variable_node));
    if (node == NULL)
    {
        printf("Hubo un error en el malloc");
        return NULL;
    }
    node->name = malloc(strlen(name) + 1);
    if (node->name == NULL)
    {
        free(node);
        printf("Hubo un error en el malloc");
        return NULL;
    }
    strcpy(node->name, name);
    node->declared = FALSE;
    node->type = VARIABLE_NODE;

    return (node_t *)node;
}

node_t *assign_variable_node(char *name, node_t *expression)
{
    variable_node *node = calloc(1, sizeof(variable_node));
    if (node == NULL)
    {
        printf("Hubo un error en el malloc");
        return NULL;
    }
    node->type = VARIABLE_NODE;
    node->name = malloc(strlen(name) + 1);
    if (node->name == NULL)
    {
        free(node);
        printf("Hubo un error en el malloc");
        return NULL;
    }
    node->declared = FALSE;
    node->value = expression;
    strcpy(node->name, name);

    return (node_t *)node;
}

node_t *add_instruction_list_node(node_t *node)
{
    return add_generic_node(INSTRUCTION_NODE, NULL, node, NULL, NULL);
}

node_t *add_element_to_list(node_t *list, node_t *element)
{

    if (element == NULL)
    {
        return (node_t *)list;
    }

    node_t *current_node = list;
    node_t *new_node = add_instruction_list_node(element);

    if (current_node->next_1 == NULL)
    {
        free(list);
        return (node_t *)new_node;
    }
    else if (new_node != NULL)
    {
        new_node->next_2 = current_node;
    }

    return (node_t *)new_node;
}

node_t *add_element_to_block(node_t *list, node_t *element)
{
    return (node_t *)add_element_to_list(list, element);
}

node_t *add_if_node(node_t *condition, node_t *then, node_t *otherwise)
{
    return add_generic_node(WHILE_NODE, NULL, condition, then, otherwise);
}

node_t *add_block_node(node_t *list)
{
    return add_generic_node(BLOCK_NODE, NULL, list, NULL, NULL);
}

node_t *add_instruction_node(node_t *node)
{
    return add_generic_node(INSTRUCTION_NODE, NULL, node, NULL, NULL);
}

node_t *add_print_node(node_t *content)
{
    return add_generic_node(PRINT_NODE, NULL, content, NULL, NULL);
}

node_t *add_read_node(node_t *content)
{
    return add_generic_node(READ_NODE, NULL, content, NULL, NULL);
}

node_t *add_text_node(char *text)
{
    return add_generic_node(TEXT_NODE, text, NULL, NULL, NULL);
}

node_t *add_number_node(char *number)
{
    return add_generic_node(NUMBER_NODE, number, NULL, NULL, NULL);
}

node_t *add_operation_node(char *operation)
{
    return add_generic_node(OPERATION_NODE, operation, NULL, NULL, NULL);
}

node_t *add_while_node(node_t *condition, node_t *block)
{
    return add_generic_node(WHILE_NODE, NULL, condition, block, NULL);
}