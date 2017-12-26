/*
Vishal Damojipurapu 
vdamojip@ucsc.edu 
PA5
12/5/17
*/
#include "Graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#define WHITE 1//vertex is undiscovered
#define GREY 2//neighboring vertex is undiscovered
#define BLACK 3//vertex is discovered

typedef struct GraphObj//used to define the struct of the graph object
{
	List* adj; 
	int* color;
	int* parent; 
	int order;
	int size;
	int* discover;
	int* finish;
	int time;
}GraphObj;

Graph newGraph(int n)
{
	if(n <= 0)
	{
		printf("number of vertices must be at least 1");
		exit(1);
	}

	//allocates memory for everything that is needed
	Graph G = malloc(sizeof(GraphObj));//the graph itself
	G->adj = malloc((n+1)*sizeof(List));//neighbors of the vertex
	G->color = malloc((n+1)*sizeof(int));//the color of a given
	G->parent = malloc((n+1)*sizeof(int));//parent of a given vertex
	G->order = n;//number of vertices in the graph
	G->size = 0;//size of the graph
	G->discover = malloc((n+1)*sizeof(int));//discover time
	G->finish = malloc((n+1)*sizeof(int));//finish time
	G->time = 0;//time used for the discovery and finish
	
	for(int i = 1; i <= n; i++)//initialize everything
	{
		G->adj[i] = newList();
		G->color[i] = WHITE;
		G->parent[i] = NIL;
		G->discover[i] = UNDEF;
		G->finish[i] = UNDEF;
	}

	return G;
}

void freeGraph(Graph* pG)//frees up all memory so no memory is lost
{
	if(*pG != NULL || pG != NULL)
	{
		for(int i = 1; i <= (*pG)->order; i++)
		{
			freeList(&(*pG)->adj[i]);
		}

		free((*pG)->color);					
		(*pG)->color = NULL;
		free((*pG)->parent);
		(*pG)->parent = NULL;
		free((*pG)->adj);
		(*pG)->adj = NULL;
		free((*pG)->discover);
		(*pG)->discover = NULL;
		free((*pG)->finish);
		(*pG)->finish = NULL;
		free(*pG);
		(*pG) = NULL;

	}
	else
	{
		printf("cannot access pG if its not there");
		exit(1);
	}
}

int getOrder(Graph G)//returns the number of vertices in the graph
{
	if(G != NULL)
	{
		return G->order; 
	}
	else
	{
		printf("Cannot call getOrder because graph is NULL");
		exit(1);
	}
}

int getSize(Graph G)//returns the size of the graph
{
	if(G != NULL)
	{
		return G->size;
	}
	else
	{
		printf("Cannot call getSize because graph is NULL");
		exit(1);
	}
}

int getParent(Graph G, int u)//returns the parent of a given vertex
{
	if(G == NULL)
	{
		printf("Cannot call getParent because graph is NULL");
		exit(1);
	}
	if(u > getOrder(G) || u < 1)
	{
		printf("Cannot call getParent because graph is NULL");
		exit(1);
	}
	return G->parent[u];
}

int getDiscover(Graph G, int u)//returns discover time of a vertex
{
	if(G == NULL)
	{
		printf("Cannot call getDiscover because graph is NULL");
		exit(1);
	}
	if(u > getOrder(G) || u < 1)
	{
		printf("Cannot call getDiscover because graph is NULL");
		exit(1);
	}
	return G->discover[u];
}

int getFinish(Graph G, int u)//returns finish time of a vertex u
{
	if(G == NULL)
	{
		printf("Cannot call getFinish because graph is NULL");
		exit(1);
	}
	if(u > getOrder(G) || u < 1)
	{
		printf("Cannot call getFinish because graph is NULL");
		exit(1);
	}
	return G->finish[u];
}

