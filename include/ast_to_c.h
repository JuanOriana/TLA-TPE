
#ifndef _TREE_TO_C_H_
#define _TREE_TO_C_H_

#include <stdio.h>

// Lleva el AST a una representacion en C
void tree_to_c(node_t *program, FILE *file);

#endif