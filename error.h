#ifndef COMPILER_ERROR_H
#define COMPILER_ERROR_H

#include "state.h"

#define SYNTAX_ERROR 101

void syntax_error(state *st, char *what);

#endif // COMPILER_ERROR_H