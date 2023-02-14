#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "state.h"

#include "tokenizer.h"

/**
 * The number of valid operator tokens.
*/
#define NUM_TOKENS 37

/**
 * The array containing all valid operator tokens.
 * 
 * Must be of length NUM_TOKENS.
*/
char *tokens[NUM_TOKENS] = {
    "!", "@", "#", "&", "*", "(", ")", "-", "+", "=",
    "|", "\\", ":", ";", "\"", "'", "<", ",", ">", ".",
    "?", "/", "{", "[", "}", "]", "*=", "-=", "+=", "/=",
    "--", "++", "&&", "||", "/**", "*/", "//"
};

/**
 * Creates a new token.
*/
token *create_token() {
    token *tk = malloc(sizeof(token));
    tk->buf = malloc(MAX_IDENT_TOKEN_LEN + 1);
    return tk;
}

/**
 * Destroys the given token.
*/
void destroy_token(token *tk) {
    free(tk->buf);
    free(tk);
    return;
}

/**
 * Gets the next character from the given input file
*/
int get_next_char(FILE *infile) {
    return fgetc(infile);
}

/**
 * Determines if the given character is irrelevant whitespace.
 * 
 * Irrelevant white space is all whitespace that does not take column space,
 * except for newline.
*/
int is_irrelevant_whitespace(int c) {
    if (c == '\t' || c == '\r' || c == '\f' || c == '\0') {
        return 1;
    }
    return 0;
}

/**
 * Determines if the given character is relevant whitespace.
 * 
 * Relevant whitespace characters are space and newline.
*/
int is_relevant_whitespace(int c) {
    if (c == '\n' || c == ' ') {
        return 1;
    }
    return 0;
}

/**
 * Gets the next relevant character from the given input file.
 * 
 * It will get new characters from the input file until it encounters
 * a character that takes column space, a newline, or end of file.
*/
int get_next_relevant_char(FILE *infile) {

    int c;
    do {

        // get char
        c = get_next_char(infile);

        if (is_irrelevant_whitespace(c) == 1) {
            // ignore irrelevant whitespace
        }
        else {
            return c;
        }
    } while (1);

}

/**
 * Determines if the given character is a valid character for keywords
 * or identifier, depending on whether or not it is the first character
 * in the keyword or identifier.
 * 
 * Alphabet characters and underscores are valid if it is the first character.
 * 
 * Numeric characters are also valid if it is not the first character.
*/
int is_keyword_or_identifier_char(int c, int is_first) {
    int ret_val = 0;
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_') {
        ret_val = 1;
    }
    else if (is_first == 0 && is_int_char(c) == 1) {
        ret_val = 1;
    }
    return ret_val;
}

/**
 * Determines if the given character is a numeric character.
*/
int is_int_char(int c) {
    if (c >= '0' && c <= '9') {
        return 1;
    }
    return 0;
}

