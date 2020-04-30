
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <libpq-fe.h>

#include "db.h"

void foo(void)
{
  printf("foo\n");
}

// Perform lookup on manifest table to find slug from a given id
int get_slug_from_id(int id, char* slug)
{
  int i = 0;
  int j = 0;
  int records = 0;
  
  // db variables
  PGconn* db;
  PGresult* res;
  
  // strings
  char lookup_query[128];
  
  // connect to db