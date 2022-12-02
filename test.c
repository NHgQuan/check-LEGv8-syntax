//#include "dataStructure.h"
#include "SyntaxCheck.c"
#include "dataStructure.c"
#include "math.c"

int main()
{
    char* str1 ="   LDA     X0, array               ";
    standardizeIntt(&str1);
    printf("%s", str1);

    
}