#include "../include/main.h"
#include <stdio.h>
#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/interpreter.h"

char* read_file(char* path){
    FILE* file = fopen(path, "rb");
    long size;
    char* buffer = 0;

    if(file == NULL){
        fprintf(stderr, "[File Error] %s:%d: Failed to open file: %s\n", __FILE__, __LINE__, path);
        exit(2);
    }

    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fseek(file, 0, SEEK_SET);

    buffer = calloc(size + 1, sizeof(char));
    if (!buffer) {
        perror("[Memory Error] Error during allocating buffer");
        exit(2);
    }

    if (fread(buffer, 1, (size_t)size, file) != (size_t)size) {
        perror("[File Error] Error during reading file");
        free(buffer);
        exit(2);
    }

    fclose(file);
    return buffer;

}

int main(int argc, char* argv[]){
    if(argc >= 2){
        char* contents = read_file(argv[1]);
        
        Lexer* lex = new_lexer(contents);
        if (!lex) {
            fprintf(stderr, "Failed to initialize lexer\n");
            free(contents);
            exit(2);
        }
        
        /*Token* tok = (void*)0;
        while((tok = get_token_lexer(lex))->type != TT_EOF){
            printf("TOKEN(%d, %s)\n", tok->type, tok->value);
        }*/
        
       Parser* parser = new_parser(lex);
       AST* root = parse_parser(parser, parser->scope);
       Interpreter* interpreter = new_interpreter();
       interp_interpreter(interpreter, root);
       //printf("%d\n%d\n", root->type, root->compound_size);

        free(contents);
        free(parser);
        free(root);
        free(interpreter);
    }else{
        printf("Usage: %s [filepath]\n", argv[0]);
    }
    
    return 0;
}