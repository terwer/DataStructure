//
//  LinkedList.cpp
//  linkedlist
//
//  Created by Terwer Green on 16/5/30.
//  Copyright © 2016年 Terwer Green. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"

struct Node *createList()
{
	struct Node *newNode = (Node *)malloc(sizeof(struct Node));
    if (newNode != NULL){
		newNode->next = NULL;
    }
	return newNode;
}

void deleteNode(struct Node *prev)
{
	struct Node *nextNode = prev->next;
    if (nextNode == NULL){
		return;
    }

	prev->next = nextNode->next;
	nextNode->next = NULL;
    free(nextNode);
}

struct Node *insertNode(struct Node *prev,ElemType data)
{
	struct Node *newNode = (Node *)malloc(sizeof(struct Node));
	if (newNode != NULL) {
		newNode->data = data;
		newNode->next = prev->next;
		prev->next = newNode;
	}
	return newNode;
}

int length(struct Node *head)
{
	struct Node *curr = head;
	int len = 0;
	while (curr->next != NULL) {
		len++;
		curr = curr->next;
	}
	return len;
}

void print(struct Node *head)
{
    if (head->next == NULL) {
        printf("empty list!\n");
        return;
    }
    
	struct Node *curr = head->next;
	while (curr != NULL) {
		printf("%s",curr->data);
		printf(" ");
		curr = curr->next;
	}
	printf("\n");
}

struct Node *getNode(struct Node *head, int i)
{
	struct Node *curr = head;
	while (i > 0 && curr != NULL) {
		curr = curr->next;
		i--;
	}
	return curr;
}

void deleteList(struct Node *head)
{
	while (length(head) > 0) {
		deleteNode(head);
	}
	free(head);
}
