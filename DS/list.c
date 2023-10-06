// Candaes Corentin

#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


// constructs a new (empty) list
List *list_create(void) {
    List *l = malloc(sizeof(List)); //il a pas cast le stagiaire
    l->first = l->last = NULL;
    return l;
}

// create a new node
ListNode *node_create(data_t data)
{
    ListNode* l = (ListNode*) malloc(sizeof(ListNode));
    l->data = data;
    l->next = NULL;
    l->prev = NULL;
    return l;
}

// counts the items on a list
size_t list_count(const List *list) {
    size_t count = 0;

    ListNode *p=list->first;
    while(p!=NULL) {
        count++;
        p=p->next;
    }

    return count;
}

void print_data(data_t data)
{
    printf("%d ", data);
}

// print data of list from first to last
void list_print(const List *list)
{
    if(list_count(list) == 0)
    {
        return;
    }
    ListNode* current = list->first;
    while (current != NULL)
    {
        print_data(current->data);
        current = current->next;
    }
    printf("\n");
}

// inserts item_data at *end* of a list
void list_addlast(List *list, data_t item_data) {
    if(list_count(list) == 0)
    {
        list->first = node_create(item_data);
        list->last = list->first;
        return;
    }
    // case list is empty

    ListNode* oldLast = list->last;
    ListNode* newLast = node_create(item_data);

    newLast->prev = oldLast;
    oldLast->next = newLast;

    list->last = newLast;
}

void destroyNodeButKeepData(ListNode* node)
{
    free(node);
}

void destroyData(data_t data)
{
    // comme j'ai vu dans du code de chez intel:

    // nothing to see here folks
}

void destroyList(List* list)
{
    ListNode* current = list->first;
    ListNode* next = NULL;

    free(list);
    list = NULL;

    while(current != NULL)
    {
        next = current->next;
        destroyData(current->data);
        destroyNodeButKeepData(current);
        current = next;
    }
}

// removes the item from *end* of the list and returns its value
data_t list_rmlast(List *list) {
    if(list_count(list) == 0)
    {
        return 0;
    }
    if(list_count(list) == 1)
    {
        ListNode* toRemove = list->last;
        data_t valueOfRemoved = toRemove->data;
        destroyNodeButKeepData(toRemove);
        toRemove = NULL;
        list->first = NULL;
        list->last = NULL;
        return valueOfRemoved;
    }

    ListNode* toRemove = list->last;
    ListNode* newLast = list->last->prev;

    list->last = newLast;
    newLast->next = NULL;

    data_t valueOfRemoved = toRemove->data;
    destroyNodeButKeepData(toRemove);
    toRemove = NULL;

    return valueOfRemoved;
}

int main(void) {

    List *l = list_create();

    assert(list_count(l)==0);

    list_addlast(l,10);
    list_addlast(l,20);
    list_addlast(l,30);
    list_addlast(l,40);

    assert(list_count(l)==4);

    list_print(l);

    data_t t =  list_rmlast(l);

    assert(t==40);
    list_print(l);

    destroyList(l);
    l = NULL;

    return 0;
}