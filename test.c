//#include "dataStructure.h"
#include "SyntaxCheck.c"
#include "dataStructure.c"
#include "math.c"

int main()
{
    char * intrction = "ADDI $s0 ,$s1, 10000000000000000000a";
    // checkIntruction(intrction, 1);
    printf("%c", backStr(intrction));
}