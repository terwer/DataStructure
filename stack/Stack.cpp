//
//  Stack.cpp
//  stack
//
//  Created by Terwer Green on 16/5/30.
//  Copyright © 2016年 Terwer Green. All rights reserved.
//

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "stack.h"

void initStack(Stack * stack, size_t size){
	
	assert(stack != NULL);

	stack->size = size;
	stack->top = 0;

	if ((stack->items = (char *)malloc(sizeof(char) * size)) == NULL) {
		fprintf(stderr, "Memory allocation for initStack failed! "
			"Aborting data entry !\n");
		exit(EXIT_FAILURE);
	}
}

void push(Stack * stack, char item){
	
	assert(stack != NULL);
	assert(stack->items != NULL);

	if (stack->size == stack->top) {
		stack->size = stack->size * 2;
		if ((stack->items = (char *)realloc(stack->items,
					sizeof(int) * stack->size)) == NULL) {
			fprintf(stderr, "Memory reallocation for stack_push failed! "
				"Aborting data entry !\n");
			exit(EXIT_FAILURE);
		}
	}
	stack->items[stack->top] = item;
	stack->top = stack->top + 1;
}

char pop(Stack * stack){
	
	char val;

	if (isEmpty(stack) == 1){
		printf("Error: Nothing to pop, stack is empty!\n");
	}

	assert(stack != NULL);
	assert(stack->top > 0);
	assert(stack->items != NULL);

	val = stack->items[stack->top - 1];
	stack->top = stack->top - 1;

	return val;
}

int isEmpty(Stack * stack){
	
	assert(stack != NULL);

	if (stack->top <= 0)
		return 1;

	return 0;
}

void clearStack(Stack * stack){
	
	assert(stack != NULL);

	if(stack->items) free(stack->items);
}

