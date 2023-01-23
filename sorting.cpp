//
// Created by Fryderyk Kögl on 23.12.22.
//

#include "sorting.h"

#include <algorithm>

using namespace std;

// Function to partition the array on the basis of pivot element
unsigned long partition(std::vector<double> &arr, unsigned long low, unsigned long high, bool reverse = false) {
    // Select the pivot element
    double pivot = arr[high];

    // Index of the smaller element
    unsigned long i = low - 1;

    // Iterate through the array and place the elements smaller than pivot on the left
    // and elements greater than pivot on the right
    for (unsigned long j = low; j <= high - 1; j++)
    {
        if (reverse){
            if (arr.at(j) > pivot)
            {
                i++;
                swap(arr.at(i), arr.at(j));
            }
        } else {
            if (arr.at(j) < pivot)
            {
                i++;
                swap(arr.at(i), arr.at(j));
            }
        }
    }

    // Place the pivot element in the correct position
    swap(arr[i + 1], arr[high]);

    // Return the pivot index
    return i + 1;
}

// Recursive function to sort the array using quicksort
void quicksort(std::vector<double> &arr, unsigned long low, unsigned long high, bool reverse=false) {
    // Base case: Return if the array has 0 or 1 elements
    if (low >= high)
        return;

    // Partition the array around a pivot element and get the pivot index
    unsigned long pivotIndex = partition(arr, low, high, reverse);

    // Recursively sort the elements before and after the pivot element
    quicksort(arr, low, pivotIndex - 1, reverse);
    quicksort(arr, pivotIndex + 1, high, reverse);
}
