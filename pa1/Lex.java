//Vishal Damojipurapu PA1

import java.io.*;
import java.util.Scanner;   

class Lex{
   public static void main(String[] args) throws IOException
   {
      Scanner in = null;
      PrintWriter out = null;
      String line = "";
      int i, n, lineNumber = 0;
      List L = new List();

      if(args.length != 2)//checks to make sure there is an input file and named output file
      {
         System.err.println("Usage: fileIO infile outfile");
         System.exit(1);
      }
      
      in = new Scanner(new File(args[0]));
      out = new PrintWriter(new FileWriter(args[1]));

      while(in.hasNextLine())
      {
         lineNumber++;
         in.nextLine();
      }    
      
      in = new Scanner(new File(args[0]));//sets scanner back to the beginning
      String[] token = new String[lineNumber];

      for(i = 0; i < token.length; i++)
      {
         token[i] = in.nextLine();//populates array
      }

      n = token.length;
      sort(L, token);//sorts input file
      L.moveFront();//moves to front to write to the output file

      while(L.index() >= 0)
      {
         out.println(token[L.get()]);//writes to output file
         L.moveNext();//increments
      }
      
      in.close();
      out.close();
   }

   static void sort(List L, String[] token)
   {
      int n = token.length;
      if(n <= 0)//error checking for a negative token length
      {
         return;
      }
      L.append(0);//adds first element into list and uses it for the comparisons
      L.moveFront();

      for(int i = 1; i < n; i++)
      {
         String temp = token[i];//creates temp array and uses it for the comparisons
         L.moveBack();//cursor points to the back in the beginning

         //sorts
         while(L.index() >= 0 && temp.compareTo(token[L.get()]) < 0)
         {
            L.movePrev(); 
         }
         if(L.index() >= 0)
         {
            L.insertAfter(i);
         }
         else
         {
            L.prepend(i);
         }
      }

      
   }

}