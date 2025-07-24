#include "../include/parser.h"
#include "../include/ast.h"

Parser* new_parser(Lexer* lex){
    Parser* parser = calloc(1, sizeof(Parser));
    parser->lex = lex;
    parser->tok = get_token_lexer(lex);
    parser->prev_token = parser->tok;
    //parser->next_token = ;
    parser->scope = new_scope();
    return parser;
}

void eat_parser(Parser* parser, int type){
    if((int)parser->tok->type == type){
        parser->prev_token = parser->tok;
        parser->tok = get_token_lexer(parser->lex);//parser->next_token;
        //parser->next_token = get_token_lexer(parser->lex);
    }else{
        fprintf(stderr, "[Syntax Error] %s:%d: Unexpected token '%s' (type %d) at parsing. Expected token type: %d.\n", __FILE__, __LINE__, parser->tok->value, parser->tok->type, type);
        exit(1);
    }
}


AST* parse_parser(Parser* parser, Scope* scope){
    return parse_stmnts_parser(parser, scope);
}

AST* parse_stmnt_parser(Parser* parser, Scope* scope){
    switch(parser->tok->type){
        case TT_IDENTIFIER: return parse_identifier_parser(parser, scope);
        case TT_INT:
        case TT_STRING:
        case TT_KEYWORD:
        case TT_L_PAREN:
        case TT_R_PAREN:
        case TT_L_BRACE:
        case TT_R_BRACE:
        case TT_SEMICOLON:
        case TT_COLON:
        case TT_COMA:
        case TT_SINGLE_QUOTE:
        case TT_DOUBLE_QUOTE:
        case TT_EQUAL:
        case TT_NULL:
        case TT_EOF:
        default:
            break;
    }
    return new_ast(AST_NOOP);
}
AST* parse_stmnts_parser(Parser* parser, Scope* scope){
    AST* compound = new_ast(AST_COMPOUND);
    compound->scope = scope;
    compound->compound_value = calloc(1, sizeof(struct AST_STRUCT*));

    AST* ast_stmnt = parse_stmnt_parser(parser, scope);
    ast_stmnt->scope = scope;
    compound->compound_value[0] = ast_stmnt;
    compound->compound_size += 1;
    while (1) {
        if (ast_stmnt && ast_stmnt->type == AST_FUNCTION_DEFINATION) {
            // Function definitions do not require a semicolon
        } else {
            if (parser->tok->type == TT_SEMICOLON) {
                eat_parser(parser, TT_SEMICOLON);
            } else if (parser->tok->type == TT_EOF || parser->tok->type == TT_R_BRACE) {
                // Allow EOF or closing brace after the last statement
                break;
            } else {
                fprintf(stderr, "[Syntax Error] %s:%d: Missing semicolon after statement. Please terminate all statements (except function definitions) with a semicolon.\n", __FILE__, __LINE__);
                exit(1);
            }
        }
        AST* next_stmnt = parse_stmnt_parser(parser, scope);
        if(next_stmnt){
            next_stmnt->scope = scope;
            compound->compound_size += 1;
            compound->compound_value = realloc(compound->compound_value, compound->compound_size * sizeof(AST*));
            compound->compound_value[compound->compound_size - 1] = next_stmnt;
            ast_stmnt = next_stmnt;
        } else {
            break;
        }
    }
    return compound;
}

