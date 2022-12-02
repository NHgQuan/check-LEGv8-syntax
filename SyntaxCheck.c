#ifndef __SYNTAXCHECK__
#define __SYNTAXCHECK__
#include<stdlib.h>
#include<stdio.h>
#include "dataStructure.c"
#include "Readfile.c"
#include "math.c"

static int textSegment = 0;
static int dataSegment = 0;

int removeCommentAt(fData* intructionSet, int at)
{
    int index = strstr(intructionSet->data[at], "/*");
    for(int i = at; i < intructionSet->nums; i++)
    {
        int endIndex = strstr(intructionSet->data[i], "*/");
        if(endIndex== -1)
            while(lenStr(intructionSet->data[i])!=index)
                removeCharStr(&(intructionSet->data[i]), index);
        if(endIndex!= -1)
            {
                for(int j=index; j<endIndex+2; j++)
                {
                    removeCharStr(&(intructionSet->data[i]), index);
                }
                return i;
            }
        index =0;
    }
    return -1;
}

void removeComment(fData* intructionSet)
{
    for(int i =0; i< intructionSet->nums; i++)
    {
        int index = strstr(intructionSet->data[i], "//");
        if(index!= -1)
        {
            while(lenStr(intructionSet->data[i])!=index)
                removeCharStr(&(intructionSet->data[i]), index);
        }

        index = strstr(intructionSet->data[i], "/*");
        if(index!= -1)
            {
                i = removeCommentAt(intructionSet, i);
                if(i==-1)
                    printf("error:comment unclose at the end of file/n");
            }
    }
}

void changeSegmentFlag(char* intructionLine)
{
    if(compareStr(intructionLine, ".data")) 
    {
        dataSegment = 1;
        textSegment =0;
    }
    if(compareStr(intructionLine, ".test")) 
    {
        dataSegment = 0;
        textSegment = 1;
    }
}

void rechangeSegmentFlag()
{
    textSegment = 0;
    dataSegment = 0;
}

