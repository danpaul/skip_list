#ifndef skip_list.h
#define skip_list.h

#include <stdio.h>
#include <stdlib.h>

#define DATA_TYPE unsigned int

enum boolean {FALSE, TRUE};

typedef struct _Skip_node Skip_node;

struct _Skip_node
{
    Skip_node* left_node;
    Skip_node* right_node;
    Skip_node* up_node;
    Skip_node* down_node;
    DATA_TYPE* data;
};

Skip_node* skip_node_constructor(DATA_TYPE* data);

void skip_node_destructor(Skip_node* node);

void skip_list_destructor(Skip_node* head);

void skip_node_delete(Skip_node* node);

Skip_node* skip_node_insert_search(Skip_node* head,
                                   DATA_TYPE* data, int is_search);

void perform_insertion(Skip_node* head, Skip_node* preceiding_node,
                       Skip_node* node_to_insert);

void skip_node_remove(Skip_node* head, DATA_TYPE data);

void skip_list_destructor(Skip_node* head);

void skip_list_print(Skip_node* head);

#endif
