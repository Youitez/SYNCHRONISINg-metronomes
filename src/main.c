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
  
  /*********************************************************