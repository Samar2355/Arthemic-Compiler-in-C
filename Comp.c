// Samar Joshi
// GitHub:
// importing library
//Standard input output library
#include <stdio.h>
//Standard library function for memory allocation
#include <stdlib.h>
// importing isdigit for character type functions
#include <ctype.h>
//importing string library for string manipulation
#include <string.h>

// There are 3 main parts of the code,Tokenization,parsing and Evaluation
// Tokenization: Breaking the input into tokens
//Firstly we will enumearate the types of tokens we will be using
typedef enum {
    TOKEN_NUMBER,TOKEN_PLUS,TOKEN_MINUS,TOKEN_END} TokenType;

    //Now i will create a structure to represent the token
    typedef struct {
        TokenType type;
        int value;
    } Token;
    //Creating a function to tokenize the input string
    Token * tokenize(const char * input){
    Token *tokens = malloc(256 * sizeof(Token));
    int pos = 0;
    while (*input){
        if (isdigit((unsigned char)*input)){
            tokens[pos].type = TOKEN_NUMBER;
            char *end;
            tokens[pos].value = (int)strtol(input, &end, 10);
            input = end;
            pos++;
        } else if (*input == '+'){
            tokens[pos].type = TOKEN_PLUS;
            input++;
            pos++;
        } else if (*input == '-'){
            tokens[pos].type = TOKEN_MINUS;
            input++;
            pos++;
        } else {
            input++; // skip whitespace/other
        }
    }
    tokens[pos].type = TOKEN_END;
    return tokens;
    }
/*  
Second Component of this will be Parsing
The function of the parser is to mainly parse the tokens and evaluate the expression
*/
int parse(Token *tokens, int *result) {
    int pos = 0;
    if (tokens[pos].type != TOKEN_NUMBER) return 0;
    *result = tokens[pos].value;
    pos++;
    while (tokens[pos].type != TOKEN_END) {
        if (tokens[pos].type == TOKEN_PLUS) {
            pos++;
            if (tokens[pos].type != TOKEN_NUMBER) return 0;
            *result += tokens[pos].value;
            pos++;
        } else if (tokens[pos].type == TOKEN_MINUS) {
            pos++;
            if (tokens[pos].type != TOKEN_NUMBER) return 0;
            *result -= tokens[pos].value;
            pos++;
        } else {
            return 0;
        }
    }
    return 1;
}
/*
Finally our third component is Evaluation
Code generator definition (Assembly like instructions)
*/
void generate_assembly(Token *tokens){
    int pos = 0;
    // Load the first number > then register
    printf("LOAD , tokens[pos].value");
    pos++;
    while (tokens[pos].type != TOKEN_END){
        if (tokens[pos].type == TOKEN_PLUS){
            // If the token is +, generate ADD instructions
            pos++;
            printf("ADD %d\n, tokens[pos].value");
        } else if (tokens[pos].type == TOKEN_MINUS){
            // If the token is -, generate MINUS instructions
            pos++;
            printf("SUB %d\n, tokens[pos].value");
        }
        pos++;
    }
}

//Finally we will do our main function
int main(){
    // buffer to hold the string input
    char input[256];
    printf("Enter an arithmetic expression like 5 + 4 : ");
    fgets(input, sizeof(input), stdin);
    
    // next tokenize the inputs
    Token *tokens = tokenize(input);
    if (!tokens){
        return 1; //exit code for failure
    }
    int result;
    if (parse(tokens, &result)){
        printf("Parsed result: %d\n", result);
        // Generate the assembly line instruction
        generate_assembly(tokens);
    } else{
        printf("Invalid Expression\n");
    }
    free (tokens);
    return 0; //exit code for successfull execution
}