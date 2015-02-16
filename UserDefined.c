#include <stdlib.h>
#include <stdio.h>
#include "UserDefined.h"

int PrintItem(const void *data)
{
	myData *cast = malloc(sizeof(myData));
	cast = (myData *)data;	
	printf("%d %s\n",cast->number,cast->theString);
	return EXIT_SUCCESS;
}

int FreeItem     (const void *data){
	return EXIT_SUCCESS;
}
int CompareItems (const void *item1_p, const void *item2_p, int key){
	return EXIT_SUCCESS;
}
void * CopyItems (const void *source_p){
	return source_p;
}