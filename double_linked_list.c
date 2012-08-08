#include "double_linked_list.h"

/*******************************************************************************
                    CONSTRUCTOR
*******************************************************************************/
Node* node_constructor(DATA_TYPE* data)
{
    Node* new_node = malloc(sizeof(Node));
    new_node->data = data;
    new_node->next_node = NULL;
    new_node->previous_node = NULL;
    return(new_node);
}


/*******************************************************************************
                    DESTRUCTOR
*******************************************************************************/
void node_destructor(Node* node)
{
    free(node->data);
    free(node);
    return;
}

/*******************************************************************************
                    INSERT
*******************************************************************************/
Node* linked_list_insert_search(Node* head, DATA_TYPE* data, int is_search)
{
    /**
    note: Client is responsible for memory allocation.
          Non-duplicating insert, data passed to function
          is freed if dupication found
    */

    Node* new_node = node_constructor(data);
    Node* place_holder = head->next_node;

    if(head->next_node==NULL||*data<=*head->next_node->data)
    {
        new_node->next_node=head->next_node;
        if(head->next_node!=NULL)
        {
            if(*data==*head->next_node->data)
            {
                node_destructor(new_node);
                return head->next_node;
            }
            head->next_node->previous_node = new_node;
        }
        if(is_search==0)
        {
            new_node->previous_node=head;
            head->next_node = new_node;
            return NULL;
        }
        node_destructor(new_node);
        return NULL;
    }
    while(place_holder->next_node!=NULL)
    {
        if(*data <= *place_holder->next_node->data)
        {
            if(*data==*place_holder->next_node->data)
            {
                node_destructor(new_node);
                return place_holder->next_node;
            }
            if(is_search==0)
            {
                new_node->next_node = place_holder->next_node;
                place_holder->next_node->previous_node = new_node;
                new_node->previous_node = place_holder;
                place_holder->next_node = new_node;
                return NULL;
            }
            else
            {
                node_destructor(new_node);
                return NULL;
            }
        }
        place_holder = place_holder->next_node;
    }
    //insertion at end of list
    new_node->previous_node = place_holder;
    place_holder->next_node = new_node;
    return NULL;

}


/*******************************************************************************
                    REMOVE
*******************************************************************************/
void remove_node(Node* head, DATA_TYPE data)
{
    Node* place_holder = head->next_node;
    while(place_holder!=NULL)
    {
        if(*place_holder->data==data)
        {
            if(place_holder->next_node==NULL)
            {
                place_holder->previous_node->next_node = NULL;
                node_destructor(place_holder);

                return;
            }
            else
            {
                place_holder->previous_node->next_node =
                    place_holder->next_node;
                place_holder->next_node->previous_node =
                    place_holder->previous_node;
                node_destructor(place_holder);
                return;
            }
        }
        if(*place_holder->data > data)
        {
            return;
        }
        place_holder = place_holder->next_node;
    }
    return;
}

/*******************************************************************************
                    LIST DESTRUCTOR
*******************************************************************************/
void list_destructor(Node* head)
{
    Node* place_holder = head->next_node;
    Node* temp;
    while(place_holder!=NULL)
    {
        temp = place_holder->next_node;
        node_destructor(place_holder);
        place_holder = temp;
    }
    head->next_node=NULL;
}

/*******************************************************************************
                    PRINT ALL
*******************************************************************************/
void print_list(Node* head)
{
    Node* place_holder = head->next_node;
    while(place_holder!=NULL)
    {
        printf("%d\n",*place_holder->data);
        place_holder = place_holder->next_node;
    }
}