char* intructionType(struct Node *intruction, fDataNode* inttTypeSet)
{
    //haven't deallocated yet
    for(int i =1; i<inttTypeSet->data->nums; i++) 
    {
        if(compareStr(intruction->data, takeFirstWord(inttTypeSet->data->data[i], ' '))) 
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
    struct fData* registersSet = readFile("D:/Workspace/C/checkLEGv8/LEGv8Data/registersSet/registersSet.txt");
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

void isImediate(char* parameter, char** inttTypeLine, Node* constSet, Node* labelSet)
{
    /// @brief this function check immediate of intruction
    //  immediate type:     u12 s19 u16 u6  s26 LSL
    /// @param parameter 
    /// @param inttTypeLine 
    if(isNumberStr(parameter))
    {
        int* bound = getImmBound(separateFirstWord(inttTypeLine, ' '));

        int imm = toInt(parameter);
        if(!(imm>=bound[0]&&imm<=bound[1])) printf("error: out of range: %s",parameter);
    }
    else
    {
        boolean isConstant = F;
        while(constSet)
        {
            if(compareStr(parameter, constSet->data))
            {
                isConstant = T;
                break;
            }
            constSet = constSet->next;
        }
        boolean isLabel = F;
        while(labelSet&&!isConstant)
        {
            if(compareStr(parameter, labelSet->data))
            {
                isLabel = T;
                break;
            }
            labelSet = labelSet->next;
        }
        if(!(isLabel||isConstant))
            printf("error: invalid value\n");
    }
}

boolean parametersIsEnough(struct Node* node, int numPara)
{
        if(lengthN(&node)==numPara) return T;
        else return F;
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

boolean isLabel(char* intructionParameter)
{
    /// @brief 
    /// @param intructionParameter 
    /// @return T if the parameter have last char is ':'
    if(backStr(intructionParameter)==':') return T;
    return F;
}
struct Node* getLabelList(fData* intructionSet)
{
    /// @brief this function traverse all node of intructionSet 
    /// then remove all lines have label identifiers and return the list of label in intructionSet
    /// @param intructionSet list of intruction in LEG code
    /// @return list of label in intructionSet
    struct Node* LabelList = NULL;
    for(int i =0 ; i< intructionSet->nums; i++)
    {
        if(isLabel(takeFirstWord((intructionSet->data[i]), ' '))) 
        {
            char* label = deepCopyStr(separateFirstWord(&(intructionSet->data[i]), ' '));
            removeCharStr(&label, lenStr(label)-1);
            appendN(&LabelList, label);
        }
    }
    return LabelList;
}

struct Node* getConstansList(fData* intructionSet)
{
    /// @brief this function traverse all node of intructionSet 
    /// then remove all lines have const identifiers and return the list of label in intructionSet
    /// if const identifier is in data segment or text segment, print error message
    /// @param intructionSet list of intruction in LEG code
    /// @return list of label in intructionSet
    struct Node* constList = NULL;
    for(int i = 0; i < intructionSet->nums; i++)
    {
        // set flag
        changeSegmentFlag(intructionSet->data[i]);

        if(compareStr(takeFirstWord((intructionSet->data[i]), ' '), ".eqv"))
            {
                //take const name to const list
                removeFirstWord(&(intructionSet->data[i]), ' ');
                appendN(&constList, separateFirstWord(&(intructionSet->data[i]), ' '));

                //if line is still have data, print error
                if(lenStr(intructionSet->data[i]))
                    {
                        while(lenStr(intructionSet->data[i]))
                        {
                            removeFirstWord(&(intructionSet->data[i]), 'z');
                        }
                        printf("error: invalid identifier");
                    }

                //if const identifier is in data or text segment, print error
                if(dataSegment||textSegment)
                    printf("error: constant identifier cannot be here");
            }
    }

    //set flag to initial value
    rechangeSegmentFlag();
}

void checkParameter(struct Node* parameter, char** inttTypeLine, char* numRe, char* numIm, Node* constSet, Node* labelSet)
{
    parametersIsEnough(parameter, 3);
    if(compareStr(numIm, "i"))
    {
        //this in data segment
        //check flag
        if(dataSegment==0) printf("ERROR: this must be in data segment\n");
    }else
    {
        if(textSegment==0) printf("ERROR: this must be in text segment\n");
        
        //check Re
        int numRe_int = toInt(numRe);
        for(int i = 0; i < numRe_int; i++)
        {
            isRegister(parameter->data);
            parameter = parameter->next;
        }

        //check Im
        int numIm_int = toInt(numIm);
        for(int i = 0; i < numIm_int; i++)
        {
            isImediate(parameter->data, inttTypeLine, constSet, labelSet);
            parameter = parameter->next;
    }
    }
    
}

void checkIntruction(char* intruction, const int index, Node* constSet, Node* labelSet)
{
    /// @brief  this function will check type of intruction then check parameter of it
    /// @param intruction is anyline of LEGv8 file
    /// @param index is line index in file of intruction
    if(*intruction='\0') return;
    // preload intruction type data file
    // this file have key word and immediate condition
    //FDataNode is a list of fData with each node contain data of each intructionType file
    // can use list to store this if have time
    fDataNode *inttTypeList = NULL;
    
    fData* inttTypePath = readFile("D:/Workspace/C/checkLEGv8/LEGv8Data/intructionType/path.txt");

    if(inttTypePath == NULL) 
    {
        printf("error: Couldn't open path.txt");
        return;
    }

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
    fDataNode* tempITL = inttTypeList;
    for(int i =0; i<lengthFdN(&inttTypeList); i++)
    {
        //take num Re and IM
        char* numRe, *numIm;
        char* inforPara = tempITL->data->data[0];
        numRe = separateFirstWord(&inforPara, ' ');
        numIm = separateFirstWord(&inforPara, ' ');

        changeSegmentFlag(intructionComponents->data);
        // i is id of each intructionType file
        inttTypeLine = intructionType(intructionComponents, tempITL);
        if(inttTypeLine != NULL)
            {
                char* iTLClone = deepCopyStr(inttTypeLine);
                //memory leak
                separateFirstWord(&iTLClone, ' ');   //remove key word, keep only imm condition
                // remember fix 1 to i
                checkParameter(intructionComponents->next, &iTLClone, numRe, numIm, constSet, labelSet);
                break;
            }
        
        if(inttTypeLine == NULL)
            tempITL= tempITL->next;
    }
    if(inttTypeLine == NULL)  printf("undefined intruction %s", intructionComponents->data);
    
}


#endif
