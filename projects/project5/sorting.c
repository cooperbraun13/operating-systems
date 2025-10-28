/**
Cooper Braun
CPSC-346-01
Project 5
10/27/2025
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10
#define NUMBER_OF_THREADS 3

void *sorter(void *params); /* thread that performs basic sorting algorithm */
void *merger(void *params); /* thread that performs merging of results */

int list[SIZE] = {7, 12, 19, 3, 18, 4, 2, 6, 15, 8};

int result[SIZE];

typedef struct
{
  int from_index;
  int to_index;
} parameters;

int main(int argc, const char *argv[])
{
  int i;

  pthread_t workers[NUMBER_OF_THREADS];

  /* establish the first sorting thread */
  // 1. call malloc to allocate a �parameters�
  // 2. use �parameters� to specify the first half of the array
  // 3. create the first thread
  {
    parameters *p1 = (parameters *)malloc(sizeof(parameters));
    if (p1 == NULL)
    {
      perror("malloc");
      exit(EXIT_FAILURE);
    }
    p1->from_index = 0;
    p1->to_index = (SIZE / 2) - 1; // left half: indices [0 .. SIZE/2 - 1]
    if (pthread_create(&workers[0], NULL, sorter, p1) != 0)
    {
      perror("pthread_create p1");
      exit(EXIT_FAILURE);
    }
  }

  /* establish the second sorting thread */
  // 1. call malloc to allocate a �parameters�
  // 2. use �parameters� to specify the second half of the array
  // 3. create the second thread
  {
    parameters *p2 = (parameters *)malloc(sizeof(parameters));
    if (p2 == NULL)
    {
      perror("malloc");
      exit(EXIT_FAILURE);
    }
    p2->from_index = (SIZE / 2);
    p2->to_index = SIZE - 1; // right half: indices [SIZE/2 .. SIZE-1]
    if (pthread_create(&workers[1], NULL, sorter, p2) != 0)
    {
      perror("pthread_create p2");
      exit(EXIT_FAILURE);
    }
  }

  /* now wait for the 2 sorting threads to finish */
  // use ptheread_join; wait for 2 sorting threads to finish
  {
    // join worker 0
    void *ret0;
    if (pthread_join(workers[0], &ret0) != 0)
    {
      perror("pthread_join 0");
      exit(EXIT_FAILURE);
    }
    // free parameters allocated for worker 0
    free(ret0); // return the malloc'd params from sorter via pthread_exit(ret)

    // join worker 1
    void *ret1;
    if (pthread_join(workers[1], &ret1) != 0)
    {
      perror("pthread_join 1");
      exit(EXIT_FAILURE);
    }
    // free parameters allocated for worker 1
    free(ret1);
  }

  /* establish the merge thread */
  // use �parameters� to hold the beginning index in each half
  // create the third thread: merge
  {
    parameters *pm = (parameters *)malloc(sizeof(parameters));
    if (pm == NULL)
    {
      perror("malloc");
      exit(EXIT_FAILURE);
    }
    pm->from_index = 0;        // start of left half
    pm->to_index = (SIZE / 2); // start of right half
    if (pthread_create(&workers[2], NULL, merger, pm) != 0)
    {
      perror("pthread_create merge");
      exit(EXIT_FAILURE);
    }
  }

  /* wait for the merge thread to finish */
  {
    void *retm;
    if (pthread_join(workers[2], &retm) != 0)
    {
      perror("pthread_join merge");
      exit(EXIT_FAILURE);
    }
    free(retm); // free the merge parameters
  }

  /* output: the sorted array */
  {
    printf("sorted result: ");
    for (i = 0; i < SIZE; i++)
    {
      printf("%d%s", result[i], (i == SIZE - 1) ? "\n" : " ");
    }
  }

  return 0;
}

/**
 * Sorting thread.
 *
 * This thread can essentially use any algorithm for sorting
 */

void *sorter(void *params)
{
  parameters *p = (parameters *)params;

  // Sorting algorithm here. It can be any sorting algorithm.
  // im gonna use insertion sort on list[p->from_index .. p->to_index] in place
  int start = p->from_index;
  int end = p->to_index;
  for (int i = start + 1; i <= end; i++)
  {
    int key = list[i];
    int j = i - 1;
    while (j >= start && list[j] > key)
    {
      list[j + 1] = list[j];
      j--;
    }
    list[j + 1] = key;
  }

  pthread_exit(0);
}

/**
 * Merge thread
 *
 * Uses simple merge sort for merging two sublists
 */

void *merger(void *params)
{
  parameters *p = (parameters *)params;

  // reuse �parameters� to hold the first index in each half
  // merge two sorted sublist to the arry result
  int left_start = p->from_index; // expected 0
  int right_start = p->to_index;  // expected SIZE/2
  int left_end = right_start - 1;
  int right_end = SIZE - 1;

  int i = left_start;  // pointer into left half
  int j = right_start; // pointer into right half
  int k = 0;           // pointer into result

  while (i <= left_end && j <= right_end)
  {
    if (list[i] <= list[j])
    {
      result[k++] = list[i++];
    }
    else
    {
      result[k++] = list[j++];
    }
  }
  // copy any leftovers
  while (i <= left_end)
  {
    result[k++] = list[i++];
  }
  while (j <= right_end)
  {
    result[k++] = list[j++];
  }

  pthread_exit(0);
}
