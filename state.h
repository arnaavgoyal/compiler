#ifndef COMPILER_STATE_H
#define COMPILER_STATE_H

#include <stdio.h>

#define MAX_SYMBOLS 1024
#define MAX_OP_TOKEN_LEN 2
#define MAX_IDENT_TOKEN_LEN 127

typedef struct _symbol {
    char ident[MAX_IDENT_TOKEN_LEN + 1];
    char type[MAX_IDENT_TOKEN_LEN + 1];
} symbol;

typedef struct _type {
    char ident[MAX_IDENT_TOKEN_LEN + 1];

};

typedef struct _state {
    int line;
    int col;
    FILE *infile;
    FILE *outfile;
    symbol symtable[MAX_SYMBOLS];
} state;

state *create_state(FILE *infile, FILE *outfile);

void destroy_state(state *st);

#endif // COMPILER_STATE_H