#ifndef RADIX_SORT_H
#define RADIX_SORT_H

#include <stdio.h>
#include <stdlib.h>
#include "counting_sort.h"
#include "data_structures.h"
void radixSort(int *array, int size);
void countingSortByDigit(int *array, int size, int exp);
#endif