#include <stdlib.h>
#include <stdio.h>

#include "state.h"

#include "error.h"

void syntax_error(state *st, char *what) {
    printf("%d:%d: %s\n", st->line, st->col, what);
    exit(SYNTAX_ERROR);
}