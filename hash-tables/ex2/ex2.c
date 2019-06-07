#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "ex2.h"

char **reconstruct_trip(Ticket **tickets, int length)
{
  HashTable *ht = create_hash_table(length);
  char **route = malloc(length * sizeof(char *));

  int counter = 0;
  // go through tickets array
  for (int i = 0; i < length; i++)
  {
    // add each ticket to ht in key: value fashion (source: destination)
    hash_table_insert(ht, tickets[i]->source, tickets[i]->destination);
  }
  // search for ticket with NONE source in ht
  Ticket *current_source = hash_table_retrieve(ht, "NONE");
  // while current ticket destination is not "NONE"
  // add destination to route array
  while (strcmp(current_source, "NONE") != 0)
  {
    // append value to route array
    route[counter] = current_source;
    // find key:value pair where key is the current ticket's destination
    current_source = hash_table_retrieve(ht, current_source);
    counter++;
  }
  // append "NONE" to route after loop is finished
  route[counter] = "NONE";

  destroy_hash_table(ht);

  return route;
}

void print_route(char **route, int length)
{
  for (int i = 0; i < length; i++)
  {
    printf("%s\n", route[i]);
  }
}

#ifndef TESTING
int main(void)
{
  // Short test
  Ticket **tickets = malloc(3 * sizeof(Ticket *));

  Ticket *ticket_1 = malloc(sizeof(Ticket));
  ticket_1->source = "NONE";
  ticket_1->destination = "PDX";
  tickets[0] = ticket_1;

  Ticket *ticket_2 = malloc(sizeof(Ticket));
  ticket_2->source = "PDX";
  ticket_2->destination = "DCA";
  tickets[1] = ticket_2;

  Ticket *ticket_3 = malloc(sizeof(Ticket));
  ticket_3->source = "DCA";
  ticket_3->destination = "NONE";
  tickets[2] = ticket_3;

  print_route(reconstruct_trip(tickets, 3), 3); // PDX, DCA, NONE

  for (int i = 0; i < 3; i++)
  {
    free(tickets[i]);
  }

  free(tickets);

  return 0;
}
#endif
