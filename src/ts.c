
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
    
    if(series[i] > max)
    {
      max = series[i];
    }
  }
  
  return max;
}

int get_range(int* series, int n)
{
  int range = 0;
  
  range = get_max(series, n) - get_min(series, n);
  
  return range;
}

double get_stddev(int* series, int n)
{
  int i = 0;
  double average = get_mean(series, n);
  
  int* deviations = malloc(n * sizeof(int));
  
  for(i=0;i<n;i++)
  {
    deviations[i] = abs(series[i] - average);
  }
  
  double variance = get_mean(deviations, n);
  
  double sigma = sqrt(variance);
  
  return sigma;
}
