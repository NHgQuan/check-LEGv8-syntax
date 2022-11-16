#ifndef __READFILE__
#define __READFILE__

#include<stdlib.h>
#include<stdio.h>
#include "./dataStructure.c"

struct fData* readFile(const char* path)
{

    FILE *file = fopen(path, "r");

    if(file==NULL) return NULL;

    char readExprs[100];
    
    

    int fileLen = 0;
    //reads file as a string line
    while(fgets(readExprs, 100 , file) != NULL) 
    {
        fileLen++;
    }

    fclose(file);
    
    file = fopen(path, "r");
  
    char **data=(char **)malloc(100*sizeof(char)*fileLen);
    //char data[fileLen][100];
    int loop = 0;
    //copy file into a string array
    do
    {
        data[loop]=(char *)malloc(100*sizeof(char));
    }
    while(fgets(data[loop++], 100 , file) != NULL);

   //displaying contents of file 
    printf("[>] Printing File output  : \n");


    fclose(file);

    struct fData* returnData= (struct fData*)malloc(sizeof(struct fData));

    returnData->nums = fileLen;
    returnData->data = data;
    // returnData->nums = fileLen;

    return returnData;
}

struct fData* getData()
{
    //enter file name
    char* filePath;
    printf("Enter file path you want to check: ");
    gets(filePath);
    //read file
    struct fData* file = readFile(filePath);
    return file;
}

#endif

