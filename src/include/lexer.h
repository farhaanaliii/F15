#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include <string.h>
#include <stdlib.h>

typedef struct{
    char* content;
    char c;
    size_t i;
} Lexer;

Lexer* new_lexer(char* content);
void incr_lexer(Lexer* lex);
Token* incr_with_token_lexer(Lexer* lex, Token* tok);
void skip_whitespaces_lexer(Lexer* lex);
Token* get_token_lexer(Lexer* lex);
Token* make_string_lexer(Lexer* lex);
Token* make_identifier_lexer(Lexer* lex);
char* get_c_as_string(Lexer* lex);
char peek_char(Lexer* lex);
#endif