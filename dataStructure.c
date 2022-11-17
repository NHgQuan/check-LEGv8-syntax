#ifndef __DATA_STRUCTURE__
#define __DATA_STRUCTURE__

#include <stdio.h>
#include <stdlib.h>


typedef char inttType;//intructionType

typedef enum { F, T } boolean;

typedef struct fData
{
        int nums;
        char** data;
} fData;

typedef struct Node
{
  char* data;
  struct Node *next;
} Node ;

void appendN(struct Node** head_ref, char* new_data)
{
    /* 1. allocate node */
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
  
    struct Node *last = *head_ref;  /* used in step 5*/
  
    /* 2. put in the data  */
    new_node->data  = new_data;
  
    /* 3. This new node is going to be the last node, so make next of
          it as NULL*/
    new_node->next = NULL;
  
    /* 4. If the Linked List is empty, then make the new node as head */
    if (*head_ref == NULL)
    {
       *head_ref = new_node;
       return;
    }
  
    /* 5. Else traverse till the last node */
    while (last->next != NULL)
        last = last->next;
  
    /* 6. Change the next of last node */
    last->next = new_node;
    return;
}

void clearN(struct Node** head)
{
    while(*head!=NULL) 
    {
        struct Node* temp;
        struct Node* prev;
        temp = *head;
        *head = temp->next;
        free(temp);
    }
}

int lengthN(struct Node** head)
{
    if(*head==NULL) return 0;
    int length = 1;
    struct Node* temp = *head;
    while(temp=temp->next)
    {
        length++;
    }
    return length;
}

// Structure of a stack node
struct sNode {
    char data;
    struct sNode* next;
};
 
 // Function to pushS an item to stack
void pushS(struct sNode** top_ref, int new_data)
{
    // allocate node
    struct sNode* new_node
        = (struct sNode*)malloc(sizeof(struct sNode));
 
    if (new_node == NULL) {
        printf("Stack overflow n");
        getchar();
        exit(0);
    }
 
    // put in the data
    new_node->data = new_data;
 
    // link the old list off the new node
    new_node->next = (*top_ref);
 
    // move the head to point to the new node
    (*top_ref) = new_node;
}
 
// Function to popS an item from stack
int popS(struct sNode** top_ref)
{
    char res;
    struct sNode* top;
 
    // If stack is empty then error
    if (*top_ref == NULL) {
        printf("Stack overflow n");
        getchar();
        exit(0);
    }
    else {
        top = *top_ref;
        res = top->data;
        *top_ref = top->next;
        free(top);
        return res;
    }
}

int lenStr(char* str)
{
    int length =0;
    while(*(str++)!='\0') length++;
    return length;
}

void removeCharStr(char** str, int index)
{
    if(index>lenStr(*str)||index<0) return;
    char* resultStr = (char*)malloc(lenStr(*str));
    int i = 0;
    for(; i < index; i++)
    {
        resultStr[i] = (*str)[i];
    }
    for(; i < lenStr(*str); i++)
    {
        resultStr[i] = (*str)[i+1];
    }
    free(*str);
    *str = resultStr;
}

void standardizeStr(char** a)
{
    int n = lenStr(*a); //take length of string
 
    //remove space in front
    for(int i=0;i<n;i++){
        if((*a)[i]==' '){
            // for(int j=i;j<n-1;j++){
            //     a[j] = a[j+1];
            // }
            // //a[n-1]=NULL;
            // a[n-1]='\0';
            removeCharStr(a, i);
            i--;
            n--;
        }
        else break;
    }
     
 
    //remove space at tail
    for(int i=n-1;i>=0;i--){
        if((*a)[i]==' '){
            //a[i]=NULL;
            removeCharStr(a, i);
            n--;
        }
        else break;
    }
     
    //remove invalid space
    for(int i=1;i<n-1;i++)
    {
        if((*a)[i]==(*a)[i+1]&&(*a)[i+1]==' '){
            removeCharStr(a, i);
            i--;
            n--;
        }
    }
}

char* deepCopyStr(char* str)
{
    char *nStr = (char*)malloc(lenStr(str)+1);
    for(int i=0; i<=lenStr(str); i++)
        {
            nStr[i] = str[i];
        }
    return nStr;

}

int charmem(char* str, int key)
{
    for(int i=0; i<=lenStr(str); i++)
    {
        if((int)str[i] == key) return i;
    }
    return -1;
}

