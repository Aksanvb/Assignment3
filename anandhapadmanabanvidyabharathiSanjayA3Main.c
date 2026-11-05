/************************anandhapadmanabanVidyabharathiSanjayA3.c************** 
Student Name: Sanjay Anandhapadmanaban Vidyabharathi Email Id: sanandha@uoguelph.ca  
Due Date: November 11, 2026 Course Name: CIS 1300  
I have exclusive control over this submission via my password. 
By including this statement in this header comment, I certify that:  
1) I have read and understood the University policy on academic integrity. 2) I 
have completed the Computing with Integrity Tutorial on Moodle; and 3) I have 
achieved at least 80% in the Computing with Integrity Self Test.  
I assert that this work is my own. I have appropriately acknowledged any and 
all material that I have used, whether directly quoted or paraphrased. 
Furthermore, I certify that this assignment was prepared by me specifically for 
this course.  
********************************************************/
/********************************************************* 
Compiling the program 
The program should be compiled using the following flags: -std=c99 -Wall  
compiling: 
gcc -std=c99 -Wall anandhapadmanabanvidyabharathiSanjayA3.c anandhapadmanabanvidyabharathiSanjayA3Main.c 
Running: ./a.out  
OR  
gcc -std=c99 -Wall anandhapadmanabanvidyabharathiSanjayA3.c anandhapadmanabanvidyabharathiSanjayA3Main.c -o miniNLP  
Running the Program: ./miniNLP
*********************************************************/

#include "givenA3.h"

int main () {

   FILE * fileInput = NULL;
   
   char stop[MAX_STOP][MAX_WORD];
   char variant[MAX_LEMMA][MAX_WORD];
   char lemma[MAX_LEMMA][MAX_WORD];
   char post[MAX_POSTS][MAX_LEN];
   
   int numPosts;
   int numStops;
   int numLemma;

   int i;
   char tokens[MAX_TOKENS][MAX_WORD];
   int tokenCount;
   int j;
   int originalTokenCount;
   int removedCount;

   char filename [20];
   
   printf ("Enter filename: ");
   scanf ("%s", filename);
   
   fileInput = fopen (filename, "r");
   numPosts = readInput (fileInput, stop, &numStops, variant, lemma, &numLemma, post);
   
   
   // call other functions here
   for(i = 0; i < numPosts; i++){
      printf("Post %d original: %s\n", i+1, post[i]);
      normalize(post[i]);

      tokenCount = tokenize(post[i], tokens);
      originalTokenCount = tokenCount;
      printf("Number of tokens = %d\n", originalTokenCount);

      tokenCount = removeStopWords(tokens, tokenCount, stop, numStops);
      removedCount = originalTokenCount - tokenCount;
      printf("Num of stop words removed = %d\n", removedCount);

      applyLemmaMap(tokens, tokenCount, variant, lemma, numLemma);
      
      printf("Post %d cleaned: ", i+1);
      for(j = 0; j < tokenCount; j++){
         printf("%s ", tokens[j]);
      }
      printf("\n");
   }
   
   fclose (fileInput);
   return 0;
}

