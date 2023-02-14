#ifndef COMPILER_PARSER_H
#define COMPILER_PARSER_H

#include "state.h"

#define IN_PRIORITY_BLOCK 1
#define NOT_IN_PRIORITY_BLOCK 0
#define IN_DEFINE_BLOCK 1
#define NOT_IN_DEFINE_BLOCK 0

typedef enum _parse_fsm_state_t {
    STATE_INITIAL,
    STATE_DEFINE,
    STATE_IDENTIFIER
} parse_fsm_state_t;

typedef enum _parse_state_t {
    STATE_RETURN,
    STATE_STRUCT_DEF,
    STATE_ENUM_DEF,
    STATE_TYPE_DEF,
    STATE_CODE_BLOCK,
    STATE_PRIORITY_EXEC,
    STATE_TYPE,
    STATE_DECL

} parse_state_t;

typedef enum _node_type_t {
    NODE_VAR_ASSIGN,
    NODE_VAR_DECL,
    NODE_VAR_RETRIEVE,
    NODE_FUNC_DECL,
    NODE_FUNC_RETURN,
    NODE_FUNC_CALL,
    NODE_FUNC_PARAM,
    NODE_INTEGER_LITERAL,
    NODE_CHAR_LITERAL,
    NODE_TYPE_DEFINE,
    NODE_STRUCT_DEFINE,
    NODE_ENUM_DEFINE
} node_type_t;

typedef struct _ast_node {
    node_type_t type;
    char *val;
    struct _ast_node *left;
    struct _ast_node *right;
} ast_node;

ast_node *create_node(node_type_t type, ast_node *left, ast_node *right);

void destroy_node(ast_node *nd);

void print_ast(ast_node *nd, int indent, int l);

char *match_type(char *s);

ast_node *parse(state *st, int in_def_block, int in_prio_block);

ast_node *parse2(state *st, parse_fsm_state_t state);

#endif // COMPILER_PARSER_H