#include <stdio.h>
#include "MGraph.h"

Status visit(VertexType i) {
	printf("%s\n", i);
	return OK;
}

int main() {
	setvbuf(stdout,NULL,_IONBF,0);
	MGraph G;
	CreateGraph(&G);
	Display(G);
	printf("--------通过结点结点值查找序号------\n");
	int l= LocateVex(G, "B");
	printf("%d\n", l);
	printf("--------通过序号查找结点的值------\n");
	VertexType a;
	strcpy(a, *GetVex(G, 2));
	printf("%s\n", a);
	printf("--------深度优先遍历开始------\n");
	DFSTraverse(G, visit);//
	return 0;

}