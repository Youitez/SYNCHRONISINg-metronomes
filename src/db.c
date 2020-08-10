
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
    fprintf(stderr, "[ERROR] Failed to query PostgreSQL database.\n");
    
    return EXIT_FAILURE;
  }
  
  records = PQntuples(res);
  
  for(i=0;i<records;i++)
  { 
    for(j=0;j<2;j++)
    {
      if(j == 1)
      {
        memcpy((void*)slug, (void*)PQgetvalue(res, i, j), PQgetlength(res, i, j));
        slug[PQgetlength(res, i, j)] = '\0';
      }
    }
  }
  
  PQclear(res);
  
  return EXIT_SUCCESS;
}

// Perform lookup on manifest table to find slug from a given id
int get_name_from_id(int id, char* name)
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
  
  sprintf(lookup_query, "SELECT id, name FROM manifest WHERE id = %d;", id);
  
  res = PQexec(db, lookup_query);
  
  if(PQresultStatus(res) != PGRES_TUPLES_OK)
  {
    fprintf(stderr, "[ERROR] Failed to query PostgreSQL database.\n");
    
    return EXIT_FAILURE;
  }
  
  records = PQntuples(res);
  
  for(i=0;i<records;i++)
  { 
    for(j=0;j<2;j++)
    {
      if(j == 1)
      {
        memcpy((void*)name, (void*)PQgetvalue(res, i, j), PQgetlength(res, i, j));
        name[PQgetlength(res, i, j)] = '\0';
      }
    }
  }
  
  PQclear(res);
  
  return EXIT_SUCCESS;
}

// Perform lookup on manifest table to find slug from a given id
int get_ticker_from_id(int id, char* ticker)
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
  
  sprintf(lookup_query, "SELECT id, ticker FROM manifest WHERE id = %d;", id);
  
  res = PQexec(db, lookup_query);
  
  if(PQresultStatus(res) != PGRES_TUPLES_OK)
  {
    fprintf(stderr, "[ERROR] Failed to query PostgreSQL database.\n");
    
    return EXIT_FAILURE;
  }
  
  records = PQntuples(res);
  
  for(i=0;i<records;i++)
  { 
    for(j=0;j<2;j++)
    {
      if(j == 1)
      {
        memcpy((void*)ticker, (void*)PQgetvalue(res, i, j), PQgetlength(res, i, j));
        ticker[PQgetlength(res, i, j)] = '\0';
      }
    }
  }
  
  PQclear(res);
  
  return EXIT_SUCCESS;
}

int get_id_from_ticker(char* ticker)
{
  int i = 0;
  int j = 0;
  int records = 0;
  int id = 0;
  
  // db variables
  PGconn* db;
  PGresult* res;
  
  // strings
  char lookup_query[128];
  char* id_string;
  
  // connect to db
  db = PQconnectdb("dbname=equities user=jmcph4");
  
  if(PQstatus(db) == CONNECTION_BAD)
  {
    fprintf(stderr, "[ERROR] Failed to connect to the PostgreSQL database.\n");
    
    return EXIT_FAILURE;
  }
  
  sprintf(lookup_query, "SELECT id, ticker FROM manifest WHERE ticker = '%s';", ticker);
  
  res = PQexec(db, lookup_query);
  
  if(PQresultStatus(res) != PGRES_TUPLES_OK)
  {
    fprintf(stderr, "[ERROR] Failed to query PostgreSQL database.\n");
    
    return EXIT_FAILURE;
  }
  
  records = PQntuples(res);
  
  for(i=0;i<records;i++)
  { 
    for(j=0;j<2;j++)
    {
      if(j == 0)
      {
	id_string = malloc(PQgetlength(res, i, j) * sizeof(char));
        memcpy((void*)id_string, (void*)PQgetvalue(res, i, j), PQgetlength(res, i, j));
        id_string[PQgetlength(res, i, j)] = '\0';
      }