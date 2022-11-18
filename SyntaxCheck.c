#ifndef __SYNTAXCHECK__
#define __SYNTAXCHECK__

#include<stdlib.h>
#include<stdio.h>
#include "dataStructure.c"
#include "Readfile.c"

char* intructionType(struct Node *intruction, fDataNode* inttTypeSet)
{
    //haven't deallocated yet
    for(int i =0; i<inttTypeSet->data->nums; i++) 
    {
        if(compareStr(intruction->data, inttTypeSet->data->data[i])) 
        {
            char* inttTypeLine = inttTypeSet->data->data[i];
            return inttTypeLine;
        }
    }
    //if intructionType is not belong to any contruction type
    return NULL;
}

boolean isRegister(char* parameter)
{
    struct fData* registersSet = readFile("./LEGv8Data/registersSet/registersSet.txt");
    for(int i = 0; i < registersSet->nums; i++)
    {
        if(compareStr(parameter, registersSet->data[i])) return T;
    }
    return F;
}

boolean isImediate(char* parameter)
{
    if(isNumberStr(parameter)) return T;
    return F;
}

boolean isTargetAddress(char* parameter)
{
    return F;
}

boolean parametersIsEnough(struct Node* node, char typeIntruction)
{
    if(typeIntruction=='r')
        if(lengthN(&node)==4) return T;
        else return F;
    if(typeIntruction=='i')
        if(lengthN(&node)==3) return T;
        else return F;
    if(typeIntruction=='j')
        if(lengthN(&node)==2) return T;
        else return F;
    return F;
}

void check2r1i(struct Node* node)
{
    
}

void checkrType(struct Node* node)
{
    //check num parameter
    if(!parametersIsEnough(node, 'r')) printf("error: too few arguments to intruction \' %s\'", node->data);
    
    //check first parameter
    node=node->next;
    if(!isRegister(node->data)) printf("error: invalid parameter \'%s\'", node->data);

    //check second parameter
    node=node->next;
    if(!isRegister(node->data)) printf("error: invalid parameter \'%s\'", node->data);

    //check third parameter
    node=node->next;
    if(!isRegister(node->data)) printf("error: invalid parameter \'%s\'", node->data);

}

void checkiType(struct Node* node)
{
    //check num parameter
    if(!parametersIsEnough(node, 'i')) printf("error: too few arguments to intruction \' %s\'", node->data);
    
    //check first parameter
    node=node->next;
    if(!isRegister(node->data)) printf("error: invalid parameter \'%s\'", node->data);

    //check second parameter
    node=node->next;
    if(!isRegister(node->data)) printf("error: invalid parameter \'%s\'", node->data);

    //check third parameter
    node=node->next;
    if(!isImediate(node->data)) printf("error: invalid parameter \'%s\'", node->data);

}

void checkjType(struct Node* node)
{
    //check num parameter
    if(!parametersIsEnough(node, 'j')) printf("error: too few arguments to intruction \' %s\'", node->data);
    
    //check first parameter
    node=node->next;
    if(!isTargetAddress(node->data)) printf("error: invalid parameter \'%s\'", node->data);

}

boolean haveBrackets(char* str)
{
    for(int i=0; i<lenStr(str); i++)
    {
        if(str[i]=='(') return T;
    }
    return F;
}

boolean aprociateBrackets(char* paraCluster)
{
    // if necessary, check paraCluster must have only one bracket pair
    if(!areBracketsBalanced(paraCluster)) return F; 
    //if(paraCluster[0] !='(') return F;
    if(charNums(paraCluster, '(') != 1 || charNums(paraCluster, ')') != 1) return F;
    if(*paraCluster) return T;
    return F;
}

void standardizeIntt(char** intruction)
{
    standardizeStr(intruction);
    int length = lenStr(*intruction), spaceIdx = charmem(*intruction, ' ');
    if(spaceIdx!=-1)
        for(int i=spaceIdx+2; i<length; i++)
            {
                if((*intruction)[i]==' ')
                {
                    removeCharStr(intruction, i);
                    length--;
                }
            }
}

struct Node* separateIntruction(char* intruction)
{
    standardizeIntt(&intruction);
    struct Node* head = NULL;
    if(intruction)
    {
        appendN(&head, separateFirstWord(&intruction, ' '));
    }
    while(*intruction)
    {
        char* simpleElement = separateFirstWord(&intruction, ',');
        if(haveBrackets(simpleElement)) 
            if(aprociateBrackets(simpleElement))
                appendN(&head, separateByBrackets(&simpleElement));
            else 
            {
                clearN(&head);
                printf("Brackets in intruction is invalid");
                return NULL;
            }
        appendN(&head, simpleElement);
    }
    return head;
}

void checkIntruction(char* intruction, const int index)
{
    /// @brief  this function will check type of intruction then check parameter of it
    /// @param intruction is anyline of LEGv8 file
    /// @param index is line index in file of intruction

    // preload intruction type data file
    // this file have key word and immediate condition
    // can use list to store this if have time
    fDataNode *inttTypeList = NULL;
    
    fData* inttTypePath = readFile("./LEGv8Data/intructionType/path.txt")

    for(int i = 0; i <inttTypePath->nums; i++)
    {
        appendFdN(&inttTypeList, readFile(inttTypePath->data[i]));
    }
    free(inttTypePath);

    // separate intruction to smaller elements
    struct Node* intructionComponents = separateIntruction(intruction);
    if(!intructionComponents) return ;

    //create new variable to store line of this intruction in type file
    char* inttTypeLine = NULL;
    fDataNode* tempiTL = inttTypeList;
    for(int i =0; i<lengthFdN(&inttTypeList); i++)
    {
        inttTypeLine = intructionType(intructionComponents, tempiTL);
        if(inttTypeLine != NULL)
            {
                if(i == 1)  check2r1i(intructionComponents);
                if(i == 2)  checkii(intructionComponents);
                if(i == 3)  checkjType(intructionComponents);
            }
    }
    if(inttTypeLine == NULL)  printf("undefined intruction %s", intructionComponents->data);
    
}

#endif