void addArc(Graph G, int u, int v)//adds an arc from vertex to another
{
	if(G == NULL)
	{
		printf("cannot use addArc on a NULL graph");
		exit(1);
	}
	if(u > getOrder(G) || u < 1 || v > getOrder(G) || v < 1)
	{
		printf("Cannot call addArc when u isn't in the range");
		exit(1);
	}

	moveFront(G->adj[u]);//moves front to iterate through adjacent array

	while(index(G->adj[u]) != -1)
	{
		if(v <= get(G->adj[u]))//inserts into the right position 
		{
			insertBefore(G->adj[u],v);
			G->size++;
			return;
		}
		moveNext(G->adj[u]);
	}
	if(index(G->adj[u]) != -1)
	{
		insertBefore(G->adj[u],v);
	}
	else
	{
		append(G->adj[u],v);
	}

	G->size++;
}

void addEdge(Graph G, int u, int v)//adds one edge to the graph
{
	if(G == NULL)
	{
		printf("cannot use addEdge on a NULL graph");
		exit(1);
	}
	if(u > getOrder(G) || u < 1 || v > getOrder(G) || v < 1)
	{
		printf("Cannot call addEdge when u isn't in the range");
		exit(1);
	}

	//adding the arc from one vertex to another and then vice versa is the same as adding an edge
	addArc(G,u,v);
	addArc(G,v,u);
	G->size--;//adding arc twice so you should decrement once(should be 1+1-1)
}

void DFS(Graph G, List S)
{
	if(length(S) != getOrder(G))
	{
		printf("Cannot use DFS if length of S is not equal number of vertices");
		exit(1);
	}

	for(int i = 1; i <= getOrder(G); i++)
	{
		G->color[i] = 1;
		G->parent[i] = NIL;
	}

	G->time = 0;

	for(moveFront(S); index(S) != -1; moveNext(S))
	{
		if(G->color[get(S)] == 1)
		{
			Visit(G,get(S),S);
		}
	}

	int x = 1;
	while(x <= getOrder(G))//deletes back of list to get vertices in correct order
	{
		deleteBack(S);
		x++;
	}
}

Graph transpose(Graph G)//retuurns a transposed Graph
{
	if(G == NULL)
	{
		printf("Cannot use DFS if length of S is not equal number of vertices");
		exit(1);
	}

	Graph transposed = newGraph(getOrder(G));
	//List L;

	for(int i = 1; i <= getOrder(G); i++)
	{
		for(moveFront(G->adj[i]); index(G->adj[i]) != -1; moveNext(G->adj[i]))
		{
			append(transposed->adj[get(G->adj[i])],i);
		}
	}

	return transposed;
}

Graph copyGraph(Graph G)//returns a copied Graph
{
	if(G == NULL)
	{
		printf("cannot use copyGraph on null graph");
		exit(1);
	}

	Graph temp = newGraph(getOrder(G));

	temp->size = G->size;
	temp->order = G->order;
	temp->time = G->time;

	for(int i = 1; i <= getOrder(G); i++)
	{
		temp->adj[i] = copyList(G->adj[i]);
	}

	return temp;

}

void printGraph(FILE* out, Graph G)//prints out the graph
{
	if(G != NULL)
	{
		for(int i = 1; i <= getOrder(G); i++)
		{
			List L = G->adj[i]; 
			fprintf(out, " %d: ", i);//prints to the output file

			moveFront(L);
			while(index(L) != -1)
			{
				fprintf(out, "%d ", get(L)); 
				moveNext(L);
			}

			fprintf(out, "\n");
		}
	}
	else
	{
		printf("Cannot print graph");
		exit(1);
	}
}

void Visit(Graph G, int u, List S)//recursive method for DFS
{
	if(G == NULL)
	{
		printf("cannot use Visit on an empty graph");
		exit(1);
	}
	G->time = G->time + 1;
	G->discover[u] = G->time; 
	G->color[u] = 2;
	for(moveFront(G->adj[u]); index(G->adj[u]) != -1; moveNext(G->adj[u]))
	{
		if(G->color[get(G->adj[u])] == 1)
		{
			G->parent[get(G->adj[u])] = u;
			Visit(G,get(G->adj[u]),S);
		}
	}
	G->color[u] = 3;
	G->time = (G->time) + 1;
	G->finish[u] = G->time;
	prepend(S,u);
}


