//
//  main.cpp
//  stack
//
//  Created by Terwer Green on 16/5/30.
//  Copyright © 2016年 Terwer Green. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Stack.h"

/*The program accepts one command line argument: a user input string. If no*/
/*user input is specified, the program will use the sample input provided*/
/*PLEASE NOTE: due to a bash feature, if entering brackets as a command line*/
/*argument, they need to be preceeded by a forward slash (\) or enclosed in a quote (') */

int main (int argc, char *argv[]){
    
    Stack stack;
    
    int i, open = 0, close = 0;
    
    /*sample input*/
    const char *input;
    
    /*check command line args*/
    if (argc != 2){
        printf("No user input detected, using example input.\n");
        input = "((a) + (b)) + ((c)(a))";
    }
    else {
        printf("User input detected.\n");
        input = argv[1];
    }
    
    initStack(&stack, INITIAL_StackIZE);
    
    printf("Input String: %s\n", input);
    
    for (i = 0; i < strlen(input); i++){
        /*check for open brackets. If it is one, push to stack.
         If it is closed, pop from stack.*/
        
        if (input[i] == '('){
            open++;
            printf("Pushing ( to stack.\n");
            push(&stack, '(');
        }
        else if (input[i] == ')'){
            close++;
            printf("Popping ) from stack.\n");
            pop(&stack);
        }
    }
    
    printf("Number of open brackets: %i. Number of close brackets: %i.\n", open, close);
    if (open == close){
        printf("Matching brackets.\n");
        
    }else {
        printf("Non matching brackets.\n");
    }
    
    clearStack(&stack);
    
    return 0;
}
