#include<stdlib.h>
#include<stdio.h>
#include "dataStructure.c"
#include "Readfile.c"

inttType intructionType(struct Node *intruction);

boolean isRegister(char* parameter);

boolean isImediate(char* parameter);

boolean isTargetAddress(char* parameter);

boolean parametersIsEnough(struct Node* node, char typeIntruction);

void checkrType(struct Node* node);

void checkiType(struct Node* node);

void checkjType(struct Node* node);

boolean haveBrackets(char* str);

struct Node* separateIntruction(char* intruction);

void checkIntruction(char* intruction, const int index);
