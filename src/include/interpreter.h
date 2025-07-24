#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "../include/ast.h"

typedef struct Interpreter_Struct{} Interpreter;

Interpreter* new_interpreter();
AST* interp_interpreter(Interpreter* com, AST* node);
AST* interp_variable_definition_interpreter(Interpreter* com, AST* node);
AST* interp_variable_interpreter(Interpreter* com, AST* node);
AST* interp_function_defination_interpreter(Interpreter* com, AST* node);
AST* interp_function_call_interpreter(Interpreter* com, AST* node);
AST* interp_string_interpreter(Interpreter* com, AST* node);
AST* interp_compound_interpreter(Interpreter* com, AST* node);
AST* interp_binary_op_interpreter(Interpreter* com, AST* node);

#endif