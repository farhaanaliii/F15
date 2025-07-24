#ifndef SCOPE_H
#define SCOPE_H
#include "../include/ast.h"

typedef struct SCOPE_STRUCT{
    AST** function_definations;
    size_t function_definations_size;

    
    AST** variable_definitions;
    size_t variable_definitions_size;
} Scope;

Scope* new_scope();
AST* add_functon_defination_scope(Scope* scope, AST* fdef);
AST* get_function_defination_scope(Scope* scope, const char* fname);
AST* add_variable_defination_scope(Scope* scope, AST* vdef);
AST* get_variable_defination_scope(Scope* scope, const char* vname);
#endif