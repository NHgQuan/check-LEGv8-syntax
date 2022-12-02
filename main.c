#include "dataStructure.c"
#include "Readfile.c"
#include "Syntaxcheck.c"
#include <stdio.h>
#include <stdlib.h>



int main()
{
    //get LEGv8 file 
    struct fData* intructionSet = getData();
    printFN(intructionSet);
    printf("---------------------------------------------------------------");

    //remove comment
    removeComment(intructionSet);
    printFN(intructionSet);
    printf("---------------------------------------------------------------");

    //BUG IN HERE!!!
    //get const and label in LEG code
    Node* constSet = getConstansList(intructionSet);
    printFN(intructionSet);
    printf("---------------------------------------------------------------");

    Node* labelSet = getLabelList(intructionSet);
    printFN(intructionSet);
    printf("---------------------------------------------------------------");

    //check each line in text segment
    for(int i = 0; i < intructionSet->nums; i++)
    {
        standardizeIntt(&(intructionSet->data[i]));
        if(lenStr(intructionSet->data[i])==0) continue;
        checkIntruction(intructionSet->data[i], i, constSet, labelSet);
    }
    char* str = "[())";
    
    printf("%d", areBracketsBalanced(str));

}