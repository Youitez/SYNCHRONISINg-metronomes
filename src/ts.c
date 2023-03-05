
#include <string.h>
#include <math.h>

#include "ts.h"

double get_mean(int* series, int n)
{
  int i = 0;
  int sum = 0;
  double mean = 0.0;

  for(i=0;i<n;i++)
  {
    sum += series[i];
  }
  
  mean = sum / n;
  
  return mean;
}

int get_min(int* series, int n)
{
  int i = 0;
  int min = 0;
  