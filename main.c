#include "module/dataStructure.h"
#include "module/Readfile.h"
#include "module/Syntaxcheck.h"
#include <stdio.h>
#include <stdlib.h>



int main()
{
    //get LEGv8 file 
    struct fData* intructionSet = getData();

    //you can uncomment this to see LEGv8 file
    // //print LEGv8 file
    // printFN(intructionSet);
    // printf("---------------------------------------------------------------\n");


    // load intruction type folder
    // this file have key word and immediate condition
    //FDataNode is a list of fData with each node contain data of each intructionType file
    fDataNode *inttTypeList = readIntructionTypeFolder("D:/Workspace/C/checkLEGv8/LEGv8Data/intructionType/path.txt");


    //remove comment
    removeComment(intructionSet);

    //get const and label in LEG code
    Node* constSet = getConstansList(intructionSet);
    Node* labelSet = getLabelList(intructionSet);

    //check each line in text segment
    for(int i = 0; i < intructionSet->nums; i++)
    {
        if(lenStr(intructionSet->data[i])==0) continue;//skip empty line
        checkIntruction(intructionSet->data[i], i, constSet, labelSet, inttTypeList);
    }

    clearFData(&intructionSet);
    clearFdN(&inttTypeList);
    clearN(&constSet);
    clearN(&labelSet);


}