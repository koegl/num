//
// Created by Fryderyk Kögl on 23.12.22.
//

#ifndef NUMPY_CPP_SORTING_H
#define NUMPY_CPP_SORTING_H

#include <vector>

unsigned long partition(std::vector<double> &arr, unsigned long low, unsigned long high, bool reverse);
void quicksort(std::vector<double> &arr, unsigned long low, unsigned long high, bool reverse);

#endif //NUMPY_CPP_SORTING_H
