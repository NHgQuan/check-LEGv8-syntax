//#include "dataStructure.h"
#include "SyntaxCheck.c"
#include "dataStructure.c"

int main()
{
    

    char* intruction = "  LDUR    X2   , [  X0   ,    0  ]  ";  
    Node* ittComp = separateIntruction(intruction);
    Node* temp = ittComp;
    while(temp)
    {
        printf("%s\n", (temp)->data);
        temp = temp->next;
    }






}