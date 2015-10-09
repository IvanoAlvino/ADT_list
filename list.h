//
//  list.h
//  1_memory_allocation
//
//  Created by Ivano Alvino on 17/05/13.
//  Copyright (c) 2013 Ivano Alvino. All rights reserved.
//

/*----------------------------------------------
                Includes
 ----------------------------------------------*/

#ifndef __memory_allocation_list_h
#define __memory_allocation_list_h

typedef struct list_handler* list;

/*----------------------------------------------
                Prototypes
 ----------------------------------------------*/

list create_list();
void head_insert( list L, void* data );
void *head_extract( list L );
void tail_insert( list L, void* data );
void *item_delete( list L, void* data, int (*cmp) (void*, void*));
void print_list( list L, void (*print_item) (void*));
void free_list( list *L);
void create_iterator(list L);
void *next_element(list L);
size_t get_size(list L);

#endif
