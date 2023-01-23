#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "state.h"
#include "tokenizer.h"

#include "parser.h"

char *keywords[] = {"return", "struct", "enum", "typedef",
                    "if", "else if", "else",
                    "for", "while", "do"};

char *types[] = {"int8", "int16", "int32", "int64"};

ast_node *create_node(node_type_t type, ast_node *left, ast_node *right) {
    ast_node *nd = malloc(sizeof(ast_node));
    nd->type = type;
    nd->val = malloc(MAX_IDENT_TOKEN_LEN + 1);
    nd->left = left;
    nd->right = right;
    return nd;
}

void destroy_node(ast_node *nd) {
    free(nd->val);
    free(nd);
    return;
}

void print_ast(ast_node *nd, int indent, int l) {
    if (nd != NULL) {
        int c = 0;
        for (int i = 0; i < indent; i++) {
            if (c == 2) {
                putchar('|');
                c = 0;
            }
            else {
                putchar(' ');
                c++;
            }
        }
        if (l == 1) {
            printf("|-");
        }
        else {
            printf("|-");
        }
        printf("%s\n", nd->val);
        print_ast(nd->left, indent + 2, 1);
        print_ast(nd->right, indent + 2, 0);
    }

}

ast_node *parse(state *st, int in_def_block, int in_prio_block) {

    ast_node *ret_val = NULL;

    token *tk = create_token();
    
    if (scan_next_token(st, tk) == SCAN_SUCCESS) {

        printf("token: %s\n", tk->buf);

        // operator
        if (tk->type == TYPE_OPERATOR) {
            if (strcmp(tk->buf, "(") == 0) {
                ret_val = parse(st, in_def_block, IN_PRIORITY_BLOCK);
            }
            else if (strcmp(tk->buf, ")") == 0) {
                if (in_prio_block == IN_PRIORITY_BLOCK) {
                    ret_val = NULL;
                }
                else {
                    printf("parser.c -- syntax error - unexpected ')' on line %d, col %d\n", st->line, st->col);
                    exit(1);
                }
            }
            else if (strcmp(tk->buf, "{") == 0) {
                if (in_def_block == NOT_IN_DEFINE_BLOCK) {
                    ret_val = parse(st, IN_DEFINE_BLOCK, in_prio_block);
                }
                else {
                    printf("parser.c -- syntax error - unexpected '{' on line %d, col %d\n", st->line, st->col);
                    exit(1);
                }
            }
            else if (strcmp(tk->buf, "}") == 0) {
                if (in_def_block == IN_DEFINE_BLOCK) {
                    ret_val = NULL;
                }
                else {
                    printf("parser.c -- syntax error - unexpected '}' on line %d, col %d\n", st->line, st->col);
                    exit(1);
                }
            }
            else if (strcmp(tk->buf, "=") == 0) {
                ret_val = create_node(NODE_VAR_ASSIGN, NULL, parse(st, in_def_block, in_prio_block));
                strcpy(ret_val->val, "assign");
            }
        }

        // literal
        else if (tk->type == TYPE_INTEGER_LITERAL) {
            ret_val = create_node(NODE_INTEGER_LITERAL, NULL, NULL);
            strcpy(ret_val->val, tk->buf);
        }
        else if (tk->type == TYPE_CHAR_LITERAL) {
            ret_val = create_node(NODE_CHAR_LITERAL, NULL, NULL);
            strcpy(ret_val->val, tk->buf);
        }

        // keyword
        else if (strcmp(tk->buf, "return") == 0) {
            if (in_def_block == IN_DEFINE_BLOCK) {
                ret_val = create_node(NODE_FUNC_RETURN, parse(st, in_def_block, in_prio_block), NULL);
                strcpy(ret_val->val, tk->buf);
            }
            else {
                printf("parser.c -- syntax error - unexpected 'return' on line %d, col %d\n", st->line, st->col);
                exit(1);
            }
        }
        else if (strcmp(tk->buf, "struct") == 0) {

        }
        else if (strcmp(tk->buf, "enum") == 0) {

        }
        else if (strcmp(tk->buf, "typedef") == 0) {

        }
        else if (strcmp(tk->buf, "if") == 0) {

        }
        else if (strcmp(tk->buf, "else if") == 0) {

        }
        else if (strcmp(tk->buf, "else") == 0) {

        }
        else if (strcmp(tk->buf, "for") == 0) {

        }
        else if (strcmp(tk->buf, "while") == 0) {

        }

        // type
        else if (strcmp(tk->buf, "int8") == 0) {
            
        }
        else if (strcmp(tk->buf, "int16") == 0) {
            
        }
        else if (strcmp(tk->buf, "int32") == 0) {
            
        }
        else if (strcmp(tk->buf, "int64") == 0) {
            
        }
        else {
            ret_val = parse(st, in_def_block, in_prio_block);
            ret_val->left = create_node(NODE_VAR_DECL, NULL, NULL);
            strcpy(ret_val->left->val, tk->buf);
        }
    }

    destroy_token(tk);
    return ret_val;
}

/* ast_node *parse2(state *st, int in_def_block, int in_prio_block) {
    parse_state_t prst;
    token *tk = create_token();
    ast_node *ret = NULL;

    switch (prst) {
        case STATE_TYPE:
            scan_next_token(st, tk);
            if (tk->type == TYPE_IDENTIFIER) {
                token *tk2 = create_token();
                scan_next_token(st, tk2);
                if (tk->type == TYPE_OPERATOR) {

                }
            }
            else {
                printf("parse2() -- syntax error - expected identifier on line %d, col %d\n", st->line, st->col);
            }
    }

    destroy_token(tk);
} */