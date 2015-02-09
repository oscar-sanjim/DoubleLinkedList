/*
 * Copyright (c) 2014 Abelardo Lopez Lagunas
 *
 * File name: GenericLists.h
 *
 * Author:  Abelardo Lopez Lagunas
 *
 * Purpose: Implements doubly linked lists using a generic pointer to the
 *          data structure so it handles arbitrary data structures.
 *
 * References:
 *          Code loosely based on my Generic Singly linked list algorithms
 *
 * Restrictions:
 *          The user must supply those functions that handle the data
 *          on each node.
 *
 * Revision history:
 *
 *          Jan 29 10:43 2014 - Starts from the Singly List Code.
 *
 *          Jan 31 17:03 2014 - Added a user defined deep copy function
 *                              that handles copying data structures with
 *                              allocated memory in them (i.e. strings)
 *
 * Error handling:
 *          If there is not enough memory to create a node or a list
 *          the related functions indicate failure and terminate the
 *          program. If the DEBUG compiler flag is set then more
 *          information is displayed indicating the source of error.
 *
 * Notes:
 *          The code is meant to show how to implement linked lists
 *          using dynamic memory for the Advanced Programming class.
 *
 */

/************************************************************************
 * Data structures for the list node and for the list header            *
 ************************************************************************/

typedef struct node_{
    void         *data_p;       /* Pointer to the user-provided data item */
    struct node_ *next_p;      /* Pointers to the next and previuos items */
    struct node_ *prev_p;
}node;

typedef struct node_ *node_p;     /* Simplify declaration of ptr to node */

struct list_{
    int    numItems;            /* Number of items in the list structure */
    node_p head_p;                /* First and last elements in the list */
    node_p tail_p;
    /*
     * Pointers for the user-defined functions that destroy, print, compare
     * and copy user data elements.
     */
    int  (* destroy)(const void *data_p);
    int    (* print)(const void *data_p);
    int  (* compare)(const void *source_p, const void *dest_p, int key);
    void *  (* copy)(const void *source_p);
}list;

typedef struct list_ *list_p;

/* Used in the SortList and FindInList functions*/
enum order {ERROR = -1, EQUAL = 0, LESS = 1, GREATER = 2, NOTEQUAL = 3};

/************************************************************************
 *                           Macro declarations                         *
 ************************************************************************/
#define ListSize(list) ((list)->numItems)
#define ListHead(list) ((list)->head_p)
#define ListTail(list) ((list)->tail_p)
#define NodeIsHead(list, element) ((element) == (list)->head_p ? 1 : 0)
#define NodeIsTail(list, element) ((element) == (list)->tail_p ? 1 : 0)
#define NodeData(element) ((element)->data_p)
#define NodeNext(element) ((element)->next_p)
#define NodePrev(element) ((element)->prev_p)

/************************************************************************
 *                     Function header declarations                     *
 ************************************************************************/

list_p CreateList    (int (*destroy) (const void *data_p),
                      int (*print)   (const void *data_p),
                      int (*compare) (const void *source_p,
                                      const void *dest_p,
                                        int key),
                      void *  (* copy)(const void *source_p));
int    DestroyList   (list_p myList_p);
int    Delete        (list_p myList_p, node_p item_p, void **data_h);
int    Insert        (list_p myList_p, node_p item_p, const void *data_p);
list_p DuplicateList (list_p sourceList_p);
int    SortList      (list_p myList_p, int key);
int    PrintList     (list_p myList_p);
node_p FindInList    (list_p myList_p, const void *value_p, int key);

