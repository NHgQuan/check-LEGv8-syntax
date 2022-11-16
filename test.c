//#include "dataStructure.h"
#include "SyntaxCheck.c"
#include "dataStructure.c"

struct foo2 
{
    int a;
    char b;
};

void foo(struct foo2 F)
{
    F.a = 2;
}



int main()
{
    // foo2 newfoo2={1, 'a'};
    // //char* b;
    // foo(newfoo2);

    // printf("%d\n",newfoo2.a);

    // char a[] = "abc def ghk";
    // for(int i = 0; i < lenStr(a); i++)
    // {
    //     char* cloneStr = deepCopyStr(a);
    //     removeChar(cloneStr, i);
    //     printf("%s\n", cloneStr);
    // }

    char* intruction = "     abc $1     $2 $3";  
    
    Node* ittComp = separateIntruction(intruction);
    Node* temp = ittComp;
    while(temp)
    {
        printf("%s\n", (temp)->data);
        temp = temp->next;
    }
}