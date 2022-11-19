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

    char* parameter = "123";
    char* inttTypeLine = "u12";
    isImediate(parameter, &inttTypeLine);




}