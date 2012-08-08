/******************************************************************************
  Title          : main.c
  Author         : Daniel Breczinski
  Created on     : November, 2011
  Description    : Poerformance comparison of linked-list and skip list ADTs.
  Usage          : ./lists
  Build with     : gcc main.c double_linked_list.c skip_list.c -o lists
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#include "double_linked_list.h"
#include "skip_list.h"


/*******************************************************************************
Precondition:   Takes an array of values to try (number of ellements to
                populate lists with), array_size of the number of ellements in
                array, number_of_search trials defines how many test searches
                to perform of the populated list to determine average search
                time, max_value is the largest possible int that can be placed
                in the lists.

Postcondition:  Prints to screen average search time for lists with given number
                of ellements.

Note:           Program take two ints from the command line representing the
                number of ellements to populate the lists with and the number
                of trials to perform on the lists.
*******************************************************************************/
void run_trials(int values_to_try[], int array_size, int number_of_search_trials,
                unsigned int max_value);



int main(int argc, char *argv[])
{
    srand(time(NULL));

    int values_to_try[1];
    int array_size = 1;

    if(argc!=3)
    {
        printf("Invalid arguments.");
        exit(-1);
    }

    values_to_try[0] = atoi(argv[1]);
    int number_of_search_trials = atoi(argv[2]);
    run_trials(values_to_try, array_size, number_of_search_trials,
                RAND_MAX);

    return 0;
}


/*******************************************************************************
                    TRIALS FUNCTION
*******************************************************************************/
void run_trials(int values_to_try[], int array_size, int number_of_search_trials,
                unsigned int max_value)
{
    time_t start_time;
    double duration;
    int* int_ptr;
    double average_time;

    unsigned int number_of_trials;
    int i = 0;
    for(i; i < array_size; i++)
    {
        if(values_to_try[i]>max_value)
        {
            printf("Value(s) supplied exceide system limits.\n");
            exit(-1);
        }
        int j = 0;
        for(j; j < 2; j++)
        {
/*******************************************************************************
                lINKED-LIST TRIAL
*******************************************************************************/
            if(j==0)
            {

                Node* linked_list_head_node = node_constructor(NULL);

                //init. data
                number_of_trials = values_to_try[i];
                int number_of_trials_counter = number_of_trials;

                //populate list
                for(number_of_trials_counter; number_of_trials_counter > 0;
                    number_of_trials_counter--)
                {
                    int_ptr = malloc(sizeof(int));
                    *int_ptr = rand()%max_value;
                    if(linked_list_insert_search
                       (linked_list_head_node, int_ptr, 0)
                       !=NULL)
                    {
                        number_of_trials_counter++;
                    }

                }

                //run search trials
                start_time = time(NULL);
                int k = 0;
                for(k; k<number_of_search_trials; k++)//
                {
                    int_ptr = malloc(sizeof(int));
                    *int_ptr = rand()%max_value;
                    linked_list_insert_search(linked_list_head_node, int_ptr, 1);
                }

                //perform calculations and determine average time of search
                duration = (double)time(NULL) - (double)start_time;
                if(duration>0)
                {
                    average_time = duration/(double)number_of_search_trials;
                }
                else{average_time = 0.0;}

                printf("On a sorted linked-list of  %d items, \n",
                        number_of_trials);
                printf("average search time is: %f seconds per search.\n\n",
                        average_time);

                list_destructor(linked_list_head_node);
                free(linked_list_head_node);
            }
/*******************************************************************************
                SKIP-LIST TRIAL
*******************************************************************************/
            else
            {

                Skip_node* skip_head = skip_node_constructor(NULL);
                number_of_trials = values_to_try[i];
                int number_of_trials_counter = number_of_trials;

                //populate skip list
                for(number_of_trials_counter; number_of_trials_counter > 0;
                    number_of_trials_counter--)
                {
                    int_ptr = malloc(sizeof(int));
                    *int_ptr = rand()%max_value;
                    if(skip_node_insert_search(skip_head, int_ptr, 0) != NULL)
                    {
                        number_of_trials_counter++;
                    }

                }

                //run search trials
                start_time = time(NULL);
                int k = 0;
                for(k; k<number_of_search_trials; k++)
                {
                    int_ptr = malloc(sizeof(int));
                    *int_ptr = rand()%max_value;
                    skip_node_insert_search(skip_head, int_ptr, 1);
                }
                duration = (double)time(NULL) - (double)start_time;

                //calculate average and output result
                if(duration>0){average_time = duration/
                               (double)number_of_search_trials;}
                else{average_time = 0.0;}

                printf("On a sorted skip-list of  %d items, \n",
                        number_of_trials);
                printf("average search time is: %f seconds per search.\n\n",
                        average_time);

                skip_list_destructor(skip_head);
                free(skip_head);
            }
        }
    }
}
