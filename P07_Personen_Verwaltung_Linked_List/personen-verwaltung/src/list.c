#include <stdlib.h>
#include <stdio.h>
#include "list.h"

// clear list
void list_clear(node_t *instance);

// insert into list
void list_insert(node_t *instance, person_t person) {
	node_t* last = instance;
	node_t* current = instance->next;

	while(current != NULL) {
		int compare = person_compare(&person, &current->content);
		if(compare == 0) {
			return; // do nothing, person already exists in list
		} else if(compare < 0) {
			break; // exit the while loop and continue
		}
		last = current;
		current = current->next;
	}


    node_t* new_node = malloc(sizeof(node_t)); ///< allocate list on the heap
    if(!new_node) {
        fprintf(stderr, __FILE__ ": malloc failed in list_insert()\n");
        exit(EXIT_FAILURE);
    }

    new_node->content = person;

    if(current == NULL) {
        last->next = new_node;
        new_node->next = NULL;
    } else {
        node_t *old_next = last->next;
        new_node->next = old_next;
        last->next = new_node;
    }
}


// remove from list
void list_remove(node_t *instance, person_t *person);

