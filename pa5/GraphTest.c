/*
Vishal Damojipurapu 
vdamojip@ucsc.edu 
PA5
12/5/17
*/

#include "Graph.h"
#include <stdlib.h>
#include <stdio.h>
#include "List.h"

int main(int argc, char* argv[])
{
	//Testing out all the graph operations and DFS sorting
	List L = newList();
	Graph G = newGraph(10);

	for(int i = 1; i <= 10; i++)
	{
		for(int j = 1; j <= 10; j++)
		{
			addEdge(G,i,j);
		}
	}

	for(int i = 1; i <= 10; i++)
	{
		append(S,i);
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

	DFS(G,L);
	getPath(L,G,10);

	printGraph(stdout, G);

}