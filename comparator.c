//compare strings record.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sorted-list.h"

int compareString(void* a,void* b)
{
    char *x = (char*)malloc(strlen(a));
    char *y = (char*)malloc(strlen(b));
    int ret = 0; 
    ret = strcmp(x,y);
    
    if(ret > 0)
    {
        return -1;
    }
    else if(ret < 0)
    {
        return 1;
    }
    else if(ret == 0)
    {
        return 0;
    }
    return -2;
}
void destroyInt(void* i)
{
    return;
}

//im not sure if this main function is needed

int main(int argc, char ** argv)
{
    
   const char *test[4];
   test[0] = "a";
   test[1] = "dog";
   test[2] = "boo";
   test[3] = "baa";
   
   int (*compare)(void*,void*) = compareString;
   void (*destroy)(void*) = destroyInt;

   SortedListPtr myList = SLCreate(compare,destroy);

   int i = 0;
   for(i = 0; i<4;i++)
   {
      int check = SLInsert(myList,(void*)(&test[i]));
      printf("check %d: %d\n",i,check);
   }
   printf("compare passed\n");

   SLPrintList(myList);

   SLDestroy(myList);

}
