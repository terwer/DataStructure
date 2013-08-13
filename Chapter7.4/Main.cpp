#include <stdio.h>
#include <stdlib.h>
#include "AMLGraph.h"

Status visit(VertexType v)
{
	printf("%s ",v);
	return OK;
}

int main(){
	AMLGraph G;
	CreateGraph(&G);
	Display(G);
	DFSTraverse(G,visit);
	BFSTraverse(G,visit);
	system("pause");
	return 0;
}