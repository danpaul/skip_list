#include "skip_list.h"

/*******************************************************************************
                    CONSTRUCTOR
*******************************************************************************/
Skip_node* skip_node_constructor(DATA_TYPE* data)
{
    Skip_node* new_node = malloc(sizeof(Skip_node));
    new_node->data = data;
    new_node->left_node = NULL;
    new_node->right_node = NULL;
    new_node->up_node = NULL;
    new_node->down_node = NULL;
    return(new_node);
}

/*******************************************************************************
                    DESTRUCTOR
*******************************************************************************/
void skip_node_destructor(Skip_node* node)
{
    free(node);
}

void skip_node_delete(Skip_node* node)
{
    Skip_node* place_holder = node;
    Skip_node* next;
    while(place_holder->up_node!=NULL)
    {
        next = place_holder->up_node;
        skip_node_destructor(place_holder);
        place_holder = next;
    }
    skip_node_destructor(place_holder);
}

/*******************************************************************************
                    LIST DESTRUCTOR
*******************************************************************************/
void skip_list_destructor(Skip_node* head)
{
    Skip_node* next;
    Skip_node* temp;

    if (head->down_node != NULL)
    {
        next = head->down_node;
        next->up_node == NULL;
    }
    else if (head->right_node != NULL)
    {
        next = head->right_node;
    }
    else
    {
        return;
    }
    head->down_node = NULL;
    head->right_node = NULL;
    while(next->down_node!=NULL)
    {
        next = next->down_node;
    }
    while(next->right_node!=NULL)
    {
        temp = next->right_node;
        skip_node_delete(next);
        next = temp;
    }
    skip_node_delete(next);
    return;
}

/*******************************************************************************
                    INSERT / SEARCH
*******************************************************************************/
Skip_node* skip_node_insert_search(Skip_node* head, DATA_TYPE* data,
                                   int is_search)
{

    Skip_node* new_node = skip_node_constructor(data);

    Skip_node* place_holder = head;

    while(TRUE)
    {
        if(place_holder->right_node==NULL)
        {
            if(place_holder->down_node==NULL)
            {
                if(is_search==0)
                {
                    perform_insertion(head, place_holder, new_node);
                    return NULL;
                }
                else
                {
                    skip_node_destructor(new_node);
                    return NULL;
                }
            }
            place_holder = place_holder->down_node;
        }
        else
        {
            if(*place_holder->right_node->data >= *data)
            {
                if(place_holder->down_node != NULL)
                {
                    place_holder = place_holder->down_node;
                }
                else
                {
                    if(*place_holder->right_node->data == *data)
                    {
                        //found match
                        skip_node_destructor(new_node);
                        return place_holder->right_node;
                    }
                    //perform insert
                        if(is_search==0)
                        {
                            perform_insertion(head, place_holder, new_node);
                            return NULL;
                        }
                        else
                        {
                            skip_node_destructor(new_node);
                            return NULL;
                        }

                    }
                }
            else
            {
                place_holder = place_holder->right_node;
            }
        }
    }

    return NULL;
}



void perform_insertion(Skip_node* head, Skip_node* preceiding_node,
                       Skip_node* node_to_insert)
{
    node_to_insert->left_node = preceiding_node;
    node_to_insert->right_node = preceiding_node->right_node;
    if(node_to_insert->right_node != NULL)
    {
        node_to_insert->right_node->left_node = node_to_insert;
    }
    preceiding_node->right_node = node_to_insert;
    build_skip(head, node_to_insert);
}


/*******************************************************************************
                    BUILD SKIP
*******************************************************************************/
void build_skip(Skip_node* head, Skip_node* current_node)
{
    int flip = rand()%2;

    if(flip==1)
    {
        Skip_node* place_holder = current_node;
        Skip_node* new_node = skip_node_constructor(current_node->data);
        //set up and down pointers
        current_node->up_node = new_node;
        new_node->down_node = current_node;
        ///need to find next up node or move last node before head/subheads
        while(place_holder->left_node->left_node!=NULL &&
              place_holder->left_node->up_node==NULL)
        {
            place_holder = place_holder->left_node;

        }
        if(place_holder->left_node->up_node==NULL)
        {
            //at top of list must create a new node and move head up
            Skip_node* sub_head = skip_node_constructor(NULL);
            sub_head->right_node = head->right_node;
            if(sub_head->right_node != NULL)
            {
                sub_head->right_node->left_node = sub_head;
            }
            sub_head->down_node = head->down_node;
            if(sub_head->down_node!=NULL)
            {
                sub_head->down_node->up_node = sub_head;
            }
            head->down_node = sub_head;
            sub_head->up_node = head;
            head->right_node = NULL;
        }
        perform_insertion(head, place_holder->left_node->up_node, new_node);

        return;
    }
    return;
}

/*******************************************************************************
                    PRINT
*******************************************************************************/
void skip_list_print(Skip_node* head)
{
///*
    Skip_node* place_holder = head;
    Skip_node* place_holder2 = head;
    printf("\n\n");
    while(place_holder!=NULL)
    {
        place_holder2 = place_holder->right_node;
        while(place_holder2!=NULL)
        {
            printf("%d ", *place_holder2->data);
            place_holder2 = place_holder2->right_node;
        }
        printf("\n");
        place_holder = place_holder->down_node;
    }
}

