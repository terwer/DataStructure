#include <stdio.h>
#include "MGraph.h"

Status visit(VertexType i) {
	printf("%s ", i);
	return OK;
}

int main() {
	MGraph G;
	CreateGraph(&G);
	Display(G);
	DFSTraverse(G, visit);
	BFSTraverse(G,visit);
	system("pause");
	return 0;
}