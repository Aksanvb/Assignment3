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

// REMEMBER to change this file name to the required format of lastnameFirstnameA3.c

// function definition of readInput

int readInput(FILE * inputData,
                char stop[][MAX_WORD],
                int * numStop,
                char variant[][MAX_WORD],
                char lemma[][MAX_WORD],
                int * numLemma,
                char post[][MAX_LEN]) {

   
   int i;
   int num;
   char line [MAX_LEN];
   
   // read num of stop words
   
   fscanf(inputData, "%d", &num);
   fgetc(inputData);
   
   *numStop = num;
   
   // read the stop words
   
   for (i = 0; i < num; i++) {
      fgets (line, MAX_LEN, inputData);
      line [strlen (line) - 1] = '\0';
      strcpy( stop[i],line);
   }
   
   // repeat the same as above for lemma pairs
   
   fscanf(inputData, "%d", &num);
   fgetc(inputData);
   
   *numLemma = num;
   
   for (i = 0; i < num; i++) {
      fgets (line, MAX_LEN, inputData);        // read the variant
      line [strlen (line) - 1] = '\0';
      strcpy( variant[i],line);
      
      fgets (line, MAX_LEN, inputData);        // read the lemma
      line [strlen (line) - 1] = '\0';
      strcpy( lemma[i],line);
   }
   
   // repeat the same as above for posts
   
   fscanf(inputData, "%d", &num);
   fgetc(inputData);
   
   for (i = 0; i < num; i++) {
      fgets (line, MAX_LEN, inputData);
      line [strlen (line) - 1] = '\0';
      strcpy( post[i],line);
   }
   
   return num;          // return num of posts read
}

// define all other functions here

void normalize(char line[]) {

   for(int i = 0; line[i] != '\0'; i++) {
      line[i] = tolower(line[i]);

      if(line[i] == '.' || line[i] == ',' || line[i] == '?' || line[i] == '!' || line[i] == ';' || line[i] == ':' || line[i] == '"' || line[i] == '\'' || line[i] == '(' || line[i] == ')' || line[i] == '[' || line[i] == ']' || line[i] == '{' || line[i] == '}' || line[i] == '-' || line[i] == '_' || line[i] == '/' || line[i] == '\\') {
         line[i] = ' ';
      }
   }
}

int tokenize(const char line[], char tokens[][MAX_WORD]) {
   int i = 0;
   int j = 0;
   int count = 0;

   while(line[i] != '\0' && count < MAX_TOKENS) {
      if(line[i] != ' ') {
         if(j< MAX_WORD - 1) {
            tokens[count][j] = line[i];
            j++;
         }
      }else if(line[i] == ' ' && j>0) {
         tokens[count][j] = '\0';
         count++;
         j = 0;
      }
      i++;
   }
     if(j>0) {
      tokens[count][j] = '\0';
      count++;
      }
   return count;
   
}

int removeStopWords(char tokens[][MAX_WORD], int count, char stop[][MAX_WORD], int S){

   int i, j;
   int countWithoutStopWords = 0;
   int isStopWord;

   for(i = 0; i < count; i++) {
      isStopWord = 0;
      for(j = 0; j < S; j++) {
         if(strcmp(tokens[i], stop[j]) == 0) {
            isStopWord = 1;
            break;
         }
      }
      if(isStopWord == 0) {
            strcpy(tokens[countWithoutStopWords], tokens[i]);
            countWithoutStopWords++;
      }
   }
   return countWithoutStopWords;
}

void applyLemmaMap(char tokens[][MAX_WORD], int count, char variant[][MAX_WORD], char lemma[][MAX_WORD], int L) {
   int i, j;
   for(i = 0; i < count; i++) {
      for(j = 0; j < L; j++) {
         if(strcmp(tokens[i], variant[j]) == 0) {
            strcpy(tokens[i], lemma[j]);
            break;
         }
      }
   }
}