int charNums(char* str, int key)
{
    int numsKey =0;
    for(int i=0; i<=lenStr(str); i++)
    {
        if((int)str[i] == key) numsKey++;
    }
    return numsKey;
}

// boolean compareStr(char* str1, char* str2)
// {
//     int lenStr1 =  lenStr(str1);
//     int i = 0;
//     for(; i < lenStr1; i++)
//     {
//         if(str2[i] == '\0') return F;
//         if(str1[i] != str2[i]) return F;
//     }
//     if(str2[i]=='\0') return T;
//     return F;
// }

boolean compareStr(char* str1, char* str2)
{
    if(str1 == NULL || str2 == NULL) 
    if(str1 == str2) return T;
    else return F;

    while(*str1!='\0' && *str2!='\0')
    {
        if(*(str1++)!=*(str2++)) return F;
    }
    if(*str1=='\0' && *str2=='\0') return T;
    else return F;
}
// Returns 1 if character1 and character2 are matching left
// and right Brackets
boolean isMatchingPair(char character1, char character2)
{
    if (character1 == '(' && character2 == ')')
        return T;
    else if (character1 == '{' && character2 == '}')
        return T;
    else if (character1 == '[' && character2 == ']')
        return T;
    else
        return F;
}
 
// Return 1 if expression has balanced Brackets
boolean areBracketsBalanced(char exp[])
{
    int i = 0;
 
    // Declare an empty character stack
    struct sNode* stack = NULL;
 
    // Traverse the given expression to check matching
    // brackets
    while (exp[i]) {
        // If the exp[i] is a starting bracket then pushS
        // it
        if (exp[i] == '{' || exp[i] == '(' || exp[i] == '[')
            pushS(&stack, exp[i]);
 
        // If exp[i] is an ending bracket then popS from
        // stack and check if the popped bracket is a
        // matching pair*/
        if (exp[i] == '}' || exp[i] == ')'
            || exp[i] == ']') {
 
            // If we see an ending bracket without a pair
            // then return false
            if (stack == NULL)
                return F;
 
            // popS the top element from stack, if it is not
            // a pair bracket of character then there is a
            // mismatch.
            // his happens for expressions like {(})
            else if (!isMatchingPair(popS(&stack), exp[i]))
                return F;
        }
        i++;
    }
 
    // If there is something left in expression then there
    // is a starting bracket without a closing
    // bracket
    if (stack == NULL)
        return T; // balanced
    else
        return F; // not balanced
}

char* takeFirstWord(char* str, const char chr)
{
    //return null if str is empty
    if(str== NULL) return NULL;

    //make clone of str and standardize it
    char* cloneStr = deepCopyStr(str);
    //standardizeIntt(&cloneStr);

    //find length and create first word string
    int nStrLen = 0;
    while(cloneStr[nStrLen]!=chr&&cloneStr[nStrLen]!=0)
    {
        nStrLen++;
    }

    char* nStr = (char*) malloc(sizeof(char)*(nStrLen+1));

    for(int i= 0; i <nStrLen;i++)
    {
        nStr[i] = cloneStr[i];
    }
    nStr[nStrLen]=0;

    free(cloneStr);

    return nStr;
}

void removeFirstWord(char** str, const char chr)
{
    int lengthFirstWord = lenStr(takeFirstWord(*str, chr));
    // check memory leak in here
    for(int i = 0; i < lengthFirstWord; i++)
    {
        removeCharStr(str, 0);
    }
    if(lenStr(*str)) removeCharStr(str, 0);
    //standardizeIntt(str);
}

char* separateFirstWord(char** str, const char chr)
{
    if(*str== NULL) return NULL;
    //string pass have must be standardized
    char* nStr = takeFirstWord(*str, chr);

    removeFirstWord(str, chr);
    
    return nStr;
}

char* separateByBrackets(char** str)
{
    int opIdx = charmem(*str, '('), sizeNStr=charmem(*str, ')')-opIdx+1;
    char* nStr = (char*)malloc(sizeNStr * sizeof(char)+1);
    for(int i=0; i<sizeNStr-2; i++)
    {
        nStr[i]=(*str)[i+opIdx+1];
    }
    nStr[sizeNStr-2] = '\0';
    for(int i=0; i<sizeNStr; i++)
    {
        removeCharStr(str, opIdx);
    }
    return nStr;
}

#endif 

