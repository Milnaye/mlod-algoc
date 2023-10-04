#include "linkedList.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef char* Element2;

void afficheElement(Element e)
{
	printf("%s ", (Element2) e);
}

void detruireElement(Element e) {}


// compare deux elements
bool equalsElement(Element e1, Element e2){
	return !strcmp((Element2) e1, (Element2) e2);
}