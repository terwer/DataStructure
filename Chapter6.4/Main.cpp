#include <stdio.h>
#include "PTree.h"

void vi(TElemType c)
{
	printf("%c ",c);
}

int main(){
	PTree T;
	CreateTree(&T);
	Print(T);
	TraverseTree(T,vi);
	system("pause");
	return 0;
}