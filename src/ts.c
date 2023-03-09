
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
  
  for(i=0;i<n;i++)
  {
    if(i == 0)
    {
      min = series[i];
    }
    
    if(series[i] < min)
    {
      min = series[i];
    }
  }
  
  return min;
}

int get_max(int* series, int n)
{
  int i = 0;
  int max = 0;
  
  for(i=0;i<n;i++)
  {
    if(i == 0)
    {
      max = series[i];
    }
    