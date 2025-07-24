#ifndef AST_H
#define AST_H

#include <stdlib.h>

typedef enum {
    AST_VARIABLE_DEFINATION,
    AST_FUNCTION_DEFINATION,
    AST_VARIABLE,
    AST_FUNCTION_CALL,
    AST_STRING,
    AST_COMPOUND,
    AST_NOOP,
    AST_BINARY_OP
} ASTType;

typedef struct AST_STRUCT {
    ASTType type;
    struct SCOPE_STRUCT* scope;
    // AST_VARIABLE_DEFINATION
    char* variable_defination_variable_name;
    struct AST_STRUCT* variable_defination_value;

    // AST_FUNCTION_DEFINITION
    struct AST_STRUCT* function_defination_body;
    char* function_defination_name;
    struct AST_STRUCT** function_defination_args;
    size_t function_defination_args_size;
    // AST_VARIABLE
    char* variable_name;

    // AST_FUNCTION_CALL
    char* function_call_name;
    struct AST_STRUCT** function_call_args;
    size_t function_call_args_size;

    // AST_STRING
    char* string_value;

    // AST_COMPOUND
    struct AST_STRUCT** compound_value;
    size_t compound_size;

    // For binary operations
    struct AST_STRUCT* binary_op_left;
    struct AST_STRUCT* binary_op_right;
    int binary_op_type;
} AST;

AST* new_ast(ASTType type);

#endif