AST* parse_expr_parser(Parser* parser, Scope* scope) {
    AST* left = NULL;

    // Parse the left operand
    switch(parser->tok->type) {
        case TT_STRING:
            left = parse_string_parser(parser, scope);
            break;
        case TT_IDENTIFIER:
            left = parse_identifier_parser(parser, scope);
            break;
        default:
            left = new_ast(AST_NOOP);
            break;
    }

    // Check for binary operator (e.g., +)
    while (parser->tok->type == TT_PLUS) {
        int op_type = parser->tok->type;
        eat_parser(parser, op_type);
        AST* right = parse_expr_parser(parser, scope);

        AST* binop = new_ast(AST_BINARY_OP);
        binop->binary_op_left = left;
        binop->binary_op_right = right;
        binop->binary_op_type = op_type;
        left = binop;
    }

    return left;
}
AST* parse_factor_parser(Parser* parser, Scope* scope){
    (void)parser;
    (void)scope;
    return new_ast(AST_NOOP);
}
AST* parse_term_parser(Parser* parser, Scope* scope){
    (void)parser;
    (void)scope;
    return new_ast(AST_NOOP);
}
AST* parse_function_call_parser(Parser* parser, Scope* scope){
    AST* func_call = new_ast(AST_FUNCTION_CALL);
    
    func_call->function_call_name = parser->prev_token->value;
    eat_parser(parser, TT_L_PAREN);
    func_call->function_call_args = calloc(1, sizeof(struct AST_STRUCT*));

    AST* ast_expr = parse_expr_parser(parser, scope);
    func_call->function_call_args[0] = ast_expr;
    func_call->function_call_args_size += 1;
    while(parser->tok->type == TT_COMA){
        eat_parser(parser, TT_COMA);
        AST* ast_expr = parse_expr_parser(parser, scope);
        func_call->function_call_args_size += 1;
        func_call->function_call_args = realloc(func_call->function_call_args, func_call->function_call_args_size * sizeof(struct AST_STRUCT*));
        func_call->function_call_args[func_call->function_call_args_size - 1] = ast_expr;
    }

    eat_parser(parser, TT_R_PAREN);
    func_call->scope = scope;
    return func_call;
}

AST* parse_variable_definition_parser(Parser* parser, Scope* scope){
    eat_parser(parser, TT_IDENTIFIER); // let
    char* var_name = parser->tok->value;
    eat_parser(parser, TT_IDENTIFIER);
    eat_parser(parser, TT_EQUAL);
    AST* var_value = parse_expr_parser(parser, scope);
    
    AST* var_define = new_ast(AST_VARIABLE_DEFINATION);
    var_define->variable_defination_variable_name = var_name;
    var_define->variable_defination_value = var_value;
    var_define->scope = scope;
    return var_define;
}
AST* parse_function_defination_parser(Parser* parser, Scope* scope){
    AST* ast = new_ast(AST_FUNCTION_DEFINATION);
    eat_parser(parser, TT_IDENTIFIER); // function
    char* function_name = parser->tok->value;
    ast->function_defination_name = calloc(strlen(function_name) + 1, sizeof(char));
    strcpy(ast->function_defination_name, function_name);
    eat_parser(parser, TT_IDENTIFIER); // function name
    eat_parser(parser, TT_L_PAREN);

    // if there is no args
    //if(parser->next_token->type == TT_R_PAREN){
    //    puts("yup");
    //}
    
    ast->function_defination_args = calloc(1, sizeof(struct AST_STRUCT*));
    AST* arg = parse_variable_parser(parser, scope);
    ast->function_defination_args_size += 1;
    ast->function_defination_args[ast->function_defination_args_size - 1] = arg;
    
    while(parser->tok->type == TT_COMA){
        eat_parser(parser, TT_COMA);
        ast->function_defination_args_size += 1;
        ast->function_defination_args = realloc(ast->function_defination_args, ast->function_defination_args_size * sizeof(struct AST_STRUCT*));
        AST* arg = parse_variable_parser(parser, scope);
        ast->function_defination_args[ast->function_defination_args_size - 1] = arg;

    }
    eat_parser(parser, TT_R_PAREN);
    eat_parser(parser, TT_L_BRACE);

    ast->function_defination_body = parse_stmnts_parser(parser, scope);

    eat_parser(parser, TT_R_BRACE);
    ast->scope = scope;
    return ast;
}
AST* parse_variable_parser(Parser* parser, Scope* scope){
    char* token_value = parser->tok->value;
    eat_parser(parser, TT_IDENTIFIER);
    if(parser->tok->type == TT_L_PAREN)
        return parse_function_call_parser(parser, scope);
    
    AST* ast_var = new_ast(AST_VARIABLE);
    ast_var->variable_name = token_value;
    ast_var->scope = scope;
    return ast_var;
}
AST* parse_string_parser(Parser* parser, Scope* scope){
    AST* ast_str = new_ast(AST_STRING);
    ast_str->string_value = parser->tok->value;

    eat_parser(parser, TT_STRING);
    ast_str->scope = scope;
    return ast_str;
}

AST* parse_identifier_parser(Parser* parser, Scope* scope){
    if(strcmp(parser->tok->value, "let") == 0){
        return parse_variable_definition_parser(parser, scope);
    }else if(strcmp(parser->tok->value, "function") == 0){
        return parse_function_defination_parser(parser, scope);
    }
    else{
        return parse_variable_parser(parser, scope);
    }
}