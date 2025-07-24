#include "../include/lexer.h"
#include <ctype.h>
#include <stdio.h>

Lexer* new_lexer(char* content){
    Lexer* lexer = calloc(1, sizeof(Lexer));
    lexer->content = content;
    lexer->i = 0;
    lexer->c = lexer->content[lexer->i];
    return lexer;
}

void incr_lexer(Lexer* lex){
    if(lex->c != '\0' && lex->i < (size_t)strlen(lex->content)){
        lex->i += 1;
        lex->c = lex->content[lex->i];
    }
}

void skip_whitespaces_lexer(Lexer* lex){
    while(lex->c == ' ' || lex->c == 10 || lex->c == 13 || lex->c == 9)
        incr_lexer(lex);
}

char peek_char(Lexer* lex){
    if(lex->i + 1 < strlen(lex->content))
        return lex->content[lex->i + 1];
    return '\0';
}

Token* get_token_lexer(Lexer* lex){
    while(lex->c != '\0' && lex->i < (size_t)strlen(lex->content)){
        
        if(lex->c == ' ' || lex->c == 10 || lex->c == 13 || lex->c == 9)
            incr_lexer(lex);
        
        if (lex->c == '/') {
            if (peek_char(lex) == '/') { // Single-line comment
                while (lex->c != '\n' && lex->c != '\0') {
                    incr_lexer(lex);
                }
                continue;
            } else if (peek_char(lex) == '*') { // Multi-line comment
                incr_lexer(lex); // skip '/'
                incr_lexer(lex); // skip '*'
                while (!(lex->c == '*' && peek_char(lex) == '/') && lex->c != '\0') {
                    incr_lexer(lex);
                }
                if (lex->c == '*' && peek_char(lex) == '/') {
                    incr_lexer(lex); // skip '*'
                    incr_lexer(lex); // skip '/'
                }
                continue;
            }
        }
        
        if(isalnum(lex->c))
            return make_identifier_lexer(lex);
        
        switch (lex->c){
            case '=':
                return incr_with_token_lexer(lex, new_token(get_c_as_string(lex), TT_EQUAL));
            case '(':
                return incr_with_token_lexer(lex, new_token(get_c_as_string(lex), TT_L_PAREN));
            case ')':
                return incr_with_token_lexer(lex, new_token(get_c_as_string(lex), TT_R_PAREN));
            case '{':
                return incr_with_token_lexer(lex, new_token(get_c_as_string(lex), TT_L_BRACE));
            case '}':
                return incr_with_token_lexer(lex, new_token(get_c_as_string(lex), TT_R_BRACE));
            case ';':
                return incr_with_token_lexer(lex, new_token(get_c_as_string(lex), TT_SEMICOLON));
            case ',':
                return incr_with_token_lexer(lex, new_token(get_c_as_string(lex), TT_COMA));
            case '\"':
                return make_string_lexer(lex);
            case '+':
                incr_lexer(lex);
                return new_token("+", TT_PLUS);
            
        }
    }

    return new_token("\0", TT_EOF);
}

Token* make_string_lexer(Lexer* lex){
    incr_lexer(lex);
    char* value = calloc(1, sizeof(char));
    value[0] = '\0';

    while(lex->c != '\"'){
        char* s = get_c_as_string(lex);
        value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
        strcat(value, s);
        incr_lexer(lex);
    }

    incr_lexer(lex);
    return new_token(value, TT_STRING);
}
Token* make_identifier_lexer(Lexer* lex){
    char* value = calloc(1, sizeof(char));
    value[0] = '\0';

    while(isalnum(lex->c)){
        char* s = get_c_as_string(lex);
        value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
        strcat(value, s);
        incr_lexer(lex);
    }

    return new_token(value, TT_IDENTIFIER);
}
char* get_c_as_string(Lexer* lex){
    char* str = calloc(2, sizeof(char));
    str[0] = lex->c;
    str[1] = '\0';
    return str;
}
Token* incr_with_token_lexer(Lexer* lex, Token* tok){
    incr_lexer(lex);
    return tok;
}