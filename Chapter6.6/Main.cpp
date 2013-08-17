#include <stdio.h>
#include "BiPTree.h"

Status visitT(BiPTree T){
	if(T) //T非空 
#ifdef CHAR
		printf("%c是",T->data);
	if(T->parent) {//T有双亲 
		printf("%c",T->parent->data);
#endif
#ifdef INT
		printf("%d是",T->data);
		if(T->parent) {//T有双亲
			printf("%d",T->parent->data);
#endif
			if(T->parent->lchild==T)
				printf("的左孩子\n");
			else
				printf("的右孩子\n");
		}
		else
			printf("根结点\n");
		return OK;
	}


int main(){
	BiPTree T;
	CreateBiTree(&T);

	printf("\n************************************************************************\n");
	printf("*二叉树的先序遍历                                                      *\n");
	printf("************************************************************************\n");
	PreOrderTraverse(T,visitT);

	printf("\n************************************************************************\n");
	printf("*二叉树的中序遍历                                                      *\n");
	printf("************************************************************************\n");
	InOrderTraverse(T,visitT);

	printf("\n************************************************************************\n");
	printf("*二叉树的后序遍历                                                      *\n");
	printf("************************************************************************\n");
	PostOrderTraverse(T,visitT);

	printf("\n************************************************************************\n");
	printf("*二叉树的先序遍历                                                      *\n");
	printf("************************************************************************\n");
	LevelOrderTraverse(T,visitT);
	system("pause");
	return 0;
}