#include <stdio.h>
#include "BiTree.h"

Status visitT(TElemType e){
#ifdef CHAR
	printf("%c ",e);
#endif
#ifdef INT
	printf("%d ",e);
#endif
	return OK;
}

int main(){
	BiTree T;
	InitBiTree(&T);
	CreateBiTree(&T);

	printf("\n************************************************************************\n");
	printf("*二叉树的先序遍历                                                      *\n");
	printf("************************************************************************\n");
	PreOrderTraverse(T,visitT);

	printf("\n\n************************************************************************\n");
	printf("*二叉树的中序遍历                                                      *\n");
	printf("************************************************************************\n");
	InOrderTraverse(T,visitT);

	printf("\n\n************************************************************************\n");
	printf("*二叉树的后序遍历                                                      *\n");
	printf("************************************************************************\n");
	PostOrderTraverse(T,visitT);

	printf("\n\n************************************************************************\n");
	printf("*二叉树的层次遍历                                                      *\n");
	printf("************************************************************************\n");
	LevelOrderTraverse(T,visitT);

	system("pause");
	return 0;
}