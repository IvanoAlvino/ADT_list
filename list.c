//
//  list.c
//  1_memory_allocation
//
//  Created by Ivano Alvino on 17/05/13.
//  Copyright (c) 2013 Ivano Alvino. All rights reserved.
//

/*----------------------------------------------
                Includes
 ----------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
typedef enum {FALSE, TRUE} boolean;

/*----------------------------------------------
                Structures definitions
 ----------------------------------------------*/

typedef struct cell {
    void* item;
    struct cell *next;
    struct cell *previous;
} list_element;

struct list_handler {
    list_element *head;
    list_element *iterator_count;
    size_t size;
};

/*----------------------------------------------
                Functions
  ----------------------------------------------*/


list create_list()
{
    list L = malloc( sizeof(*L) );
    L->head = NULL;
    L->iterator_count = L->head;
    L->size = 0;
    return L;
};

void head_insert( list L, void* data )
{
    // new list element creation and initialization
    list_element* e = malloc( sizeof(list_element) );
    e->previous = NULL;
    e->item = data;
    
    // head insert
    if (L->head != NULL )
        (L->head)->previous = e;
    e->next = L->head;
    L->head = e;
    L->size++;
};
  
void tail_insert( list L, void* data )   
{
    // new list element creation and initialization
    list_element* e = malloc( sizeof(list_element) );
    e->item = data;
    e->previous = NULL;
    e->next = NULL;
    
    // tail insert
    if ( L->head == NULL) //first element inserted
        L->head = e;
    else {
        list_element* this = L->head;
        while (this->next != NULL)
            this = this->next;
        this->next = e;
        e->previous = this;
    }
    L->size++;
}

//search is a private function, not seen by the interface (list.h)

list_element* search( list L, void* data, int (*cmp) (void*, void*) )
{
    list_element* this = L->head;
    while ( this != NULL )
        if ( cmp( data, this->item) == TRUE )
            return this;
        else
            this = this->next;
    return NULL;
};

void *item_delete( list L, void* data, int (*cmp) (void*, void*))
{
    list_element* this = search( L, data, cmp);
    void *item;
    if (this != NULL )
    {
        // special cases ( size(list) == 1 || 2 ) 
        if (this->previous == NULL)
        {
            if (this->next == NULL) {
                L->head = NULL;
                L->size--;
                item = this->item;
                free(this);
                return item;
            }
            L->head = this->next;
            L->size--;
            item = this->item;
            free(this);
            return item;
        }
        else if ( this->next == NULL ) {
            (this->previous)->next = NULL;
            L->size--;
            item = this->item;
            free(this);
            return item;
        }
        
        // general case, i.e. (size(list) > 2)
        (this->previous)->next = this->next;
        (this->next)->previous = this->previous;
        L->size--;
        item = this->item;
        free(this);
        return item;
    }
    return NULL;
}

void print_list( list L, void (*print_item) (void*))
{
    list_element* this = L->head;
    while (this != NULL) {
        print_item( this->item );
        this = this->next;
    }
}

void* head_extract( list L ) {
    if ( L->head == NULL ) {
        printf("\nThe list is empty");
        return NULL;
    }
    void* data = (L->head)->item;
    list_element* current = L->head;
    L->head = (L->head)->next;
    free(current);
    return data;
    L->size--;
}

void free_list( list *L) {
    list_element *this, *curr;
    this = (*L)->head;
    while ( this != NULL ) {
        curr = this;
        this = this->next;
        free(curr);
    }
    free(*L);
}

void create_iterator(list L) {
    L->iterator_count = L->head;
}

void *next_element(list L) {
    list_element *this = L->iterator_count;
    if ( this == NULL )
        return NULL;
    L->iterator_count = this->next;
    return this->item;
}

size_t get_size(list L) {
    return L->size;
}







