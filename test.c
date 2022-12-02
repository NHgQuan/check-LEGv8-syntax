//#include "dataStructure.h"
#include "SyntaxCheck.c"
#include "dataStructure.c"
#include "math.c"

int main()
{
    char* str1 ="abc abc bcd bc b aaa";
    char* str2 ="aa";
    printf("%d", strstr(str1, str2));
    
}