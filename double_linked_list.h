#ifndef double_linked_list.h
#define double_linked_list.h

#include <stdio.h>
#include <stdlib.h>

#define DATA_TYPE unsigned int

typedef struct _Node Node;

struct _Node
{
    Node* previous_node;
    Node* next_node;
    DATA_TYPE* data;
};

Node* node_constructor(DATA_TYPE* data);

void node_destructor(Node* node);

Node* linked_list_insert_search(Node* head, DATA_TYPE* data, int is_search);

void remove_node(Node* head, DATA_TYPE data);

void list_destructor(Node* head);

void print_list(Node* head);

#endif
