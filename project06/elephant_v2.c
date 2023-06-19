#include "elephant.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Elephant *new_elephant(const char name[], enum type which_type,
                       unsigned int id, unsigned short weight,
                       float trunk_length) {
    Elephant *elephant = NULL;
    char *new_name = NULL;
    if (name != NULL) {
        new_name = malloc(strlen(name) + 1);
        elephant = malloc(sizeof(Elephant));

        strcpy(new_name, name);
        elephant->name = new_name;

        elephant->elephant_type = which_type;
        elephant->id = id;
        elephant->weight = weight;
        elephant->trunk_length = trunk_length;
    }
    return elephant;
}

unsigned short get_type(const Elephant *const el_ptr,
                        enum type *const type_ptr) {
    unsigned short return_val = 0;

    if (el_ptr != NULL && type_ptr != NULL) {
        return_val = 1;
        *type_ptr = el_ptr->elephant_type;
    }
    return return_val;
}

const char *get_name(const Elephant *const el_ptr) {
    char *return_val = NULL;
    if (el_ptr != NULL && el_ptr->name != NULL) {
        return_val = malloc(strlen(el_ptr->name) + 1);

        if (return_val != NULL) {
            strcpy(return_val, el_ptr->name);
        }
    }
    return return_val;
}

void print_elephant(const Elephant *const el_ptr) {
    if (el_ptr != NULL) {
        printf("%s ", el_ptr->name);
        if (el_ptr->elephant_type == 0) {
            printf("AFRICAN ");
        } else {
            printf("ASIAN ");
        }
        printf("%d ", el_ptr->id);
        printf("%d ", el_ptr->weight);
        printf("%g\n", el_ptr->trunk_length);
    }
}

short compare(const Elephant *const el_ptr1, const Elephant *const el_ptr2) {
    short return_val = -1;

    if (el_ptr1 != NULL && el_ptr2 != NULL && el_ptr1->name != NULL &&
        el_ptr2->name != NULL) {
        if (strcmp(el_ptr1->name, el_ptr2->name) == 0 &&
            el_ptr1->elephant_type == el_ptr2->elephant_type &&
            el_ptr1->id == el_ptr2->id &&
            el_ptr1->trunk_length == el_ptr2->trunk_length &&
            el_ptr1->weight == el_ptr2->weight) {
            return_val = 1;
        } else {
            return_val = 0;
        }
    }
    return return_val;
}

unsigned short change_name(Elephant *const el_ptr, const char new_name[]) {
    unsigned short return_val = 0;
    if (el_ptr != NULL && new_name != NULL) {
        char *new_string = malloc(strlen(new_name) + 1);
        strcpy(new_string, new_name);

        if (new_string != NULL) {
            free(el_ptr->name);
            el_ptr->name = new_string;
            return_val = 1;
        }
    }
    return return_val;
}

unsigned short copy(Elephant *const el_ptr1, const Elephant *const el_ptr2) {
    unsigned int return_val = 1;

    if (el_ptr1 != NULL && el_ptr2 != NULL && el_ptr1->name != NULL &&
        el_ptr2->name != NULL) {
        change_name(el_ptr1, el_ptr2->name);

        el_ptr1->elephant_type = el_ptr2->elephant_type;
        el_ptr1->id = el_ptr2->id;
        el_ptr1->weight = el_ptr2->weight;
        el_ptr1->trunk_length = el_ptr2->trunk_length;
    } else {
        return_val = 0;
    }
    return return_val;
}
