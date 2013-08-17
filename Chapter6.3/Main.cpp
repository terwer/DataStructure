#include <stdio.h>
#include "BiThrTree.h"

Status vi(TElemType c){
#if CHAR
	printf("%c ",c);
#else
	printf("%d ",c);
#endif
	return OK;
}

int main(){
	BiThrTree T;
	CreateBiThrTree(&T);

	printf("\n************************************************************************\n");
	printf("*线索二叉树的中序线索化                                                  *\n");
	printf("************************************************************************\n");
	InOrderTraverse_Thr(T,vi);

	system("pause");
	return 0;
}