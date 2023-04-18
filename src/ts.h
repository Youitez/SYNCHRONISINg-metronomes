
#ifndef TS_H_
#define TS_H_

#include <stdio.h>
#include <stdlib.h>

// descriptive statistics and measures of central tendency
double get_mean(int* series, int n);
int get_median(int* series, int n);
int get_mode(int* series, int n);
int get_min(int* series, int n);
int get_max(int* series, int n);
int get_range(int* series, int n);
double get_stddev(int* series, int n);

// time series functions