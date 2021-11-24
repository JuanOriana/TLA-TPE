#ifndef _TREE_H_
#define _TREE_H_

#define TRUE 1
#define FALSE 0

typedef enum node_type
{
    TEXT_NODE = 0,
    NUMBER_NODE,
    OPERATION_NODE,
    VARIABLE_NODE,
    PRINT_NODE,
    READ_NODE,
    IF_NODE,
    WHILE_NODE,
    BLOCK_NODE,
    INSTRUCTION_NODE,
    NEGATION_NODE,
    EXPRESSION_NODE,
    LIST_NODE,
    CANVAS_NODE,
    PLOT_NODE,
    CV_OP_TYPE,
} node_type;

// Funciona como un wrapper generico (interfaz)

// REF
// TYPE             META            N1           N2         N3
// TEXT_NODE        texto           X            X          X
// NUMBER_NODE      numero          X            X          X
// OPERATION_NODE   operation       X            X          X
// PRINT_NODE       X               content      X          X
// READ_NODE        X               content      X          X
// IF_NODE          X               condition    then       otherwise
// WHILE_NODE       X               condition    first-i      X
// INSTRUCTION_NODE X               instruction  next-node         X
// NEGATION_NODE
// EXPRESSION_NODE  X               first        second     third
// LIST_NODE        X               reference    next
// CANVAS_NODE      X               width        height     X
// PLOT_NODE        X               canvas       X          X

typedef struct node_t
{
    node_type type;
    void *meta;
    void *meta2;
    struct node_t *next_1;
    struct node_t *next_2;
    struct node_t *next_3;

} node_t;

typedef struct variable_node
{
    node_type type;
    int declared;
    int var_type;
    char *name;
    node_t *value; // EXPRESSION_NODE TEXT_NODE NUMBER_NODE
} variable_node;

typedef struct cv_op_node_t
{
    node_type type;
    struct node_t *var;
    void *op;
    char *data;
    struct node_t *x1;
    struct node_t *x2;
    struct node_t *y1;
    struct node_t *y2;

} cv_op_node_t;

node_t *declare_variable_node(char *name, int var_type);
node_t *add_value_variable(node_t *var_node, node_t *expression);
node_t *assign_variable_node(char *name, node_t *expression);
node_t *add_variable_reference(char *name);

node_t *add_generic_cv_op_node(node_t *var, void *op, char *data, struct node_t *x1, struct node_t *y1, struct node_t *x2, struct node_t *y2);

node_t *add_expression_node(node_t *first, node_t *second, node_t *third);
node_t *add_instruction_node(node_t *node_t);
node_t *add_instruction_list_node(node_t *node_t);
node_t *add_element_to_list(node_t *list, node_t *element);

node_t *add_print_node(node_t *content);
node_t *add_read_node(node_t *content);
node_t *add_bin_cv_op_node(char *operation, node_t *canvas, node_t *first, node_t *second);
node_t *add_plot_node(node_t *content);

node_t *add_text_node(char *text);
node_t *add_number_node(char *number);
node_t *add_canvas_node(char *width, char *height);

node_t *add_block_node(node_t *list);
node_t *add_if_node(node_t *condition, node_t *then, node_t *otherwise);
node_t *add_while_node(node_t *condition, node_t *block);
node_t *add_operation_node(char *operation);

#endif
