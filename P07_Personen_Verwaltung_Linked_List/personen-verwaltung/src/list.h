#ifndef _LIST_H_
#define _LIST_H_

#include "person.h"

typedef struct node {
    person_t content; // in diesem Knoten gespeicherte Person
    struct node *next; // Pointer auf den nächsten Knoten in der Liste
} node_t;

// clear list
void list_clear(node_t *instance);

// insert into list
void list_insert(node_t *instance, person_t person);

// remove from list
void list_remove(node_t *instance, person_t *person);

#endif // _LIST_H_