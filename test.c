//#include "dataStructure.h"
#include "SyntaxCheck.c"
#include "dataStructure.c"
#include "math.c"

int main()
{
    

    // char* intruction = "  LDUR    X2   , [  X0   ,    0  ]  ";  
    // Node* ittComp = separateIntruction(intruction);
    // Node* temp = ittComp;
    // while(temp)
    // {
    //     printf("%s\n", (temp)->data);
    //     temp = temp->next;
    // }

    char* condition = "u12";
    int* bound = getImmBound(condition);

    for(int i = 0; i <2; i++)
    {
        printf("%d\n", bound[i]);
    }




}