#include <stdio.h>
#include "list.h"

void take_user_input(int *num)
{
  printf("Enter a number: ");
  scanf("%d", num);
}

void perform_action(List_ptr list, char input_char)
{
  int num, position;
  switch (input_char)
  {
  case 'a':
    take_user_input(&num);
    add_to_end(list, num);
    break;

  case 'b':
    take_user_input(&num);
    add_to_start(list, num);
    break;

  case 'c':
    take_user_input(&num);
    printf("Enter position: ");
    scanf("%d", &position);
    insert_at(list, num, position);
    break;

  case 'd':
    take_user_input(&num);
    add_unique(list, num);
    break;

  case 'e':
    remove_from_start(list);
    break;

  case 'f':
    remove_from_end(list);
    break;

  case 'g':
    printf("Enter position: ");
    scanf("%d", &position);
    remove_at(list, position);
    break;

  case 'h':
    take_user_input(&num);
    remove_first_occurrence(list, num);
    break;

  case 'i':
    take_user_input(&num);
    remove_all_occurrences(list, num);
    break;

  case 'j':
    clear_list(list);
    break;

  case 'k':
    break;

  case 'l':
    display(list);
    break;

  case 'm':
    break;
  }
}

int main(void)
{
  List_ptr list = create_list();
  char input;
  printf("Please enter the alphabet of the operation you would like to perform(a-m)\n");
  scanf("%c", &input);
  while (input != 'm')
  {
    perform_action(list, input);
    scanf("%c", &input);
    printf("Please enter the alphabet of the operation you would like to perform(a-m)\n");
  }
  return 0;
}