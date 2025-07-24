#include "../include/scope.h"
#include <string.h>


Scope* new_scope(){
    Scope* scope = calloc(1, sizeof(struct SCOPE_STRUCT));
    scope->function_definations = (void*)0;
    scope->function_definations_size = 0;

    scope->variable_definitions = (void*)0;
    scope->variable_definitions_size = 0;
    return scope;
}
AST* add_functon_defination_scope(Scope* scope, AST* fdef){
    scope->function_definations_size += 1;
    if(scope->function_definations == (void*)0){
        scope->function_definations = calloc(1, sizeof(struct AST_STRUCT*));
    }else{
        scope->function_definations = realloc(scope->function_definations, scope->function_definations_size * sizeof(struct AST_STRUCT**));
    }

    scope->function_definations[scope->function_definations_size - 1] = fdef;

    return fdef;
}
AST* get_function_defination_scope(Scope* scope, const char* fname){
    for(size_t i=0; i<scope->function_definations_size; i++){
        AST* fdef = scope->function_definations[i];
        if(strcmp(fdef->function_defination_name, fname) == 0){
            return fdef;
        }
    }
    return (void*)0;
}

AST* add_variable_defination_scope(Scope* scope, AST* vdef){
    if(scope->variable_definitions == (void*)0){
        scope->variable_definitions = calloc(1, sizeof(struct AST_STRUCT*));
        scope->variable_definitions[0] = vdef;
        scope->variable_definitions_size += 1;
    }else{
        scope->variable_definitions_size += 1;
        scope->variable_definitions = realloc(scope->variable_definitions, scope->variable_definitions_size * sizeof(struct AST_STRUCT*));
        scope->variable_definitions[scope->variable_definitions_size - 1] = vdef;
    }

    return vdef;
}
AST* get_variable_defination_scope(Scope* scope, const char* vname){
    for(size_t i=0; i<scope->variable_definitions_size; i++){
        AST* vdef = scope->variable_definitions[i];
        if(strcmp(vdef->variable_defination_variable_name, vname) == 0){
            return vdef;
        }
    }
    return (void*)0;
}