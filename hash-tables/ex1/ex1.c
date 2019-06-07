#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"
#include "ex1.h"

Answer *get_indices_of_item_weights(int *weights, int length, int limit)
{
  HashTable *ht = create_hash_table(16);
  Answer *my_answer = malloc(sizeof(Answer));

  for (int i = 0; i < length; i++)
  {
    hash_table_insert(ht, weights[i], i);
  }

  for (int i = 0; i < length; i++)
  {
    int search_term = limit - weights[i];
    int search_result = hash_table_retrieve(ht, search_term);
    if (search_result != -1)
    {
      if (search_result > i)
      {
        my_answer->index_1 = search_result;
        my_answer->index_2 = i;
      }
      else
      {
        my_answer->index_1 = i;
        my_answer->index_2 = search_result;
      }
      destroy_hash_table(ht);
      return my_answer;
    }
  }
  destroy_hash_table(ht);
  return NULL;
}

void print_answer(Answer *answer)
{
  if (answer != NULL)
  {
    printf("%d %d\n", answer->index_1, answer->index_2);
  }
  else
  {
    printf("NULL\n");
  }
}

#ifndef TESTING
int main(void)
{
  // TEST 1
  int weights_1 = {9};
  Answer *answer_1 = get_indices_of_item_weights(&weights_1, 1, 9);
  print_answer(answer_1); // NULL

  // TEST 2
  int weights_2[] = {4, 4};
  Answer *answer_2 = get_indices_of_item_weights(weights_2, 2, 8);
  print_answer(answer_2); // {1, 0}

  // TEST 3
  int weights_3[] = {4, 6, 10, 15, 16};
  Answer *answer_3 = get_indices_of_item_weights(weights_3, 5, 21);
  print_answer(answer_3); // {3, 1}

  // TEST 4
  int weights_4[] = {12, 6, 7, 14, 19, 3, 0, 25, 40};
  Answer *answer_4 = get_indices_of_item_weights(weights_4, 9, 7);
  print_answer(answer_4); // {6, 2}

  return 0;
}

#endif