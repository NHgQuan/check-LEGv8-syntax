#ifndef __DATA_STRUCTURE_H__
#define __DATA_STRUCTURE_H__

#include <stdio.h>
#include <stdlib.h>

typedef char inttType;//intructionType

typedef enum { F, T } boolean;

typedef struct fData
{
        int nums;
        char** data;
} fData;

typedef struct Node
{
  char* data;
  struct Node *next;
} Node ;

void appendN(struct Node** head_ref, char* new_data);

void clearN(struct Node** head);

int lengthN(struct Node** head);

boolean compareStr(char* str1, char* str2);

int lenStr(char* str);

void standardizeIntt(char* a);

char* deepCopyStr(char* str);

char* takeFirstWord(char* str);

void removeChar(char str[], int index);

char* separateFirstWord(char str[]);

char* separateByBrackets(char str[]);

boolean isMatchingPair(char character1, char character2);

boolean areBracketsBalanced(char exp[]);

// Function to pushS an item to stack
void pushS(struct sNode** top_ref, int new_data);
 
// Function to popS an item from stack
int popS(struct sNode** top_ref);



#endif