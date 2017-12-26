/*
Vishal Damojipurapu 
vdamojip@ucsc.edu 
PA5
12/5/17
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char* argv[])
{

	FILE *in = NULL;
	FILE *out = NULL;
	int n;//number of vertices passed
	int a;//one end of an edge
	int b;//other end of the same edge
	int scc = 0;//strongly connected components
	List S = newList();
	List temp = newList();

	if( argc != 3 )
	{
    	printf("Usage: %s <input file> <output file>\n", argv[0]);
    	exit(1);
    }

    in = fopen(argv[1], "r");//opens the infile 
    out = fopen(argv[2], "w");//opens the outfile
   
   if( in == NULL )
   {
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if( out == NULL )
   {
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   fscanf(in, " %d ", &n);//scans the number of vertices
   Graph G = newGraph(n);//creates the graph

   while(fscanf(in, "%d %d ", &a, &b))//builds the graph
   {
   		if(a != 0 && b != 0)
   		{
   			addArc(G,a,b);
   	   	}
   	   	else
   	   	{
   	   		break;
   	   	}
   }

   fprintf(out, "Adjacency list representation of G:\n");
   printGraph(out, G);//prints the graph to the outfile
   fprintf(out, "\n\n");

   for(int i = 1; i <= n; i++)//fills up the list with the vertices
   {
   		append(S,i);
   }

  
   DFS(G,S);
   
   Graph trans = transpose(G);
   DFS(trans,S); 

   for(moveFront(S); index(S) != -1; moveNext(S))//counts the number of scc's
   {
   		int e = get(S);
   		if(getParent(trans,e) == NIL)
   		{
   			scc++;
   		}
   }

   fprintf(out, "G contains %d strongly connected components: ", scc);
   fprintf(out, "\n");

   scc = 1;//resets the number of scc to print it out correctly

   for(moveBack(S); index(S) != -1; movePrev(S))
   {
  		int e = get(S);
  		prepend(temp, e);
  		if(getParent(trans,e) == NIL)
  		{
  			fprintf(out, "Component %d: ", scc);
  			printList(out,temp);
  			fprintf(out,"\n");
  			scc++;//updates number of scc's
  			clear(temp);//clears the list so you can continue to find the connected components for each tree from the list
  		}
   }

   //frees up all memory allocation
   freeList(&S);
   freeList(&temp);
   freeGraph(&G);
   freeGraph(&trans);

   //closes in and out file
   fclose(in);
   fclose(out);
}