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
    printf("---------------------------------------------------------------\n");

    //remove comment
    removeComment(intructionSet);
    // printFN(intructionSet);
    // printf("---------------------------------------------------------------\n");

    //get const and label in LEG code
    Node* constSet = getConstansList(intructionSet);
    // printFN(intructionSet);
    // printf("---------------------------------------------------------------\n");

    Node* labelSet = getLabelList(intructionSet);
    // printFN(intructionSet);
    // printf("---------------------------------------------------------------\n");

    //check each line in text segment
    for(int i = 0; i < intructionSet->nums; i++)
    {
        if(i==8)
            printf("here\n");
        standardizeIntt(&(intructionSet->data[i]));
        // printf("%s\n", intructionSet->data[i]);
        // printf("---------------------------------------------------------------\n");

        if(lenStr(intructionSet->data[i])==0) continue;
        checkIntruction(intructionSet->data[i], i, constSet, labelSet);
        // printf("done: %d\n", i);
    }

}