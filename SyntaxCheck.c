#ifndef __SYNTAXCHECK__
#define __SYNTAXCHECK__

#include<stdlib.h>
#include<stdio.h>
#include "dataStructure.c"
#include "Readfile.c"
#include "math.c"
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

void isRegister(char* parameter)
{
    struct fData* registersSet = readFile("./LEGv8Data/registersSet/registersSet.txt");
    for(int i = 0; i < registersSet->nums; i++)
    {
        if(compareStr(parameter, registersSet->data[i])) return;
    }
    printf("error: invalid parameter \'%s\'", parameter);
}

int* getImmBound(char* condition)
{
    /// @brief this function return upper bound and lower bound of immediate condition
    /// @param condition have format u_number or s_number, u is unsign and s is sign
    /// @return an two element array of upper bound and lower bound

    int* bound = (int*)malloc(sizeof(int)*2);
    if(condition[0]=='u')
    {
        bound[0] = 0;
        removeCharStr(&condition, 0);
        bound[1] = expo(2, toInt(condition)) - 1;
    }
    if(condition[0]=='s')
    {
        bound[0] =  -   (expo(2, toInt(condition) - 1 ));
        removeCharStr(&condition, 0);
        bound[1] =      expo(2, toInt(condition) - 1 );
    }
    return bound;
}

void isImediate(char* parameter, char** inttTypeLine)
{
    /// @brief this function check immediate of intruction
    //  immediate type:     u12 s19 u16 u6  s26 LSL
    /// @param parameter 
    /// @param inttTypeLine 
    if(!isNumberStr(parameter)) printf("error: parameter need to be a number");
    int* bound = getImmBound(separateFirstWord(inttTypeLine, ' '));

    int imm = toInt(parameter);
    if(!(imm>=bound[0]&&imm<=bound[1])) printf("error: out of range: %s",parameter);
    return;
}

boolean parametersIsEnough(struct Node* node, int numPara)
{
        if(lengthN(&node)==numPara) return T;
        else return F;

}

void check2r1i(struct Node* node, char** inttTypeLine)
{
    parametersIsEnough(node, 3);

    //check first parameter
    isRegister(node->data);

    //check second parameter
    node=node->next;
    isRegister(node->data);

    //check third parameter
    node=node->next;
    isImediate(node->data, inttTypeLine);
}

boolean haveBrackets(char* str)
{
    for(int i=0; i<lenStr(str); i++)
    {
        if(str[i]=='[') return T;
    }
    return F;
}

boolean aprociateBrackets(char* paraCluster)
{
    // if necessary, check paraCluster must have only one bracket pair
    if(!areBracketsBalanced(paraCluster)) return F; 
    //if(paraCluster[0] !='(') return F;
    if(charNums(paraCluster, '[') != 1 || charNums(paraCluster, ']') != 1) return F;
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
    
    if(haveBrackets(intruction)) 
    if(aprociateBrackets(intruction))
    {
        removeCharStr(&intruction, charmem(intruction, '['));
        removeCharStr(&intruction, charmem(intruction, ']'));
    }
    else 
    {
        printf("Brackets in intruction is invalid");
        return NULL;
    }
    
    struct Node* head = NULL;
    if(intruction)
    {
        appendN(&head, separateFirstWord(&intruction, ' '));
    }
    while(*intruction)
    {
        char* simpleElement = separateFirstWord(&intruction, ',');
        appendN(&head, simpleElement);
    }
    return head;
}

void checkParameter(struct Node* parameter, char** inttTypeLine, int id)
{
    if(id == 1)  check2r1i(parameter, inttTypeLine);
    if(id == 2)  check2r1i(parameter, inttTypeLine);
    if(id == 3)  check2r1i(parameter, inttTypeLine);
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
    
    fData* inttTypePath = readFile("./LEGv8Data/intructionType/path.txt");

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
                char* iTLClone = deepCopyStr(inttTypeLine);
                separateFirstWord(&iTLClone, ' ');   //remove key word, keep only imm condition
                checkParameter(intructionComponents->next, &iTLClone, i);
            }
    }
    if(inttTypeLine == NULL)  printf("undefined intruction %s", intructionComponents->data);
    
}

#endif
