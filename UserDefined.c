#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "UserDefined.h"
#include "GenericLists.h"

int PrintItem(const void *data)
{
	/* Create a cast pointer and asign the parameter */
	myData *cast;
	cast = (myData *)data;	
	/* Print the variables */
	printf("%d %s\n",cast->number,cast->theString);
	return EXIT_SUCCESS;
}

int FreeItem (const void *data){
	/* Create a cast pointer and asign the parameter */
	myData * cast;
	cast = (myData *)data;
	/* Free the String and then, the structure*/
	free(cast->theString);
	free(cast);

	return EXIT_SUCCESS;
}


int CompareItems (const void *item1_p, const void *item2_p, int key){
	/* Create a cast pointer and asign the parameter */
	myData *valor1;
	valor1 = (myData *)item1_p;

	if((key == INT) || (key == STR)) /* Comparing two nodes */
	{
		/* Create a cast pointer and asign the second parameter */
		myData *valor2;
		valor2 = (myData *)item2_p;

		/* Compare the nodes by numeric value */
		if(key == INT)
		{
			if(valor1->number  == valor2->number) return EQUAL;
			else if(valor1->number  <  valor2->number) return LESS;
			else if(valor1->number  >  valor2->number) return GREATER;
		}

		/* Compare the nodes by string */
		if(key == STR)
		{
			if(strcmp(valor1->theString,valor2->theString) == 0) return EQUAL;
			else return NOTEQUAL;
		}
	}


	/* Comparing a node and a String */
	if(key == SINGLESTR)
	{
		if(strcmp(valor1->theString,item2_p) == 0) return EQUAL;
		else return NOTEQUAL;
	}
	/* Return an error if the key is wrong */
	return ERROR;
}

void * CopyItems (const void *source_p){
	/* Create a cast pointer and asign the parameter */
	myData * cast = (myData *)source_p;
	
	/* Alloc memory for the new copy of the data */
	myData * newNode = malloc(sizeof(myData));
	/* Asign the number of the old data*/
	newNode->number = cast->number;
	/* Alloc memory for the string of the old data and then copy it*/
	newNode->theString = malloc(sizeof(cast->theString));
	strcpy(newNode->theString,cast->theString);
	
	return newNode;
}