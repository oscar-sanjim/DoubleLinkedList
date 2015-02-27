/*
 * Copyright (c) 2014 Abelardo López Lagunas
 *
 * Program: listTest.c
 *
 * Author:  Abelardo López lagunas
 *
 * Purpose: This program tests how the list-management routines work.
 *
 * Usage:
 *          The program reads a text file with the elements that will
 *          be converted into nodes in a linked list. The usage form is:
 *
 *          listTest file.txt
 *
 * References:
 *          Based on my own code for the Generic Linked lists
 *
 * File formats:
 *          The input file should have four numbers per list in ASCII
 *          format.
 *
 * Restrictions:
 *          If the input file is not in ASCII format the program exits
 *
 * Revision history:
 *
 *          Thu Jan 29 17:17 2014 - Created file
 *          Fri Jan 30 15:34 2014 - Added more tests for the insertion
 *                                  and deletion at the head & middle.
 *          Sun Feb 01 14:47 2014 - Separated the user defined functions
 *                                  into their own files.
 *          Tue Feb 03 11:30 2014 - Commented out the Sort and Duplicate
 *                                  list functions that were not in the
 *                                  TC2025 assignment.
 *
 * Error handling:
 *          On any unrecoverable error, the program exits
 *
 * Notes:
 *          This code will be used as a tutorial on pointers and data
 *          structures, in particular linked lists.
 *
 * $Id$
 */

#include <stdio.h>                                    /* Used for printf */
#include <stdlib.h>                      /* Used for malloc, & EXIT codes*/
#include <assert.h>                         /* Used for the assert macro */
#include <string.h>                                       /* For strcmp */
#include "FileIO.h"        /* Used for the file access support functions */
#include "GenericLists.h"      /* Used for all list management functions */
#include "UserDefined.h"                /* All the user defined functions*/


/*************************************************************************
 *                        Global constant values                         *
 ************************************************************************/
#define NUMPARAMS 2


/*************************************************************************
 *                           Main entry point                            *
 *************************************************************************/
