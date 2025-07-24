#include "../include/interpreter.h"
#include <stdio.h>
#include <string.h>
#include "../include/scope.h"
#include "../include/token.h"

static AST* OS_OUT(Interpreter* com, AST** args, int size){
    for(int i=0; i<size; i++){
        AST* visited_ast = interp_interpreter(com, args[i]);
        switch(visited_ast->type){
            case AST_STRING: printf("%s\n", visited_ast->string_value); break;
            default: printf("[Warning] %s:%d: Attempted to print unsupported AST type (%d) at OS_OUT.\n", __FILE__, __LINE__, visited_ast->type);
        }
    }
    return new_ast(AST_NOOP);
}
Interpreter* new_interpreter(){
    Interpreter* com = calloc(1, sizeof(struct Interpreter_Struct));
    return com;
}
AST* interp_interpreter(Interpreter* com, AST* node){
    switch(node->type){
        case AST_VARIABLE_DEFINATION: return interp_variable_definition_interpreter(com, node);
        case AST_VARIABLE: return interp_variable_interpreter(com, node);
        case AST_FUNCTION_CALL: return interp_function_call_interpreter(com, node);
        case AST_FUNCTION_DEFINATION: return interp_function_defination_interpreter(com, node);
        case AST_STRING: return interp_string_interpreter(com, node);
        case AST_COMPOUND: return interp_compound_interpreter(com, node);
        case AST_BINARY_OP: return interp_binary_op_interpreter(com, node);
        case AST_NOOP: return node;
    }

    fprintf(stderr, "[Interpreter Error] %s:%d: Uncaught statement of AST type '%d'. This may indicate a bug in the parser or interpreter.\n", __FILE__, __LINE__, node->type);
    exit(1);
    return new_ast(AST_NOOP);
}
AST* interp_function_defination_interpreter(Interpreter* com, AST* node){
    (void)com;
    add_functon_defination_scope(node->scope, node);
    return node;
}
AST* interp_variable_definition_interpreter(Interpreter* com, AST* node){
    (void)com;
    add_variable_defination_scope(node->scope, node);
    return node;
}

AST* interp_variable_interpreter(Interpreter* com, AST* node){
    AST* vdef = get_variable_defination_scope(node->scope, node->variable_name);
    
    if(vdef != (void*)0){
        return interp_interpreter(com, vdef->variable_defination_value);
    }
    
    fprintf(stderr, "[Name Error] %s:%d: Undefined variable name '%s' in current scope.\n", __FILE__, __LINE__, node->variable_name);
    exit(1);
}

AST* interp_function_call_interpreter(Interpreter* com, AST* node){
    if(strcmp(node->function_call_name, "out") == 0){
        return OS_OUT(com, node->function_call_args, node->function_call_args_size);
    }
    AST* fdef = get_function_defination_scope(node->scope, node->function_call_name);
    if(fdef == (void*)0){
        fprintf(stderr, "[Name Error] %s:%d: Undefined function '%s' in current scope.\n", __FILE__, __LINE__, node->function_call_name);
        exit(1);
    }
    for(size_t i=0; i<node->function_call_args_size; i++){
        
        // grab the variable from the function defination arguments
        AST* ast_var = (AST*) fdef->function_defination_args[i];

        // grab the value from the function call arguments
        AST* ast_value = (AST*) node->function_call_args[i];

        // create a new variable defination with the value of the argument
        // in the function call
        AST* ast_vardef = new_ast(AST_VARIABLE_DEFINATION);
        ast_vardef->variable_defination_value = ast_value;

        // copy the name from the function defination argument into the new
        // variable defination
        ast_vardef->variable_defination_variable_name = (char*) calloc(strlen(ast_var->variable_name) + 1, sizeof(char));
        strcpy(ast_vardef->variable_defination_variable_name, ast_var->variable_name);

        //printf("%s = %s\n", ast_vardef->variable_defination_variable_name, ast_vardef->variable_defination_value);
        // push our variable to function body scope
        
        add_variable_defination_scope(fdef->function_defination_body->scope, ast_vardef);
        
        //puts("yup");
    }
    
    
    return interp_interpreter(com, fdef->function_defination_body);
    

}

AST* interp_string_interpreter(Interpreter* com, AST* node){
    (void)com;
    return node;
}

AST* interp_compound_interpreter(Interpreter* com, AST* node){
    for(size_t i=0; i<node->compound_size; i++){
        interp_interpreter(com, node->compound_value[i]);
    }
    
    return new_ast(AST_NOOP);
}

AST* interp_binary_op_interpreter(Interpreter* com, AST* node){
    AST* left = interp_interpreter(com, node->binary_op_left);
    AST* right = interp_interpreter(com, node->binary_op_right);

    if (node->binary_op_type == TT_PLUS) {
        // String concatenation
        if (left->type == AST_STRING && right->type == AST_STRING) {
            size_t len = strlen(left->string_value) + strlen(right->string_value) + 1;
            char* result = malloc(len);
            strcpy(result, left->string_value);
            strcat(result, right->string_value);

            AST* ast = new_ast(AST_STRING);
            ast->string_value = result;
            return ast;
        }
        // Add support for other types (e.g., int) if needed
    }
    fprintf(stderr, "[Interpreter Error] %s:%d: Unsupported binary operation or operand types.\n", __FILE__, __LINE__);
    exit(1);
}

