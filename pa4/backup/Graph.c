/*
Vishal Damojipurapu 
vdamojip@ucsc.edu 
PA4
11/18/17
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
	int* distance;
	int order;
	int size;
	int source;
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
	G->distance = malloc((n+1)*sizeof(int));//distance from the source vertex
	G->order = n;//number of vertices in the graph
	G->size = 0;//size of the graph
	G->source = NIL;//source of the graph
	
	for(int i = 1; i <= n; i++)
	{
		G->adj[i] = newList();
		G->color[i] = WHITE;
		G->parent[i] = NIL;
		G->distance[i] = INF;
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
		free((*pG)->distance);
		(*pG)->distance = NULL;
		free((*pG)->adj);
		(*pG)->adj = NULL;
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

int getSource(Graph G)//returns the source of the graph
{
	if(G != NULL)
	{
		return G->source;
	}
	else
	{
		printf("Cannot call getSource because graph is NULL");
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

int getDist(Graph G, int u)//returns the distance of a given vertex from the source
{
	if(G == NULL)
	{
		printf("Cannot call getDist because graph is NULL");
		exit(1);
	}
	if(u > getOrder(G) || u < 1)
	{
		printf("Cannot call getDist because graph is NULL");
		exit(1);
	}
	return G->distance[u];
}

void getPath(List L, Graph G, int u)//finds the path for one vertex to another
{
	if(getSource(G) == NIL)					
	{
		printf("getSource of the graph is NIL");
		exit(1);
	}
	if(u > getOrder(G) || u < 1)
	{
		printf("Cannot call getPath when u isn't in the range");
		exit(1);
	}
	if(G == NULL)
	{
		printf("Cannot call getPath because G is NULL");
		exit(1);
	}
	if(L == NULL)
	{
		printf("Cannot call getPath because L is NULL");
		exit(1);
	}
	if(G->source == u)
	{
		append(L,u);
	}
	else if(G->parent[u] == NIL)
	{
		append(L, NIL);
	}
	else
	{
		getPath(L, G, G->parent[u]);//uses recursion 
		append(L, u);
	}
}

void makeNull(Graph G)//makes the graph null by clearing every vertex
{
	if(G == NULL)
	{
		printf("cannot use makeNull on a NULL graph");
		exit(1);
	}
	else
	{
		for(int i = 1; i <= getOrder(G); i++)
		{
			clear(G->adj[i]);
		}
	}	
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

void BFS(Graph G, int s)//breadth first search sorting algorithm 
{
	if(G == NULL)
	{
		printf("cannot use BFS on a NULL graph");
		exit(1);
	}
	if(s > getOrder(G) || s < 1)
	{
		printf("cannot use BFS on s that doesn't fall in the range");
		exit(1);
	}

	List Q = newList();//creates a new list that is used as the queue

	//initializes everything
	for(int i = 1; i <= getOrder(G); i++)
	{
		G->distance[i] = INF;
		G->parent[i] = NIL;
		G->color[i] = WHITE;
	}

	G->distance[s] = 0;
	G->parent[s] = NIL;
	G->color[s] = GREY;
	G->source = s;
	int tempE;//temporary variable
	
	append(Q,s);//appends the source to the queue

	while(length(Q) > 0)
	{
		tempE = front(Q);//sets the temporary vertex to the front of the queue
		List tempAdj = G->adj[tempE];//creates a new temporary list for the neighboring vertices
		deleteFront(Q);

		for(moveFront(tempAdj); index(tempAdj) != -1; moveNext(tempAdj))
		{
			int v = get(tempAdj);//vertex

			if(G->color[v] == WHITE)
			{
				G->color[v] = GREY;
				G->distance[v] = (G->distance[tempE]) + 1;
				G->parent[v] = tempE; 
				append(Q,v);
			}
		}

		G->color[tempE] = BLACK;//sets the discovered vertex to black
	}

	freeList(&Q);//frees the queue that was created earlier
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


