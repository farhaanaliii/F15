#include "../include/ast.h"

AST* new_ast(ASTType type){
    AST* ast = calloc(1, sizeof(AST));
    ast->type = type;
    ast->scope = (void*)0;
    // AST_VARIABLE_DEFINATION
    ast->variable_defination_variable_name = (void*)0;
    ast->variable_defination_value = (void*)0;

    // AST_FUNCTION_DEFINITION
    ast->function_defination_body = (void*)0;
    ast->function_defination_name = (void*)0;
    ast->function_defination_args = (void*)0;
    ast->function_defination_args_size = 0;
    // AST_VARIABLE
    ast->variable_name = (void*)0;

    // AST_FUNCTION_CALL
    ast->function_call_name = (void*)0;
    ast->function_call_args = (void*)0;
    ast->function_call_args_size = 0;

    // AST_STRING
    ast->string_value = (void*)0;

    // AST_COMPOUND
    ast->compound_value = (void*)0;
    ast->compound_size = 0;

    ast->binary_op_left = NULL;
    ast->binary_op_right = NULL;
    ast->binary_op_type = 0;

    return ast;
}