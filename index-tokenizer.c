/*
 * tokenIndex.c
 * Joseph Suria jrs460
 * Kevin Cochan kjc199 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "index-tokenizer.h"

/*
 *subString creates a new string from start to end and returns it as pointer.
 */
char *subString(char *str, int start, int end){

    char *returnStr = (char*)calloc(strlen(str)+1,sizeof(char));
    if(returnStr == 0)
    {
        printf("Calloc fail\n");
        return NULL;
    }
    int i = 0;
    int j = start;
    for(i = 0; i<=(end-start); i++)
    {
        *(returnStr+i) = *(str+j);
        j++;
    }
    return returnStr;
}


/*
 * TKCreate creates a new TokenizerT object for a given token stream
 * (given as a string).
 * 
 * TKCreate should copy the arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate( FILE * fd ) {
    
    TokenizerT *tk = (TokenizerT*) malloc(sizeof(TokenizerT));

    //Check for malloc fail
    if(tk == 0)
    {
        printf("Malloc Fail\n");
        return NULL;
    }

    tk->position = 0;
    int i = 1;
    char *c = (char*) malloc(i);
    char * buffer = (char*)malloc(i);
    *c = fgetc(fd);
    strcpy(buffer,c);
    while((*c=fgetc(fd)) != EOF){
        i++; 
        buffer = (char*)realloc(buffer,i);
        strcat(buffer,c);    
    } 
    buffer = (char*)realloc(buffer,i+1);
    strcat(buffer,"\0");
    tk->inputString = buffer;
    free(c);
    return tk;
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy( TokenizerT * tk ) {

    if(tk != NULL)
    {
        free(tk);
    }
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken( TokenizerT * tk ) {

    char *inputStr = tk->inputString;
    int start = tk->position;
    int position = tk->position;
    if(*(inputStr+position) == '\0')
    {
        return NULL;
    }

    //Skip whitespace characters, they still act as delimiters for tokens
    while(isspace(*(inputStr+position)) != 0 || *(inputStr+position) == '\\') 
    {
        if(*(inputStr+position) == '\\')
        {
           if(*(inputStr+position+1) == 't'|| *(inputStr+position+1) == 'r'||
               *(inputStr+position+1) == 'f'|| *(inputStr+position+1) == 'v'||   
               *(inputStr+position+1) == 'n')
           {
               start++;
               position++;
           }
        }
        start++;
        position = start;
    }
  
    while(!isalpha(*(inputStr+start)) && *(inputStr+start) != '\0')
    {
        start++;
        position++;
    }
    if(*(inputStr+position) == '\0')
    {
        return NULL;
    }

    //check if first character is letter 
    if(isalpha(*(inputStr+start)))
    {
        while(*(inputStr+position))
        {
            if(isalpha(*(inputStr+position)))
            {
               inputStr[position] =(char) tolower(*(inputStr+position));
            }
            
            //any letter or number will create word token
            if(isalnum(*(inputStr+position)))
            {
                position++;
            }
            else
            {
                break;
            }
        }

        tk->position = position;
        return subString(inputStr,start,position-1);
    }
    return NULL;
}
