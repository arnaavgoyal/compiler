#ifndef COMPILER_PARSER_H
#define COMPILER_PARSER_H

#include "state.h"

#define IN_PRIORITY_BLOCK 1
#define NOT_IN_PRIORITY_BLOCK 0
#define IN_DEFINE_BLOCK 1
#define NOT_IN_DEFINE_BLOCK 0

typedef enum _operator_type_t {
    OPERATOR_POSTFIX_INCREMENT,
    OPERATOR_POSTFIX_DECREMENT,
    OPERATOR_FUNCTION_CALL,
    OPERATOR_ARRAY_SUBSCRIPT,
    OPERATOR_MEMBER_ACCESS,
    OPERATOR_INDIRECT_MEMBER_ACCESS,

    OPERATOR_PREFIX_INCREMENT,
    OPERATOR_PREFIX_DECREMENT,
    OPERATOR_UNARY_PLUS,
    OPERATOR_UNARY_MINUS,
    OPERATOR_LOGICAL_NOT,
    OPERATOR_BITWISE_NOT,
    OPERATOR_TYPE_CAST,
    OPERATOR_INDIRECTION,
    OPERATOR_ADDRESS_OF,
    OPERATOR_SIZEOF,

    OPERATOR_MULTIPLY,
    OPERATOR_DIVIDE,
    OPERATOR_MODULO,

    OPERATOR_ADD,
    OPERATOR_SUBTRACT,

    OPERATOR_BITWISE_LEFT_SHIFT,
    OPERATOR_BITWISE_RIGHT_SHIFT,

    OPERATOR_LESS_THAN,
    OPERATOR_LESS_THAN_OR_EQUAL,
    OPERATOR_GREATER_THAN,
    OPERATOR_GREATER_THAN_OR_EQUAL,

    OPERATOR_EQUAL,
    OPERATOR_NOT_EQUAL,

    OPERATOR_BITWISE_AND,

    OPERATOR_BITWISE_XOR,

    OPERATOR_BITWISE_OR,

    OPERATOR_LOGICAL_AND,

    OPERATOR_LOGICAL_OR,

    OPERATOR_TERNARY,

    OPERATOR_ASSIGN,
    OPERATOR_ADD_ASSIGN,
    OPERATOR_SUBTRACT_ASSIGN,
    OPERATOR_MULTIPLY_ASSIGN,
    OPERATOR_DIVIDE_ASSIGN,
    OPERATOR_MODULO_ASSIGN,
    OPERATOR_BITWISE_LEFT_SHIFT_ASSIGN,
    OPERATOR_BITWISE_RIGHT_SHIFT_ASSIGN,
    OPERATOR_BITWISE_AND_ASSIGN,
    OPERATOR_BITWISE_XOR_ASSIGN,
    OPERATOR_BITWISE_OR_ASSIGN,

    OPERATOR_COMMA
} operator_type_t;

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
    NODE_ENUM_DEFINE,
    NODE_OPERATOR,
    NODE_IDENTIFIER
} node_type_t;

typedef struct _ast_node {
    node_type_t type;
    char *val;
    int id;
    struct _ast_node *left;
    struct _ast_node *right;
} ast_node;

ast_node *create_node(node_type_t type, ast_node *left, ast_node *right);

void destroy_node(ast_node *nd);

void print_ast(ast_node *nd, int indent, int l);

char *match_type(char *s);

ast_node *unary_eval(state *st, char *end);

ast_node *parse(state *st, int in_def_block, int in_prio_block);

ast_node *parse2(state *st, parse_fsm_state_t state);

#endif // COMPILER_PARSER_H