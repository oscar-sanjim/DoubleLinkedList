#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "UserDefined.h"
#include "GenericLists.h"

int PrintItem(const void *data)
{
	myData *cast;
	cast = (myData *)data;	
	printf("%d %s\n",cast->number,cast->theString);
	return EXIT_SUCCESS;
}

int FreeItem (const void *data){
	myData * cast;
	cast = (myData *)data;
	free(cast->theString);
	//cast->number = 0;
	free(cast);
	return EXIT_SUCCESS;
}


int CompareItems (const void *item1_p, const void *item2_p, int key){
	
	myData *valor1;
	valor1 = (myData *)item1_p;

	if((key == INT) || (key == STR))
	{
		myData *valor2;
		valor2 = (myData *)item2_p;

		if(key == INT)
		{
			if(valor1->number  == valor2->number) return EQUAL;
			else if(valor1->number  <  valor2->number) return LESS;
			else if(valor1->number  >  valor2->number) return GREATER;
		}

		if(key == STR)
		{
			if(strcmp(valor1->theString,valor2->theString) == 0) return EQUAL;
			else return NOTEQUAL;
		}
	}



	if(key == SINGLESTR)
	{
		if(strcmp(valor1->theString,item2_p) == 0) return EQUAL;
		else return NOTEQUAL;
	}

	return ERROR;
}

void * CopyItems (const void *source_p){
	myData * newNode = malloc(sizeof(myData));
	myData * cast = (myData *)source_p;
	newNode->number = cast->number;
	newNode->theString = malloc(sizeof(cast->theString));
	strcpy(newNode->theString,cast->theString);
	return newNode;
}