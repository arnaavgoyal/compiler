#include <stdlib.h>
#include <stdio.h>

#include "state.h"

state *create_state(FILE *infile, FILE *outfile) {

    state *st = malloc(sizeof(state));
    st->line = 1;
    st->col = 1;
    st->infile = infile;
    st->outfile = outfile;
    return st;
}

void destroy_state(state *st) {

    free(st);

}