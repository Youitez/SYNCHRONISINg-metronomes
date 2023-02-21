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
  
  printf("--- QUOTE FOR %s ---\n", ticker);
  printf("Name:         %s\n", name);
  printf("Latest Price: $%.2f\n", (float)(close[0]/100));
  printf("Mean Price:   $%.2f\n", get_mean(close, num_rows)/100);
  printf("Min. Price:   $%.2f\n", (float)get_min(close, num_rows)/100);
  printf("Max. Price:   $%.2f\n", (float)get_max(close, num_rows)/100);
  printf("Std. Dev.:    $%.2f\n", get_stddev(close, num_rows)/100);
  printf("\n\n\n");
  
  if(close[0] < get_mean(close, num_rows))
  {
    printf("Security is currently trading $%.2f below historical averages.\n", 
           (get_mean(close, num_rows)/100) - ((float)(close[0]/100)));
  }
  else if(close[0] >= get_mean(close, num_rows))
  {
    printf("Security is currently trading $%.2f above historical averages.\n", 
           (float)((close[0] - get_mean(close, num_rows))/100));
  }
  
  /***************************************************************************/
  
  free(slug);
  free(timestamp);
  free(open);
  free(high);
  free(low);
  free(close);
  free(volume);
  
  
  return EXIT_SUCCESS;
}