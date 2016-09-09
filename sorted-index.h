#ifndef SORTED_INDEX_H
#define SORTED_INDEX_H
/*
 * sorted-index.h
 */

#include <stdlib.h>
#define INS_WORD 1
#define INS_FILE 0

//======Prototypes for User-Defined Functions==========
//-=-=-=-You do not need to do anything with these definitions-=-=-=-

/*
 * Your list is used to store data items of an unknown type, which you need to sort.
 * Since the type is opaque to you, you do not know how to directly compare the data.
 *
 * You can presume though that a user will supply your code with a comparator function
 * that knows how to compare the data being sorted, but your code must do the rest
 * of the bookkeeping in a generic manner.
 *
 * The comparator function will take pointers to two data items and will return -1 if the 1st 
 * is smaller, 0 if the two are equal, and 1 if the 2nd is smaller.
 *
 * The user will also supply a destruct function will take a pointer to a single data item
 *	and knows how to deallocate it. If the data item does not require deallocation, the user's
 *  destruct function will do nothing.
 *
 * Note that you are not expected to implement any comparator or destruct functions.
*  Your code will have appropriate comparator function and a destruct functions added to it.
 */

typedef int (*CompareFuncT)( void *, void * );
typedef void (*DestructFuncT)( void * );



//-=-=-=-You must implement all the functions and definitions below-=-=-=-

//=====0: SortedIndex=====================================
//===0.1: List Definition, List Create/Destroy

/*
 * Sorted Index type and list node type that will hold all the data to be sorted.
 */

typedef struct ListNode* ListNodePtr;
struct ListNode
{
    int occurences;
    void *data;
    ListNodePtr next;
    ListNodePtr files;
};

struct SortedIndex
{
    ListNodePtr head;
    CompareFuncT compare;
    DestructFuncT destroy;
};
typedef struct SortedIndex* SortedIndexPtr;


/*
 * SLCreate creates a new, empty, 'SortedIndex'.
 *
 * SLCreate's parameters will be a comparator (cf) and destructor (df) function.
 *   Both the comparator and destructor functions will be defined by the user as per
 *     the prototypes above.
 *   Both functions must be stored in the SortedIndex struct.
 * 
 * SLCreate must return NULL if it does not succeed, and a non-NULL SortedIndexPtr
 *   on success.
 */

SortedIndexPtr SICreate(CompareFuncT cf, DestructFuncT df);


/*
 * SLDestroy destroys a SortedIndex, freeing all dynamically-allocated memory.
 */
void SIDestroy(SortedIndexPtr list);



//===0.2: List Insert

/*
 * SLInsert inserts a given data item 'newObj' into a SortedIndex while maintaining the
 *   order and uniqueness of list items.
 * 
 * SLInsert should return 1 if 'newObj' is not equal to any other items in the list and
 *   was successfully inserted.
 * SLInsert should return 0 if 'newObj' is equal to an item already in the list or it was
 *   not successfully inserted
 *
 * Data item equality should be tested with the user's comparator function *
 */

int SIInsert(SortedIndexPtr list, void *word, void *file);

/*
 * prints list assuming data is of int type
 */

void SIPrintList(SortedIndexPtr list);
void SIPrintFile(FILE * fd, SortedIndexPtr index);
#endif
