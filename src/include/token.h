#ifndef TOKEN_H
#define TOKEN_H
#include <stdlib.h>

typedef enum{
    TT_INT,
    TT_STRING,
    TT_IDENTIFIER,
    TT_KEYWORD,
    TT_L_PAREN,
    TT_R_PAREN,
    TT_L_BRACE,
    TT_R_BRACE,
    TT_SEMICOLON,
    TT_COLON,
    TT_COMA,
    TT_SINGLE_QUOTE,
    TT_DOUBLE_QUOTE,
    TT_EQUAL,
    TT_NULL,

    TT_PLUS,
    TT_EOF
} TokenType;

typedef struct{
    char* value;
    TokenType type;
} Token;

Token* new_token(char* value, TokenType type);
#endif