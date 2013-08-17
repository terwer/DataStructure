#include <stdio.h>
#include "ALGraph.h"


void visit(char *i)
{
	printf("%s ",i);
}


int main(){
	ALGraph G;
	CreateGraph(&G);
	Display(G);
	DFSTraverse(G,visit);
	BFSTraverse(G,visit);
	system("pause");
	return 0;
}
