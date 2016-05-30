//
//  Stack.h
//  stack
//
//  Created by Terwer Green on 16/5/30.
//  Copyright © 2016年 Terwer Green. All rights reserved.
//

#define INITIAL_StackIZE 20

typedef struct {
	size_t size;
	int top;
	char *items;

} Stack;

void initStack(Stack * stack, size_t size);

void push(Stack * stack, char item);

char pop(Stack * stack);

int isEmpty(Stack * stack);

void clearStack(Stack * stack);


