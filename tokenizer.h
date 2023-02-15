#ifndef COMPILER_TOKENIZER_H
#define COMPILER_TOKENIZER_H

#include "state.h"

#define SCAN_SUCCESS 0
#define SCAN_FAILURE 1
#define SCAN_NO_MORE_TOKENS -1

typedef enum _token_type_t {
    TYPE_OPERATOR,
    TYPE_IDENTIFIER,
    TYPE_INTEGER_LITERAL,
    TYPE_CHAR_LITERAL
} token_type_t;

typedef struct _token {
    token_type_t type;
    char *buf;
} token;

token *create_token();

void destroy_token(token *tk);

int get_next_char(FILE *infile);

int is_irrelevant_whitespace(int c);

int is_relevant_whitespace(int c);

int get_next_relevant_char(FILE *infile);

int is_keyword_or_identifier_char(int c, int is_first);

int is_int_char(int c);

void unscan_token(token *tk);

int scan_next_token(state *st, token *tk);

enum _op_token_type_t {
    TOKEN_EXCLAMATION_POINT,
    TOKEN_AT_SIGN,
    TOKEN_HASHTAG,
    TOKEN_AMPERSAND,
    TOKEN_ASTERISK,
    TOKEN_OPEN_PARENTHESIS,
    TOKEN_CLOSE_PARENTHESIS,
    TOKEN_HYPHEN,
    TOKEN_PLUS,
    TOKEN_EQUALS,
    TOKEN_OPEN_CURLY_BRACE,
    TOKEN_OPEN_SQUARE_BRACKET,
    TOKEN_CLOSE_CURLY_BRACE,
    TOKEN_CLOSE_SQUARE_BRACKET,
    TOKEN_PIPE,
    TOKEN_BACK_SLASH,
    TOKEN_COLON,
    TOKEN_SEMICOLON,
    TOKEN_DOUBLE_QUOTES,
    TOKEN_SINGLE_QUOTES,
    TOKEN_LEFT_ANGLE_BRACKET,
    TOKEN_COMMA,
    TOKEN_RIGHT_ANGLE_BRACKET,
    TOKEN_PERIOD,
    TOKEN_QUESTION_MARK,
    TOKEN_FORWARD_SLASH,
    TOKEN_ASTERISK_EQUALS,
    TOKEN_HYPHEN_EQUALS,
    TOKEN_PLUS_EQUALS,
    TOKEN_FORWARD_SLASH_EQUALS,
    TOKEN_HYPHEN_HYPHEN,
    TOKEN_PLUS_PLUS,
    TOKEN_AMPERSAND_AMPERSAND,
    TOKEN_PIPE_PIPE,
    TOKEN_FORWARD_SLASH_ASTERISK_ASTERISK,
    TOKEN_ASTERISK_FORWARD_SLASH,
    TOKEN_FORWARD_SLASH_FORWARD_SLASH
};

#endif // COMPILER_TOKENIZER_H