/*
 * tokenIndex.c
 * Joseph Suria jrs460
 * Kevin Cochan kjc199 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SIZE 21
#define NAME 50
//char size[9] = {'s','i','z','e','o','f','(',')'};
//char operators[] = {'(',')','[',']','.','-','>','<','*','&','!','~','+','/','%','=','^','|',',','?',':'};
char *allNames[NAME] = {"left parentheses","right parentheses","left bracket","right bracket",
                    "dot operator","minus sign","greater than","less than","indirect sign",
                    "address","negate","1's comp","plus sign","divide sign","modulus",
                    "equals sign","bitwise exclusive or","bitwise or","comma",
                    "condition symbol","true/false symbol","structure pointer","increment",
                    "decrement","shift right","shift left","equals","not equals","logical AND",
                    "logical OR","plus equals","minus equals","multiply equals","divide equals",
                    "modulus equals","shift right equals","shift left equals","AND equals",
                    "XOR equals","less or equal","greater or equal","OR equals",
                    "hexadecimal","Octal","decimal","word","float","BAD TOKEN","sizeof()"};

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */
struct TokenizerT_ {

    int   position;
    int   tkType;
    char *inputString;
};

typedef struct TokenizerT_ TokenizerT;
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

TokenizerT *TKCreate( char * ts ) {
    
    TokenizerT *tk = (TokenizerT*) malloc(sizeof(TokenizerT));

    //Check for malloc fail
    if(tk == 0)
    {
        printf("Malloc Fail\n");
        return NULL;
    }

    tk->inputString = ts;
    tk->position = 0;
    tk->tkType = 0;
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
        tk->tkType = 45;
        return subString(inputStr,start,position-1);
    }

   
 
     //any other character will be recognized as bad token 
     //tk->tkType = 47;
     //tk->position = position+1;
     //return subString(inputStr,start, position);
    
    return NULL;
}

/*
 * main will have a string argument (in argv[1]).
 * The string argument contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int main(int argc, char **argv) {


    FILE* fp;
   
    fp = fopen("file.txt", "r");
    
    int i = 1;
    char* c =(char*) malloc(i);
    char * buffer = (char*)malloc(i);
    *c = fgetc(fp);    
    strcpy(buffer,c); 
    while((*c=fgetc(fp)) != EOF)
    {
        
        if(fp == NULL)
        {
            perror("Error opening file");
            return -1;
        }
    
        buffer = (char*)realloc(buffer,i+1);
        strcat(buffer,c); 
        i++; 
    }
    strcat(buffer,"\0");

    TokenizerT *tk = TKCreate(buffer);
    if(tk == NULL)
    {
        return -1;
    }
    char *token = TKGetNextToken(tk);
   
    
    while(token != NULL) 
    {
        //if bad token, print Hex value. else print token regularly
        if(tk->tkType == 47)
        {
            printf("%s:[0x%x]\n",allNames[tk->tkType],*(token+2));
        }
        else
        {
            printf("%s: %s\n",allNames[tk->tkType],token);
        }
        free(token);
        token = TKGetNextToken(tk);
    } 
    TKDestroy(tk);   
    fclose(fp);
    free(c);
    free(buffer);
    return 0;
}
