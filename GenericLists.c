#include <stdlib.h>
#include "GenericLists.h"
#include <stdio.h>

/******************************/
/**** Oscar Sanchez 1183806 ***/
/**** jacob Rivera  1184125 ***/
/******************************/

//******************************
//**** Definición de Métodos ***
//******************************

list_p CreateList (int (*destroy) (const void *data_p),
                  int (*print)   (const void *data_p),
                  int (*compare) (const void *source_p,
                                      const void *dest_p,
                                        int key),
                      void *  (* copy)(const void *source_p)) {

	/* Alloc meemory for the list */
	list_p newList =(list_p) malloc(sizeof(list));

	/* Set the variables to a default value */
	newList->numItems = 0;
	newList->head_p = NULL;
	newList->tail_p = NULL;

	/* Assign the methods to the list */
	newList->destroy = destroy;
	newList->print = print;
	newList->compare = compare;
	newList->copy = copy;

	return newList;
}

int DestroyList(list_p myList_p){
	if (myList_p == NULL) /* Check if the list is valid */
	{
		return EXIT_FAILURE;
	}
	else{
		node_p temp, last;
		/* Run throught the list, delete the data from each node and then free each node */
		for (temp =(node_p)myList_p->head_p; temp != NULL; temp = temp->next_p)
		{
		 	myList_p->destroy(temp->data_p);
		 	if (temp != myList_p->head_p)
			 	free(last);
		 	last = temp;
		}
		/* Free the structure of the list */
		free(last);
		free(myList_p); 
		return EXIT_SUCCESS;
	}
}


int Delete(list_p myList_p, node_p item_p, void **data_h){
	/* Check if the list is valid */
	if (myList_p == NULL){
		return EXIT_FAILURE;
	}
	else {
		node_p temp;
		/* In case the item is a NULL, delete the head */
		if(item_p == NULL)
		{
			temp = myList_p->head_p;
			*data_h = temp->data_p;
			myList_p->head_p = temp->next_p;
		 	temp->next_p->prev_p = NULL;
		 	free(temp);
			myList_p->numItems--;
		}
		else
		{
			/* Assign the handler to the data of the node that will be deleted */
			*data_h = item_p->data_p;

			/* Run throught the list and find the node that has to be deleted*/
			for (temp = myList_p->head_p; temp != NULL; temp = temp->next_p)
			{
				/* Node found */
				if (myList_p->compare(temp->data_p,item_p->data_p,2) == 0)
			 	{
			 		/*data_h = &item_p->data_p;*/
			 		/* If the node is the head, assign a new head */
			 		if(myList_p->compare(temp->data_p,myList_p->head_p->data_p,2) == 0)
			 		{
			 			myList_p->head_p = temp->next_p;
			 			temp->next_p->prev_p = NULL;
			 		}
			 		else{
			 			/* If the node is the tail, assign a new tail */
			 			if(myList_p->compare(temp->data_p,myList_p->tail_p->data_p,2) == 0)
				 		{
				 			myList_p->tail_p = temp->prev_p;
				 			temp->prev_p->next_p = NULL;
				 		}
				 		/* If the node is in the middle, connect the last and the next */
				 		else
				 		{
				 			temp->prev_p->next_p = temp->next_p;
				 			temp->next_p->prev_p = temp->prev_p;
				 		}
			 		}

			 		/* Free the node and decrement the number of elments*/
			 		free(temp);
			 		myList_p->numItems--;

			 		break;
			 	}
			}
		}
		return EXIT_SUCCESS;
	}
}

int Insert(list_p myList_p, node_p item_p, const void *data_p){
	/* Check that the list is valid */
	if (myList_p == NULL)
	{
		return EXIT_FAILURE;
	}
	else {
		/* Allocate memory for the new node */
		node_p temp = (node_p) malloc(sizeof(node));
		/* Assign the data*/
		temp->data_p = data_p;

		/* If it's the first element of the list */
		if(myList_p->numItems == 0)
		{
			myList_p->head_p = temp;
			temp->prev_p = NULL;
			temp->next_p = NULL;
			myList_p->tail_p = temp;
			myList_p->numItems++;
		}
		else {
			/* Assign at the tail */
			if (item_p == NULL)
			{
				myList_p->tail_p->next_p = temp;
				temp->next_p = NULL;
				temp->prev_p =  myList_p->tail_p;
				myList_p->tail_p = temp;
			}
			else
			{ 
				if(NULL == item_p->prev_p) /*Checking node for head*/
				{
					myList_p->head_p = temp;
				}
				else /* Not the head */
				{
					item_p->prev_p->next_p = temp;
				}
				/* Insert the new node*/
				temp->prev_p = item_p->prev_p;
				temp->next_p = item_p;
				item_p->prev_p = temp;

			}
			myList_p->numItems++;
		}
		return EXIT_SUCCESS;
	}
}

list_p DuplicateList (list_p sourceList_p) {
	
	/* If the list is not empty */
	if(NULL != sourceList_p->head_p)
	{
		/* Create a new list and a comuple of nodes */
		list_p newlist =(list_p) malloc(sizeof(list));
		node_p temp =(node_p)  malloc(sizeof(node));
		node_p iterator;

		/* Copy the data for the first node */
		temp->data_p = sourceList_p->copy(temp->data_p);
		temp->prev_p = NULL;
		newlist->head_p = temp;
		newlist->numItems = 1;
	
		/* Run throught the list, for each node, create a new one and copy the data to the new*/
		for(iterator=sourceList_p->head_p->next_p; iterator!=NULL; iterator=iterator->next_p)
		{
			node_p created =(node_p) malloc(sizeof(node));
			created->data_p = sourceList_p->copy(iterator->data_p);
			
			/* Interlink the new nodes */
			created->prev_p = temp;
			temp->next_p = created;

			temp = created;
			newlist->numItems++;
		}

		/* Assign the tail to the last element */
		temp->next_p = NULL;
		newlist->tail_p = temp;

		return newlist;
	}

	return NULL;
}

int SortList (list_p myList_p, int key){
	return EXIT_SUCCESS;
}

int PrintList(list_p myList_p){
	/* Check that the llist is valid */
	if (myList_p == NULL)
	{
		return EXIT_FAILURE;
	}
	else
	{
		node_p temp;
		/* Run througt the list and call the print method in each element */
		for (temp = myList_p->head_p; temp != NULL; temp = temp->next_p)
		{
			myList_p->print(temp->data_p);
		}
		
		return EXIT_SUCCESS;
	}
}

node_p FindInList (list_p myList_p, const void *value_p, int key){
	node_p temp;
	/* Run through the list, comparing each value */
	for (temp = myList_p->head_p; temp!= NULL; temp = temp->next_p)
	{
		if (myList_p->compare(temp->data_p, value_p, key) == EQUAL)
		{
			return temp;
		}
	}
	return NULL;
}
