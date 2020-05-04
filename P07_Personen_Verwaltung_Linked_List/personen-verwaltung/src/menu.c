#include "menu.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>

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
            menu_remove(people);
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
    printf("Insert Person\n");
    list_insert(people, read_person());
}

void menu_remove(node_t* people) {
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
        printf("$  %s, %s (%d)\n", 
                current->content.name,
                current->content.first_name,
                current->content.age
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