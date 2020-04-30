/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zuercher Hochschule Winterthur             -
 * --  _| |_| | | | |____ ____) |  (University of Applied Sciences)           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ----------------------------------------------------------------------------
 */
/**
 * @file
 * @brief Lab implementation
 */
#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "person.h"

/**
 * @brief Main entry point.
 * @param[in] argc  The size of the argv array.
 * @param[in] argv  The command line arguments...
 * @returns Returns EXIT_SUCCESS (=0) on success, EXIT_FAILURE (=1) there is an expression syntax error.
 */
int main(int argc, char* argv[])
{
	// BEGIN-STUDENTS-TO-ADD-CODE
    node_t people;
    menu(&people);
	// END-STUDENTS-TO-ADD-CODE
    return EXIT_SUCCESS;
}

void menu(node_t* people) {
    printf("Welcome to People Management - Linked List");
    char in;

    do {
        printf("I(nsert), R(emove), S(how), C(lear), E(nd):\n>");
        scanf(" %c", &in);
        switch (tolower(in)) {
        case 'i':
            insert(people);
            break;
        case 'r':
            remove(people);
            break;
        case 's':
            show(people);
            break;
        case 'c':
            clear(people);
            break;
        case 'e':
            return;
        default:
            printf("not a valid command");
            break;
        }
    } while (in != EOF && in != 'e');
}

static person_t read_person(void) {
    char last_name[NAME_LEN];
    char first_name[NAME_LEN];
    int age = 0;
    size_t last_name_len = 0, first_name_len = 0;
    person_t person;
    printf("Enter last name:  ");

    // last name
    do {
        if (last_name_len == -1) {
            printf("Warning: Please enter a name that's between 1 and 20 chars: ");
        }

        scanf("%s", last_name);
        last_name_len = strlen(last_name);

        if (!(last_name_len > 0 && last_name_len < NAME_LEN)) {
            last_name_len = -1;
        }
    } while (last_name_len == -1);

    printf("Enter first name:  ");
     
    // first name
    do {
        if (first_name_len == -1) {
            printf("Warning: Please enter a first name that's between 1 and 20 chars: ");
        }

        scanf("%s", first_name);
        first_name_len = strlen(first_name);

        if (!(first_name_len > 0 && first_name_len < NAME_LEN)) {
            first_name_len = -1;
        }
    } while (first_name_len == -1);

    printf("Enter age:  ");

    // age
    do {
        if (age == -1) {
            printf("Warning: Please enter a valid age: ");
        }
        scanf("%d", &age);

        if (age < 0 || age > 130) {
            age = -1;
        }
    } while (age == -1);
    last_name_len = strlen(last_name);

    // strncpy null terminators
    last_name_len += 1;
    first_name_len += 1;
    (void)strncpy(person.name, last_name, last_name_len);
    (void)strncpy(person.first_name, first_name, first_name_len);
    person.age = age;

    return person;
}

void insert(node_t* people) {
    printf("Insert Person");
    list_insert(people, read_person());
}

void remove(node_t* people) {
    list_remove(people, read_person());
}

void clear(node_t* people) {
    list_clear(people);
}

void show(node_t* people) {
    node_t* current = people->next;
    size_t len = 0;
    printf("People Management - Linked List\n");

    while (current) {
        printf("$  %s, %s (%d)\n"
               , current->content.name
               , current->content.first_name
               , current->content.age
        );
        printf("------------------------------------------------------------------\n");
        current = current->next;
        ++len;
    }

    if (len) {
        printf("(%ld) persons.\n", len);
    }
    else {
        printf("There are no entries.\n");
    }
}