#include <stdio.h>
#include <stdlib.h>

#include "state.h"
#include "tokenizer.h"
#include "parser.h"

int main() {

    FILE *infile = fopen64("input.txt", "r");
    FILE *outfile = fopen64("output.asm", "w");

    state *comp_state = create_state(infile, outfile);

    ast_node *nd = parse(comp_state, NOT_IN_DEFINE_BLOCK, NOT_IN_PRIORITY_BLOCK);
    printf("%p\n", nd);
    print_ast(nd, 0, 0);

    destroy_state(comp_state);

    fclose(infile);
    fclose(outfile);

    return 0;
    
}