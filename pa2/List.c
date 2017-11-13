/*Vishal Damojipurapu vdamojip@ucsc.edu PA2*/

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

typedef struct NodeObj
{
 	int data;//data inside node
    struct NodeObj* next;//use to point to next node
    struct NodeObj* previous;//use to point to previous node
}NodeObj;

typedef NodeObj* Node;

typedef struct ListObj
{
	Node front;
	Node back;
	Node cursorElement;
	int length;
	int cursorIndex;//index of the cursor
}ListObj;


// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = N->previous = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// Creates a new empty list.
List newList(void)
{	
	List L;
	L = malloc(sizeof(ListObj));
	L->front = L->back = NULL;
	L->cursorElement = NULL;
	L->cursorIndex = -1;
	L->length = 0;
	return (L);
}


// freeQueue()
// Frees all heap memory associated with Queue *pQ, and sets *pQ to NULL.S
void freeList(List* pL){
   if(pL!=NULL && *pL!=NULL) { 
      while( length(*pL) >= 1 ) { 
         deleteFront(*pL);
      }
      free(*pL);
      *pL = NULL;
   }
}


//returns length of list
int length(List L) 
{	
	if(L == NULL)
	{
		printf("List is NULL\n");
		exit(1);
	}
	else
	{
		return L->length;
	}
}

int index(List L) // If cursor is defined, returns the index of the cursor element,
 // otherwise returns -1.
{
	if(L->cursorElement != NULL)
	{
		return L->cursorIndex;
	}
	else
	{
		return -1;
	}
}

int front(List L) // Returns front element of list. Pre: length()>0
{
	if(L->length >= 1)
	{
		return L->front->data;
	}
	else
	{
		printf("Length of list is not >= 1\n");
		exit(1);
	}
}

int back(List L) // Returns back element of list. Pre: length()>0
{
	if(length(L) >= 1)
	{
		return L->back->data;
	}
	else
	{
		printf("Length of list is not >= 1\n");
		exit(1);
	}
}

int get(List L) // Returns cursor element. Pre: length()>0, index()>=0
{
	if(length(L) > 0 && L->cursorIndex >= 0)
	{
		return L->cursorElement->data;
	}
	else
	{ 
		printf("Length of list is not > 0 or cursorIndex is not >= 0\n");
		exit(1);
	}
}

// equals()
// returns true (1) if A is identical to B, false (0) otherwise
int equals(List A, List B){
   int eq = 0;
   Node N = NULL;
   Node M = NULL;

   if(A==NULL || B==NULL)
   {
      printf("List Error: calling equals() on NULL List reference\n");
      exit(1);
   }

   eq = ( A->length == B->length );
   N = A->front;//set to front so you can iterate through it after
   M = B->front;
   while( eq && N!=NULL){//use to compare nodes in each list
      eq = (N->data==M->data);
      N = N->next;
      M = M->next;
   }
   return eq;
}

// Manipulation procedures
void clear(List L) // Resets this List to its original empty state.
{
	while(L->back != NULL)//iterate and delete each node
	{
		deleteFront(L);
	}

	L->front = L->back = NULL;
	L->length = 0;
	L->cursorIndex = -1;
	L->cursorElement = NULL;

}

void moveFront(List L) // If List is non-empty, places the cursor under the front element,
 // otherwise does nothing.
{
	if(length(L) >= 1)		
	{
		L->cursorElement = L->front;
		L->cursorIndex = 0;
	}
}

void moveBack(List L) // If List is non-empty, places the cursor under the back element,
 // otherwise does nothing.
{
	if(length(L) >= 1)	
	{
		L->cursorElement = L->back;
		L->cursorIndex = length(L) - 1;
	}
}

void movePrev(List L) // If cursor is defined and not at front, moves cursor one step toward
 // front of this List, if cursor is defined and at front, cursor becomes
// undefined, if cursor is undefined does nothing.
{
	if(L->cursorElement != NULL && L->cursorElement != L->front)
	{
		L->cursorElement = L->cursorElement->previous;
		(L->cursorIndex)--;
	}
	else if(L->cursorElement != NULL && L->cursorElement == L->front )
	{
		L->cursorElement = NULL;
		L->cursorIndex = -1;
	}
}

void moveNext(List L) // If cursor is defined and not at back, moves cursor one step toward
 // back of this List, if cursor is defined and at back, cursor becomes
 // undefined, if cursor is undefined does nothing.
{
	if(L->cursorElement != NULL && L->cursorElement != L->back)
	{
		L->cursorElement = L->cursorElement->next;
		(L->cursorIndex)++;
	}
	else if(L->cursorElement != NULL && L->cursorElement == L->back)
	{
		L->cursorElement = NULL;
		L->cursorIndex = -1;
	}
}

void prepend(List L, int data) // Insert new element into this List. If List is non-empty,
 // insertion takes place before front element.
{
	Node N = newNode(data);//new node that is inserted at the beginning of the list
	if(length(L) == 0)
	{
		L->front = L->back = N;
		(L->length)++;
		L->cursorElement = L->front = L->back;
	}
	else
	{	
		L->front->previous = N;
		N->next = L->front;
		L->front = N;
		(L->length)++;
		if(L->cursorElement != NULL)
		{
			(L->cursorIndex)++;
		}
	}
}

