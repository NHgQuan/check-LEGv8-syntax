//#include "dataStructure.h"
#include "SyntaxCheck.c"
#include "dataStructure.c"

int main()
{
    

    // char* intruction = "     abc $1     12234($2)($1)";  
    // char* testStr = "1234($1)";
    
    // Node* ittComp = separateIntruction(intruction);
    // Node* temp = ittComp;
    // while(temp)
    // {
    //     printf("%s\n", (temp)->data);
    //     temp = temp->next;
    // }

    char* str1 = "     abc $1,     12234($2)($1)";
    standardizeIntt(&str1);
    printf("%s\n", str1);    


}