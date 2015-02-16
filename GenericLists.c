#include <stdlib.h>
#include "GenericLists.h"

//******************************
//**** Definición de Métodos ***
//******************************

list_p CreateList (int (*destroy) (const void *data_p),
                  int (*print)   (const void *data_p),
                  int (*compare) (const void *source_p,
                                      const void *dest_p,
                                        int key),
                      void *  (* copy)(const void *source_p)) {

	list_p newList = malloc(sizeof(list));

	newList->numItems = 0;
	newList->head_p = NULL;
	newList->tail_p = NULL;

	newList->destroy = destroy;
	newList->print = print;
	newList->compare = compare;
	newList->copy = copy;

	return newList;
}

int DestroyList(list_p myList_p){
	node_p temp;
	for (temp = myList_p->head_p; temp->next_p != NULL; temp = temp->next_p)
	{
	 	myList_p->destroy(temp);
	}
	free(myList_p); 
	return EXIT_SUCCESS;
}


int Delete(list_p myList_p, node_p item_p, void **data_h){
	node_p temp;
	for (temp = myList_p->head_p; temp->next_p != NULL; temp = temp->next_p)
	{
	 	if (temp == item_p)
	 	{
	 		data_h = item_p->data_p;

	 		if(temp == myList_p->head_p)
	 		{
	 			myList_p->head_p = temp->next_p;
	 			temp->next_p->prev_p = NULL;
	 		}
	 		else{
	 			if(temp == myList_p->tail_p)
		 		{
		 			myList_p->tail_p = temp->prev_p;
		 			temp->prev_p->next_p = NULL;
		 		}
		 		else
		 		{
		 			temp->prev_p->next_p = temp->next_p;
		 			temp->next_p->prev_p = temp->prev_p;
		 		}
	 		}
	 		myList_p->destroy(temp);
	 		myList_p->numItems--;

	 		break;
	 	}
	}
	return EXIT_SUCCESS;
}

int Insert(list_p myList_p, node_p item_p, const void *data_p){
	
	node_p temp;
	temp->data_p = data_p;

	if(myList_p->numItems == 0)
	{
		myList_p->head_p = temp;
		temp->prev_p = NULL;
		temp->next_p = NULL;
		myList_p->tail_p = temp;
		myList_p->numItems++;
	}
	else {
		if (item_p == NULL)
		{
			myList_p->tail_p->next_p = temp;
			temp->next_p = NULL;
			myList_p->tail_p = temp;
			myList_p->numItems++;
		}
		else
		{
			if(NULL == item_p->prev_p) /*Checking node for head*/
			{
				myList_p->head_p = temp;
			}
			temp->prev_p = item_p->prev_p;
			temp->next_p = item_p;
			item_p->prev_p = temp;
		}
	}
	

}

list_p DuplicateList (list_p sourceList_p) {
	list_p newlist;
	node_p temp, iterator;
	if(NULL != sourceList_p->head_p)
	{
		temp->data_p = sourceList_p->head_p->data_p;
		temp->prev_p = NULL;
		newlist->head_p = temp;
		newlist->numItems = 1;
	

		for(iterator=sourceList_p->head_p->next_p; iterator!=NULL; iterator=iterator->next_p)
		{
			node_p created;
			created->data_p = iterator->data_p;
			created->prev_p = temp;
			temp->next_p = created;

			temp = created;
			newlist->numItems++;
		}

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
	node_p temp;
	for (temp = myList_p->head_p; temp != NULL; temp->next_p)
	{
		myList_p->print(temp->data_p);
	}
	return EXIT_SUCCESS;
}
node_p FindInList (list_p myList_p, const void *value_p, int key){
	
}