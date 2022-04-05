#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libpq-fe.h>

#include "db.h"
#include "ts.h"

#define TOTAL 7394

int main(int argc, char** argv)
{
  if(argc != 2)
  {
    printf("Usage: %s ticker\n", argv[0]);
    
    return EXIT_SUCCESS;
  }
  
  int res = 0;
  int num_rows = 0;
  
  long long* timestamp;
  int* open;
  int* high;
  int* low;
  int* close;
  int* volume;
  char name[128];
  char ticker[128];
  int id = 0;
  char* slug = malloc(64 * sizeof(char));
  
  /***************************************************************************/
  
  id = get_id_from_ticker(argv[1]);
  get_slug_from_id(id, slug);
  num_rows = get_row_count_from_slug(slug);
  
  res = load_ts(id, &timestamp, &open, &high, &low, 
                &close, &volume);
  
  if(res == EXIT_FAILURE)
  {
    return EXIT_FAILURE;
  }
  
  get_name_from_id(id, name);
  get_ticker_from_id(id, ticker);
  
  printf("--- QUOTE FOR %s --