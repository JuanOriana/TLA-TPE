#ifndef _AST_H_
#define _AST_H_

#define TRUE 1
#define FALSE 0

//Referencia para idea general: https://github.com/habi-a/C-Interpretor/blob/master/src/ast.c

typedef enum node_type
{
    STRING_NODE,
    INTEGER_NODE,
    DOUBLE_NODE,
    OPERATION_NODE,
    VARIABLE_NODE,
    WRITE_NODE,
    READ_NODE,
    IF_NODE,
    WHILE_NODE,
    BLOCK_NODE,
    INSTRUCTION_NODE,
    EXPRESSION_NODE,
    CANVAS_NODE,
    PLOT_NODE,
    CV_OP_NODE,
    RETURN_NODE
} node_type;

// Funciona como un wrapper generico (interfaz)

// REF
// TYPE             META            N1           N2         N3          META2
// STRING_NODE      texto           X            X          X           X
// INTEGER_NODE     numero          X            X          X           X
// DOUBLE_NODE      numero          X            X          X           X
// OPERATION_NODE   operation       X            X          X           (0 si no contiene floats y 1 si si)
// WRITE_NODE       X               content      X          X           X
// READ_NODE        X               content      X          X           X
// IF_NODE          X               condition    then       otherwise   X
// WHILE_NODE       X               condition    first-i      X         X
// INSTRUCTION_NODE X               instruction  next-node    X         X
// EXPRESSION_NODE  X               first        second     third       X
// CANVAS_NODE      widht            X           X          X           height
// PLOT_NODE        X               canvas       X          X           x
// RETURN_NODE      X               return_val   X          X           x

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
    int is_constant;
    int var_type;
    char *name;
    node_t *value;
} variable_node;

typedef struct cv_op_node_t
{
    node_type type;
    struct node_t *var;
    void *op;
    char *data;
    struct node_t *x;
    struct node_t *y;
    struct node_t *axis;
    struct node_t *axis2;

} cv_op_node_t;

node_t *declare_variable_node(char *name, int var_type);
node_t *declare_constant_variable_node(char *name, int var_type);
node_t *add_value_variable(node_t *var_node, node_t *expression);
node_t *assign_variable_node(char *name, node_t *expression);
node_t *add_variable_reference(char *name);
node_t *add_generic_cv_op_node(node_t *var, void *op, char *data, node_t *x, node_t *y, node_t *axis, node_t *axis2);
node_t *add_expression_node(node_t *first, node_t *second, node_t *third);
node_t *add_instruction_node(node_t *node_t);
node_t *add_instruction_list_node(node_t *node_t);
node_t *add_element_to_list(node_t *list, node_t *element);
node_t *add_write_node(node_t *content);
node_t *add_read_node(node_t *content);
node_t *add_bin_cv_op_node(char *operation, node_t *canvas, node_t *first, node_t *second);
node_t *add_plot_node(node_t *content);
node_t *add_string_node(char *text);
node_t *add_integer_node(char *integer);
node_t *add_double_node(char *floating);
node_t *add_canvas_node(char *width, char *height);
node_t *add_block_node(node_t *list);
node_t *add_if_node(node_t *condition, node_t *then, node_t *otherwise);
node_t *add_while_node(node_t *condition, node_t *block);
node_t *add_return_node(node_t *expression);
node_t *add_operation_node(char *operation);

#endif
