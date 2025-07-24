#ifndef PARSER_H
#define PARSER_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/ast.h"
#include "../include/lexer.h"
#include "../include/scope.h"

typedef struct{
    Lexer* lex;
    Token* tok;
    Token* prev_token;
    //Token* next_token;
    Scope* scope;
} Parser;

Parser* new_parser(Lexer* lex);
void eat_parser(Parser* parser, int type);
AST* parse_parser(Parser* parser, Scope* scope);
AST* parse_stmnt_parser(Parser* parser, Scope* scope);
AST* parse_stmnts_parser(Parser* parser, Scope* scope);
AST* parse_expr_parser(Parser* parser, Scope* scope);
AST* parse_factor_parser(Parser* parser, Scope* scope);
AST* parse_term_parser(Parser* parser, Scope* scope);
AST* parse_function_defination_parser(Parser* parser, Scope* scope);
AST* parse_function_call_parser(Parser* parser, Scope* scope);
AST* parse_variable_definition_parser(Parser* parser, Scope* scope);
AST* parse_variable_parser(Parser* parser, Scope* scope);
AST* parse_string_parser(Parser* parser, Scope* scope);
AST* parse_identifier_parser(Parser* parser, Scope* scope);
#endif