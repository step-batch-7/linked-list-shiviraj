#include <stdio.h>
#include "list.h"

int main(void)
{
  List_ptr list = create_list();
  Status status = add_to_start(list, 2);
  status = add_to_start(list, 1);
  status = add_to_end(list, 4);
  status = add_to_end(list, 5);
  status = insert_at(list, 3, 2);
  display(list);
  return 0;
}