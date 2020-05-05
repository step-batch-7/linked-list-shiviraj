#include <stdio.h>
#include <stdlib.h>
#include "list.h"

List_ptr create_list(void)
{
  List_ptr list = malloc(sizeof(List));
  list->head = NULL;
  list->last = NULL;
  list->count = 0;
  return list;
};

Status add_to_end(List_ptr list, int value)
{
  Node_ptr node = malloc(sizeof(Node));
  node->value = value;
  if (list->head == NULL)
  {
    list->head = node;
    list->last = node;
  }
  list->last->next = node;
  list->last = node;
  list->count++;
  node->next = NULL;
  return Success;
};

Status add_to_start(List_ptr list, int value)
{
  Node_ptr node = malloc(sizeof(Node));
  node->value = value;
  node->next = list->head;
  list->head = node;
  if (list->last == NULL)
    list->last = node;
  list->count++;
  return Success;
};

Node_ptr find_node_at(List_ptr list, int position)
{
  Node_ptr node = list->head;
  for (int i = 1; i < position; i++)
    node = node->next;
  return node;
}

Status insert_at(List_ptr list, int value, int position)
{
  if (position < 0 && position > list->count)
    return Failure;
  if (position == 0)
    return add_to_start(list, value);
  if (position == list->count - 1)
    return add_to_end(list, value);
  Node_ptr node = malloc(sizeof(Node));
  node->value = value;
  Node_ptr node_at = find_node_at(list, position);
  node->next = node_at->next;
  node_at->next = node;
  list->count++;
  return Success;
};

Status is_include_in_list(List_ptr list, int value)
{
  Node_ptr node = list->head;
  Status is_include = Failure;
  while (is_include == Failure && node != NULL)
  {
    if (node->value == value)
      is_include = Success;
    node = node->next;
  }
  return is_include;
}

Status add_unique(List_ptr list, int value)
{
  Status is_include = is_include_in_list(list, value);
  if (is_include)
    return !is_include;
  return add_to_end(list, value);
};

void display(List_ptr list)
{
  Node_ptr node = list->head;
  while (node != NULL)
  {
    printf("%d \n", node->value);
    node = node->next;
  }
};

Status remove_from_start(List_ptr list)
{
  if (list->count < 1)
    return Failure;
  Node_ptr node_to_remove = list->head;
  list->head = node_to_remove->next;
  list->count--;
  free(node_to_remove);
  return Success;
};

Status remove_from_end(List_ptr list)
{
  if (list->count < 1)
    return Failure;
  Node_ptr node_to_remove = list->last;
  list->last = find_node_at(list, list->count - 1);
  list->last->next = NULL;
  list->count--;
  free(node_to_remove);
  return Success;
};

Status remove_at(List_ptr list, int position)
{
  if (position < 0 || position > list->count)
    return Failure;
  if (position == 0)
    return remove_from_start(list);
  if (position == list->count - 1)
    return remove_from_end(list);
  Node_ptr node = find_node_at(list, position);
  Node_ptr node_to_remove = node->next;
  node->next = node_to_remove->next;
  list->count--;
  free(node_to_remove);
  return Success;
};

Prev_Current_Pair_ptr find_pair_of_first_occurrence(List_ptr list, int value)
{
  Prev_Current_Pair_ptr pair = malloc(sizeof(Prev_Current_Pair));
  pair->prev = list->head;
  pair->current = list->head;
  while (pair->current->value != value)
  {
    pair->prev = pair->current;
    pair->current = pair->prev->next;
  }
  return pair;
};

Status remove_first_occurrence(List_ptr list, int value)
{
  Status is_include = is_include_in_list(list, value);
  if (!is_include)
    return Failure;
  Prev_Current_Pair_ptr pair = find_pair_of_first_occurrence(list, value);
  if (list->head == pair->current)
    list->head = pair->current->next;
  pair->prev->next = pair->current->next;
  if (list->last == pair->current)
    list->last = pair->prev;
  list->count--;
  free(pair->current);
  return Success;
};

Status remove_all_occurrences(List_ptr list, int value)
{
  Status is_include = is_include_in_list(list, value);
  while (is_include)
  {
    remove_first_occurrence(list, value);
    is_include = is_include_in_list(list, value);
  }
  return Success;
};

Status clear_list(List_ptr list)
{
  Node_ptr node_to_remove = list->head;
  while (node_to_remove != NULL)
  {
    remove_from_start(list);
    node_to_remove = list->head;
  }
  return Success;
};

void destroy_list(List_ptr list)
{
  clear_list(list);
  free(list);
};