/**
 * Scans the next token and inserts it, along with other information,
 * into the state object pointed to by the given pointer.
 * 
 * Returns SCAN_SUCCESS on success, SCAN_FAILURE on error, or
 * SCAN_NO_MORE_TOKENS if EOF was encountered.
 * 
 * On newline or space, it calls itself again to ensure that it returns
 * with a useful token.
 * 
 * The scanned token is passed in the state object's buf as a
 * null terminated char array.
 * 
 * Keyword and identifier detection is greedy and will stop at whitespace
 * non-alphanumeric, and non-underscore characters.
 * 
 * Integer literal detection is also greedy, and will stop at the first
 * non-numeric character.
 * 
 * Operator detection is greedy, and will stop at the first alphanumeric or
 * underscore character. However, if the resulting possible operator is not
 * a valid operator, it will decrease by one character until it matches a
 * valid operator. If no valid operators are matched, the function will
 * print an invalid operator error and return SCAN_FAILURE.
*/
int scan_next_token(state *st, token *tk) {

    // start at success
    int ret_val = SCAN_SUCCESS;

    // buffer for operator detection
    char op_detect_buf[MAX_OP_TOKEN_LEN + 1];

    // get the next char
    int c = get_next_relevant_char(st->infile);
    st->col++;

    // newline character
    if (c == '\n') {

        // increment line counter
        st->line++;

        // set col counter back to one
        st->col = 1;

        // recursive call to ensure useful token
        ret_val = scan_next_token(st, tk);

    }

    // space character
    else if (c == ' ') {

        // recursive call to ensure useful token
        ret_val = scan_next_token(st, tk);

    }

    // end of file encountered
    else if (c == EOF) {

        ret_val = SCAN_NO_MORE_TOKENS;

    }

    // keyword or identifier encountered
    else if (is_keyword_or_identifier_char(c, 1)) {

        tk->type = TYPE_IDENTIFIER;

        // greedily grab subsequent chars until an invalid char is hit
        int i = 0;
        do {
            tk->buf[i] = c;
            c = get_next_relevant_char(st->infile);
            st->col++;
            i++;
        } while (i < MAX_IDENT_TOKEN_LEN && is_keyword_or_identifier_char(c, 0));

        // null terminate the buffer
        tk->buf[i] = '\0';

        // put the extra char back
        ungetc(c, st->infile);
        st->col--;

    }
    else if (is_int_char(c)) {

        tk->type = TYPE_INTEGER_LITERAL;
    
        // greedily grab subsequent chars until an invalid char is hit
        int i = 0;
        do {
            tk->buf[i] = c;
            i++;
            c = get_next_relevant_char(st->infile);
            st->col++;
        } while (is_int_char(c));

        // null terminate the buffer
        tk->buf[i] = '\0';

        // put the extra char back
        ungetc(c, st->infile);
        st->col--;

    }
    else {

        tk->type = TYPE_OPERATOR;
    
        // greedily grab subsequent chars until an invalid char is hit
        // to generate the possible operator
        int i = 0;
        int odb_idx = 0;
        while (i < MAX_OP_TOKEN_LEN && is_keyword_or_identifier_char(c, 1) == 0 && is_relevant_whitespace(c) == 0) {
            tk->buf[i] = c;
            c = get_next_relevant_char(st->infile);
            st->col++;
            i++;
        }

        // put the extra char in the detect buffer (to be put back into the input stream)
        op_detect_buf[odb_idx++] = c;
        st->col--;

        // null terminate the buffer
        tk->buf[i] = '\0';

        int j;
        int matched = 0;
        while (i > 0 && matched == 0) {

            // attempt to match a valid token
            j = 0;
            while (j < NUM_TOKENS && matched == 0) {
                if (strcmp(tk->buf, tokens[j]) == 0) {
                    matched = 1;
                }
                else {
                    j++;
                }
            }

            // if no valid tokens were matched
            if (matched == 0) {

                // if the possible operator length is one and it has not been matched,
                // the operator is invalid
                if (i == 1) {
                    printf("scan() -- syntax error - unknown operator '%s' on line %d col %d\n",
                           tk->buf, st->line, st->col);
                    ret_val = SCAN_FAILURE;
                }

                // subtract the rightmost char from the possible operator
                op_detect_buf[odb_idx++] = tk->buf[i - 1];
                st->col--;
                tk->buf[--i] = '\0';

            }
        }

        // put all unmatched or unused chars back into the input stream
        int k = 0;
        while (k < odb_idx) {
            ungetc(op_detect_buf[k++], st->infile);
        }

    }

    return ret_val;

    /**
    switch(c) {
        case '~':
            break;
        case '`':
            break;
        case '!':
            break;
        case '@':
            break;
        case '#':
            break;
        case '$':
            break;
        case '%':
            break;
        case '^':
            break;
        case '&':
            break;
        case '*':
            break;
        case '(':
            break;
        case ')':
            break;
        case '-':
            break;
        case '+':
            break;
        case '=':
            break;
        case '{':
            break;
        case '[':
            break;
        case '}':
            break;
        case ']':
            break;
        case '|':
            break;
        case '\\':
            break;
        case ':':
            break;
        case ';':
            break;
        case '"':
            break;
        case '\'':
            break;
        case '<':
            break;
        case ',':
            break;
        case '>':
            break;
        case '.':
            break;
        case '?':
            break;
        case '/':
            break;
        default:
            break;
    }
    */
}