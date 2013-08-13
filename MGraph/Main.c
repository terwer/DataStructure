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
	printf("--------ͨ�������ֵ�������------\n");
	int l= LocateVex(G, "B");
	printf("%d\n", l);
	printf("--------ͨ����Ų��ҽ���ֵ------\n");
	VertexType a;
	strcpy(a, *GetVex(G, 2));
	printf("%s\n", a);
	printf("--------������ȱ�����ʼ------\n");
	DFSTraverse(G, visit);
	return 0;

}