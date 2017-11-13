/*Vishal Damojipurapu vdamojip@ucsc.edu PA2*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"

#define MAX_LEN 160

int main(int argc, char * argv[])
{

   int lineCount=0;//counts the number of lines for the array
   int i = 0;//incrementer for loop
   FILE *in = NULL;
   FILE *out = NULL;
   char line[MAX_LEN];

   // check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing 
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   while( fgets(line, MAX_LEN, in) != NULL)  
   {
      lineCount++;//finds the amount of lines needed for your array
   }


   fclose(in);
   in = fopen(argv[1], "r");//starts from the beginning
   
   char *arr[lineCount];

   while( fgets(line, MAX_LEN, in) != NULL)
   {
      arr[i] = malloc(strlen(line)+1);//creates space for a specific amount 
      strcpy(arr[i], line);//copies the line into the array
      i++;
   }

   
   

   
   List L = newList();

   //sorting method begins//
   append(L,0);//appends the first element into the list so you can start sorting
   moveFront(L);

   for(int j = 1; j < lineCount; j++)
   {
      char *temp = arr[j];//creates temp array for the correct size for sorting
      moveBack(L);//cursor points to the back in the beginning

         
      while(index(L) >= 0 && strcmp(temp, arr[get(L)]) < 0)
      {
         movePrev(L); 
      }
      if(index(L) >= 0)
      {
         insertAfter(L,j);
      }
      else
      {
         prepend(L,j);
      }
   }

   moveFront(L);

   while(index(L)>=0)
   {
      fprintf(out, arr[get(L)]);//prints to out file
      moveNext(L);//used to iterate through loop
   }

   for(i = 0; i < lineCount; i++)//used to iterate through array and free each element
   {
      free(arr[i]);
   }

   clear(L);
   freeList(&L);

   /* close files */
   fclose(in);
   fclose(out);

   return(0);
}

