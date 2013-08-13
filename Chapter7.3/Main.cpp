#include <stdio.h>
#include <stdlib.h>
#include "OLGraph.h"

Status visit(VertexType i) {
	printf("%s ", i);
	return OK;
}


int main(){
	OLGraph G;
	CreateDG(&G);
	Display(G);
	DFSTraverse(G,visit);
    BFSTraverse(G,visit);
	system("pause");
	return 0;
}