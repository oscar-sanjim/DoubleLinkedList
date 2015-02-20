#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "UserDefined.h"

int PrintItem(const void *data)
{
	myData *cast = malloc(sizeof(myData));
	cast = (myData *)data;	
	printf("%d %s\n",cast->number,cast->theString);
	return EXIT_SUCCESS;
}

int FreeItem (const void *data){
	myData * cast = (myData *)data;
	free(cast->theString);
	//cast->number = 0;
	free(cast);
	return EXIT_SUCCESS;
}


int CompareItems (const void *item1_p, const void *item2_p, int key){
	
	myData *valor1 = malloc(sizeof(myData));
	valor1 = (myData *)item1_p;

	if((key == INT) || (key == STR))
	{
		myData *valor2 = malloc(sizeof(myData));
		valor2 = (myData *)item2_p;

		if(key == INT)
		{
			if(valor1->number  == valor2->number) return 0;
			else if(valor1->number  <  valor2->number) return 1;
			else if(valor1->number  >  valor2->number) return 2;
		}

		if(key == STR)
		{
			if(strcmp(valor1->theString,valor2->theString) == 0) return 0;
			else return 3;
		}
	}

	if(key == SINGLESTR)
	{
		if(strcmp(valor1->theString,item2_p) == 0) return 0;
		else return 3;
	}

	return -1;
}

void * CopyItems (const void *source_p){
	myData * newNode = malloc(sizeof(myData));
	myData *cast = (myData *)source_p;
	newNode->number = cast->number;
	newNode->theString = malloc(sizeof(cast->theString));
	strcpy(newNode->theString,cast->theString);
	return newNode;
}