#include <stdlib.h>
#include "GenericLists.h"

//*****************************
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
}//Notaa: Preguntar a Abelardo si es necesario un free de cada elemento del struct de lista


int Delete(list_p myList_p, node_p item_p, void **data_h){

}