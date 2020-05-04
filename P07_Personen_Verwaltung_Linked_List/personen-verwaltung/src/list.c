#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "list.h"

// clear list
void list_clear(node_t* instance) {
    assert(instance);

    node_t* current = instance->next;
    while (current) {
        node_t* tmp = current;
        current = current->next;
        free(tmp);
    }
    if(instance->next != NULL) {
        instance->next = NULL;
	}
}

// insert into list
void list_insert(node_t* instance, person_t person) {
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
        node_t *next = last->next;
        new_node->next = next;
        last->next = new_node;
    }
}


// remove from list
void list_remove(node_t* instance, person_t person) {
    node_t *current = instance;
    node_t *last;

    if (!current->next) {
        return; // if already empty
    }

    last = current;
    current = current->next;

    while (current) {

        if (person_compare(&current->content, &person) == 0)
        {
            // destroy current and remove
            if (current->next) {
                last->next = current->next;
            }
            else {
                last->next = NULL;
            }
            free(current);
            return;
        }
        else {
            last = current;
            current = current->next;
        }
    }
}

