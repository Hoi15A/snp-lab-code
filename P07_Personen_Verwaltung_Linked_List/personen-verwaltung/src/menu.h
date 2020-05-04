#ifndef _MENU_H_
#define _MENU_H_


#include "list.h"
#include "person.h"

void menu(node_t *people);

void insert(node_t *people);

void show(node_t *people);

void menu_remove(node_t *people);

void clear(node_t *people);

#endif