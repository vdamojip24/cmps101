/*
Vishal Damojipurapu 
vdamojip@ucsc.edu 
PA4
11/18/17
*/
#include "Graph.h"
#include "List.h"
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	//Testing out all the graph operations and sorting
	List L = newList();
	Graph G = newGraph(10);

	for(int i = 1; i <= 10; i++)
	{
		for(int j = 1; j <= 10; j++)
		{
			addEdge(G,i,j);
		}
	}

	addArc(G,11,11);

	printf("%d", getOrder(G));
	printf("\n");

	printf("%d", getSize(G));
	printf("\n");	

	printf("%d", getSource(G));
	printf("\n");

	printf("%d", getParent(G, 1));
	printf("\n");

	printf("%d", getDist(G, 1));
	printf("\n");

	BFS(G,5);
	getPath(L,G,10);

	printGraph(stdout, G);

}