#include "dataStructure.c"
#include "Readfile.c"
#include "Syntaxcheck.c"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    // //get LEGv8 file 
    // struct fData* intructionSet = getData();
    
    // //check each line
    // for(int i = 0; i < intructionSet->nums; i++)
    // {
    //     standardizeStr(intructionSet->data[i]);
    //     checkIntruction(intructionSet->data[i], i);
    // }
    char* str = "[())";
    
    printf("%d", areBracketsBalanced(str));

}