void append(List L, int data) // Insert new element into this List. If List is non-empty,
 // insertion takes place after back element.
{
	Node N = newNode(data);// new node that is inserted at the end of the list
	if(length(L) == 0)
	{
		L->front = L->back = N;
		(L->length)++;
	}
	else
	{
		L->back->next = N;
		N->previous = L->back;
		L->back = N;			
		(L->length)++;
	}
}

void insertBefore(List L, int data) // Insert new element before cursor.
 // Pre: length()>0, index()>=0
{
	Node N = newNode(data);
	if(length(L) <= 0 || L->cursorIndex < 0)
	{
		printf("Length of list is <=0 or cursorIndex < 0\n");
		exit(1);
	}
	else if(L->cursorElement == L->front)//if the cursor is at the front, rearrange pointers so you can insert before the first node
	{
		N->previous = NULL;
		N->next = L->cursorElement;
		L->cursorElement->previous = N;
		L->front = N;
		(L->length)++;
		(L->cursorIndex)++;
	}
	else
	{
		N->next = L->cursorElement;
		N->previous = L->cursorElement->previous;
		L->cursorElement->previous->next = N;
		L->cursorElement->previous = N;
		(L->length)++;
		(L->cursorIndex)++;
	}
}

void insertAfter(List L, int data) // Inserts new element after cursor.
 // Pre: length()>0, index()>=0
{
	Node N = newNode(data);
	if(length(L) <= 0 || index(L) < 0)
	{
		printf("Length of list is <=0 or cursorIndex < 0\n");
		exit(1);
	}
	else if(L->cursorElement == L->back)//if cursor is at the back, rearrange pointers so you can insert new element at the end of the list
	{
		N->next = NULL;
		N->previous = L->cursorElement;
		L->cursorElement->next = N;
		L->back = N;
		(L->length)++;
	}
	else
	{
		N->previous = L->cursorElement;
		N->next = L->cursorElement->next;
		L->cursorElement->next->previous = N;
		L->cursorElement->next = N;
		(L->length)++;
	}
}

void deleteFront(List L) // Deletes the front element. Pre: length()>0
{
	if(length(L) >= 2)
	{
		L->front = L->front->next;
		if(L->cursorElement == L->front->previous)
		{
			L->cursorElement = NULL;
		}
		L->cursorIndex--;
		L->length--;
		freeNode(&L->front->previous);

	}
	else if (length(L) == 1) 
	{	
		(L->length)--;
		L->cursorIndex = -1;//you don't have to do this, but I  did it to support the fact that there are no nodes in the list
		L->cursorElement = NULL;
		L->back = NULL;
		freeNode(&L->front);
	}
	else
	{
		printf("Length of list is <=0\n");
		exit(1);
	}
}

void deleteBack(List L) // Deletes the back element. Pre: length()>0
{

	if(length(L) >= 2)
	{	
		if(L->cursorElement == L->back)
		{
			L->cursorIndex = -1;
			L->cursorElement = NULL; 
			L->back = L->back->previous;
			(L->length)--;
			freeNode(&L->back->next);

		}
		else
		{	
			L->back = L->back->previous;
			(L->length)--;
			freeNode(&L->back->next);
		}
	}
	else if (length(L) == 1) 			
	{
		freeNode(&L->back);
		L->front = L->back = NULL;//take out front
		(L->length)--;
		L->cursorIndex = -1;
	}
	else
	{
		printf("Length of list is <=0\n");
		exit(1);
	}
}

void delete(List L) // Deletes cursor element, making cursor undefined.
 // Pre: length()>0, index()>=0
// Other methods
{
	if(L->length <= 0 || L->cursorIndex < 0)
	{
		printf("Length of list is <=0 or cursorIndex < 0\n");
		exit(1);
	}
	else if(L->cursorElement == L->front)
	{
		deleteFront(L);
	}
	else if(L->cursorElement == L->back)
	{
		deleteBack(L);
	}
	else
	{
		L->cursorElement->next->previous = L->cursorElement->previous;
		L->cursorElement->previous->next = L->cursorElement->next;
		freeNode(&L->cursorElement);
		(L->length)--;
		L->cursorIndex = -1;
	}
	
}

void printList(FILE* out, List L)
{
   Node N = NULL;

   if( L == NULL )
   {
      printf("List Error: calling printList() on NULL List reference\n");
      exit(1);
   }

   for(N = L->front; N != NULL; N = N->next)
   {
      printf("%d ", N->data);
   }
}

List copyList(List L)
	{ // Returns a new List representing the same integer sequence as this
 // List. The cursor in the new list is undefined, regardless of the
 // state of the cursor in this List. This List is unchanged.
		List temp = newList();//creates new list that is returned
      	Node N = L->front;

      	while(N != NULL)//iterate through new list and append data into 
      	{
         	append(temp, N->data);
         	N = N->next;
      	}
      	return temp;
	}

