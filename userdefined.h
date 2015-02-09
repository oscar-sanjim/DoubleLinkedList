/*
 * Copyright (c) 2014 Abelardo Lopez Lagunas
 *
 * File name: UserDefined.h
 *
 * Author:  Abelardo Lopez Lagunas
 *
 * Purpose: Implements all the user defined functions for handling the
 *          specific user data structure that is pointed to by the doubly
 *          linked list node.
 *
 * References:
 *          Code loosely based on my Generic Singly linked list algorithms
 *
 * Restrictions:
 *          Must use the doubly linked lists code
 *
 * Revision history:
 *
 *          Feb 01 14:41 2014 - File created
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

/*************************************************************************
 *                       User defined structures                         *
 ************************************************************************/
typedef struct myData_{
    int    number;
    char * theString;
}myData;

enum theKey {INT = 1, STR, SINGLESTR};

/*************************************************************************
 *                       User defined print function                     *
 ************************************************************************/
int PrintItem    (const void *data);
int FreeItem     (const void *data);
int CompareItems (const void *item1_p, const void *item2_p, int key);
void * CopyItems (const void *source_p);
