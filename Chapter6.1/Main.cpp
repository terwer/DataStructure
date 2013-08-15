#include <stdio.h>
#include "SqBiTree.h"

Status visit(TElemType e){
	printf("%c ",e);
	return OK;
}

int main(){ 
	SqBiTree bt;
	InitBiTree(bt);
	CreateBiTree(bt);
	PreOrderTraverse(bt,visit);
	InOrderTraverse(bt,visit);
	PostOrderTraverse(bt,visit);
	LevelOrderTraverse(bt,visit);
	PrintTree(bt);
	system("pause");
	return 0;
}


