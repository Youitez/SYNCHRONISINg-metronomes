
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
    }
  }
  
  id = atoi(id_string);
  
  PQclear(res);
  
  free(id_string);
  
  return id;
}

// Retrieve a security by id
int load_ts(int id, long long** timestamp, int** open, int** high, int** low, int** close, int** volume)
{
  int i = 0;
  int j = 0;
  int records = 0;
  
  // db variables
  PGconn* db;
  PGresult* res;
  
  // strings
  char slug[128];
  char series_query[128];
  
  // connect to db
  db = PQconnectdb("dbname=equities user=jmcph4");
  
  if(PQstatus(db) == CONNECTION_BAD)
  {
    fprintf(stderr, "[ERROR] Failed to connect to the PostgreSQL database.\n");
    
    return EXIT_FAILURE;
  }
  
  get_slug_from_id(id, slug);
  
  // query appropriate table for time series data
  
  sprintf(series_query, "SELECT extract(epoch from timestamp), open, high, low, close, volume FROM %s;", slug);
  
  res = PQexec(db, series_query);
  
  if(PQresultStatus(res) != PGRES_TUPLES_OK)
  {
    fprintf(stderr, "[ERROR] Failed to query PostgreSQL database.\n");
    
    return EXIT_FAILURE;
  }
  
  records = PQntuples(res);
  
  // allocate memory for arrays
  
  *timestamp = malloc(records * sizeof(long long));
  
  if(*timestamp == NULL)
  {
    fprintf(stderr, "[ERROR] Failed to allocate memory.\n");
    
    return EXIT_FAILURE;
  }
  
  *open = malloc(records * sizeof(int));
  
  if(*open == NULL)
  {
    fprintf(stderr, "[ERROR] Failed to allocate memory.\n");
    
    return EXIT_FAILURE;
  }
  
  *high = malloc(records * sizeof(int));
  
  if(*high == NULL)
  {
    fprintf(stderr, "[ERROR] Failed to allocate memory.\n");
    
    return EXIT_FAILURE;
  }
  
  *low = malloc(records * sizeof(int));
  
  if(*low == NULL)
  {
    fprintf(stderr, "[ERROR] Failed to allocate memory.\n");
    
    return EXIT_FAILURE;
  }
  
  *close = malloc(records * sizeof(int));
  
  if(*close == NULL)
  {
    fprintf(stderr, "[ERROR] Failed to allocate memory.\n");
    
    return EXIT_FAILURE;
  }
  
  *volume = malloc(records * sizeof(int));
  
  if(*volume == NULL)
  {
    fprintf(stderr, "[ERROR] Failed to allocate memory.\n");
    
    return EXIT_FAILURE;
  }
  
  // handle results
  
  for(i=0;i<records;i++)
  {
    for(j=0;j<6;j++)
    {      
      switch(j)
      {
        case 0:
          timestamp[0][i] = atol(PQgetvalue(res, i, j));
          break;
        case 1:
          open[0][i] = atoi(PQgetvalue(res, i, j));
          break;
        case 2:
          high[0][i] = atoi(PQgetvalue(res, i, j));
	  break;
        case 3:
          low[0][i] = atoi(PQgetvalue(res, i, j));
          break;
        case 4:
          close[0][i] = atoi(PQgetvalue(res, i, j));
          break;
        case 5:
          volume[0][i] = atoi(PQgetvalue(res, i, j));
          break;
      }
      
    }
  }
  
  // clean up
  
  PQclear(res);
  PQfinish(db);
  
  return EXIT_SUCCESS;
}

int get_row_count_from_slug(char* slug)
{
  int i = 0;
  int j = 0;
  int records = 0;
  int count = 0;
  
  // db variables
  PGconn* db;
  PGresult* res;
  
  // strings
  char lookup_query[128];
  char* count_string;
  
  // connect to db
  db = PQconnectdb("dbname=equities user=jmcph4");
  
  if(PQstatus(db) == CONNECTION_BAD)
  {
    fprintf(stderr, "[ERROR] Failed to connect to the PostgreSQL database.\n");
    
    return EXIT_FAILURE;
  }
  
  sprintf(lookup_query, "SELECT COUNT(*) FROM %s;", slug);
  
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
        count_string = malloc(PQgetlength(res, i, j) * sizeof(char));
        memcpy((void*)count_string, (void*)PQgetvalue(res, i, j), PQgetlength(res, i, j));
        count_string[PQgetlength(res, i, j)] = '\0';
      }
    }
  }
  
  count = atoi(count_string);
  
  free(count_string);
  
  return count;
}