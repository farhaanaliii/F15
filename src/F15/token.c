#include "../include/token.h"

Token* new_token(char* value, TokenType type){
    Token* tok = calloc(1, sizeof(Token));
    tok->type = type;
    tok->value = value;
    return tok;
}