int main (int argc, const char * argv[]) {
    
    FILE   *fp;                                    /* Pointer to the file */
//  list_p  theList_p, copyOfList_p;  /* Used to test the list operations */
    list_p  theList_p              ;  /* Used to test the list operations */
    myData *data_p;                   /* The data portion is user defined */
    node_p  aNode;                /* Pointer to a random node in the list */
    char *  aString;           /* Test string for arbitary data insertion */
    
    /* Check if the number of parameters is correct */
    if (argc < NUMPARAMS){
        printf("Need a file with the test data\n");
        printf("Abnormal termination\n");
        exit (EXIT_FAILURE);
    } else {
        fp = fopen (argv[1],"r");        /* Open file for read operation */
        if (!fp) {                                  /* There is an error */
            printf ("The filename: %s does not exist or is corrupted\n",
                    argv[1]);
            printf ("Abnormal termination\n");
            exit (EXIT_FAILURE);                /* Terminate the program */
        } else {
            /* Create the linked list data structure */
            theList_p = CreateList(FreeItem, PrintItem, CompareItems,CopyItems);
            
            while (!feof(fp)){
                
                data_p = (myData *) malloc(sizeof(myData));
                assert (data_p != NULL);   /* Abort if not enough memory */
                
                data_p->number = GetInt(fp);
                data_p->theString = GetString(fp);
                
#ifdef DEBUG
                printf("Integer read is %d:\n", data_p->number);
                printf("String read is %s:\n", data_p->theString);
#endif
                /***** Test insertion at the Tail *****/
                if (Insert(theList_p, NULL, data_p) != EXIT_SUCCESS)
                    printf("Error inserting element %d: %s:\n",
                           data_p->number, data_p->theString);
            }
            
            printf("Original list:\n");
            if (PrintList(theList_p) != EXIT_SUCCESS)
                printf("Error printing the list\n");
            
            /****** Test Insertion at the Head *****/
            data_p = (myData *) malloc(sizeof(myData));
            assert (data_p != NULL);   /* Abort if not enough memory */
            
            data_p->number = 9;
            aString = (char *) malloc((sizeof(char) *
                                      strlen("Gyro Gearloose")) + 1);
            strcpy(aString, "Gyro Gearloose");
            data_p->theString = aString;
            
#ifdef DEBUG
            printf("Integer read is %d:\n", data_p->number);
            printf("String read is %s:\n", data_p->theString);
#endif
            if (Insert(theList_p, ListHead(theList_p), data_p) != EXIT_SUCCESS)
                printf("Error inserting element %d: %s at the Head\n",
                       data_p->number, data_p->theString);
            
            printf("Insertion at the Head:\n");
            if (PrintList(theList_p) != EXIT_SUCCESS)
                printf("Error printing the list\n");
            
            /***** Test insertion in the middle *****/
            data_p = (myData *) malloc(sizeof(myData));
            assert (data_p != NULL);   /* Abort if not enough memory */
            
            data_p->number = 10;
            aString = (char *) malloc((sizeof(char) *
                                       strlen("Launchpad")) + 1);
            strcpy(aString, "Launchpad");
            data_p->theString = aString;
            
            aNode = FindInList(theList_p, "Louie", SINGLESTR);
            if (aNode == NULL){
                printf("Error: failed to find selected node \n");
            }
            
            if (Insert(theList_p, aNode, data_p) != EXIT_SUCCESS)
                printf("Error inserting element %d: %s at the Head\n",
                       data_p->number, data_p->theString);
            
            printf("Search & insertion in the middle:\n");
            if (PrintList(theList_p) != EXIT_SUCCESS)
                printf("Error printing the list\n");
            
//            /***** Duplicate the list *****/
//            copyOfList_p = DuplicateList(theList_p);
//            if (copyOfList_p == NULL)
//                printf("Error copying the list\n");
//            
//            printf("Copy of the list\n");
//            if (PrintList(copyOfList_p) != EXIT_SUCCESS)
//                printf("Error printing the copy of the list\n");
//            
//            /*****  Sort the duplicate of the list *****/
//            printf("Sorting the copy\n");
//            SortList(copyOfList_p, INT);
//            
//            printf("Sorted copy of the list\n");
//            if (PrintList(copyOfList_p) != EXIT_SUCCESS)
//                printf("Error printing the copy of the list\n");
//            
//            /***** Destroy the copy of the list *****/
//            if (DestroyList(copyOfList_p) != EXIT_SUCCESS)
//                printf ("Error deleting the copy of the list\n");
//            else
//                printf("Copy of the list was deleted successfully\n");
            
            /***** Test deletion in the middle *****/
            aNode = FindInList(theList_p, "Donald", SINGLESTR);
            if (aNode == NULL){
                printf("Error: failed to find selected node \n");
            }
            
            printf("El apuntador de data_p es");
            theList_p->print(data_p);
            if (Delete(theList_p, aNode,
                       (void **)&data_p) == 0 && theList_p->destroy!= NULL){
                /* Call the user defined function to deallocate the data */
                printf("El apuntador de data_p despues es");
                theList_p->print(data_p);
                theList_p->destroy(data_p);
            } else
                printf("Error deleting from the middle\n");
            printf("Deletion from middle:\n");
            if (PrintList(theList_p) != EXIT_SUCCESS)
                printf("Error printing the list\n");

            /***** Test deletion at the head *****/
            if (Delete(theList_p, ListHead(theList_p),
                       (void **)&data_p) == 0 && theList_p->destroy!= NULL){
                /* Call the user defined function to deallocate the data */
                theList_p->destroy(data_p);
            } else
                printf("Error deleting from the head\n");
            
            printf("Deletion from hea\n");
            if (PrintList(theList_p) != EXIT_SUCCESS)
                printf("Error printing the list\n");

            /***** Destroy the list *****/
            if (DestroyList(theList_p) != EXIT_SUCCESS)
                printf ("Error deleting the list\n");
            else
                printf("Original list was deleted successfully\n");
        }
        fclose (fp);                        /* Close the input data file */
        return (EXIT_SUCCESS);
    }
}

