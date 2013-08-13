#include <stdio.h>
#include "MGraph.h"

Status visit(VertexType i) {
	printf("%s\n", i);
	return OK;
}

int main() {
	MGraph G;
	CreateGraph(&G);
	Display(G);
	/*printf("--------ͨ�������ֵ�������------\n");
	int l;
	l= LocateVex(G,"B");
	printf("%d\n", l);
	printf("--------ͨ����Ų��ҽ���ֵ------\n");
	VertexType a;
	strcpy(a, *GetVex(G, 2));
	printf("%s\n", a);
	*/
	printf("\n--------������ȱ�����ʼ------\n");
	DFSTraverse(G, visit);
	system("pause");
	return 0;
}