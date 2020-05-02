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
  if (position >= list->count)
    return Failure;
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
