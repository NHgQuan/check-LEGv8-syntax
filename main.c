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


    // preload intruction type data file
    // this file have key word and immediate condition
    //FDataNode is a list of fData with each node contain data of each intructionType file
    // can use list to store this if have time
    fDataNode *inttTypeList = NULL;
    
    fData* inttTypePath = readFile("D:/Workspace/C/checkLEGv8/LEGv8Data/intructionType/path.txt");

    if(inttTypePath == NULL) 
    {
        printf("(x) Couldn't open path.txt");
        return 0;
    }

    for(int i = 0; i <inttTypePath->nums; i++)
    {
        char* path =inttTypePath->data[i];
        appendFdN(&inttTypeList, readFile(path));
    }
    free(inttTypePath);


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
        if(i==16)
            printf("here\n");
        standardizeIntt(&(intructionSet->data[i]));
        // printf("%s\n", intructionSet->data[i]);
        // printf("---------------------------------------------------------------\n");

        if(lenStr(intructionSet->data[i])==0) continue;
        checkIntruction(intructionSet->data[i], i, constSet, labelSet, inttTypeList);
        // printf("done: %d\n", i);
    }

}