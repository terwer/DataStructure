#include <stdio.h>
#include "ALGraph.h"


void print(char *i)
{
	printf("%s ",i);
}

int main(){
	ALGraph G;
	CreateGraph(&G);
	return 0;
}