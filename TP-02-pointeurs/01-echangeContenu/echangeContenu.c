#include "echangeContenu.h"

void echangeContenu(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}