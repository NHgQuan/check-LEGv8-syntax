#ifndef __SYNTAXCHECK__
#define __SYNTAXCHECK__

#include<stdlib.h>
#include<stdio.h>
#include "dataStructure.c"
#include "Readfile.c"

inttType intructionType(struct Node *intruction)
{
    struct fData* intructionSet = readFile("./intructionType/i.txt");
    for(int i = 0; i < intructionSet->nums; i++)
    {
        if(compareStr(intruction->data, intructionSet->data[i])) return 'i';
    }

    intructionSet = readFile("./intructionType/r.txt");
    for(int i = 0; i < intructionSet->nums; i++)
    {
        if(compareStr(intruction->data, intructionSet->data[i])) return 'r';
    }

    intructionSet = readFile("./intructionType/j.txt");
    for(int i = 0; i < intructionSet->nums; i++)
    {
        if(compareStr(intruction->data, intructionSet->data[i])) return 'j';
    }

    //if intructionType is not belong to any contruction type
    return 0;
}

boolean isRegister(char* parameter)
{
    if(parameter[0] != '$') return F;
    
    //if(parameter[1] == '')
    return F;
}

boolean isImediate(char* parameter)
{
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
    struct Node* intructionComponents = separateIntruction(intruction);
    if(!intructionComponents) return ;
    char type = intructionType(intructionComponents);
    if(type == 0 ) printf("undefined intruction %s", intructionComponents->data);
    if(type == 'r') checkrType(intructionComponents);
    if(type == 'i') checkiType(intructionComponents);
    if(type == 'j') checkjType(intructionComponents);
}

#endif
