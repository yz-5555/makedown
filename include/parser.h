#ifndef PAR_H
#define PAR_H

#include "utils.h"

typedef enum NodeType {
    NT_HEADER
} NodeType;

typedef struct ASTNode {
    NodeType type;
    char value[VALUE_CAPACITY];
    struct ASTNode *children;
    struct ASTNode *next;
} ASTNode;

#endif // PAR_H
