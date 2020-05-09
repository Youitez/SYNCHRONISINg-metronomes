
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
  db = PQconnectdb("dbname=equities user=jmcph4");
  
  if(PQstatus(db) == CONNECTION_BAD)
  {
    fprintf(stderr, "[ERROR] Failed to connect to the PostgreSQL database.\n");
    
    return EXIT_FAILURE;
  }
  
  sprintf(lookup_query, "SELECT id, slug FROM manifest WHERE id = %d;", id);
  
  res = PQexec(db, lookup_query);
  
  if(PQresultStatus(res) != PGRES_TUPLES_OK)
  {