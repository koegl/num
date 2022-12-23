//
// Created by Fryderyk Kögl on 23.12.22.
//

#include "sorting.h"

#include <iostream>
#include <algorithm>

using namespace std;

// Function to partition the array on the basis of pivot element
int partition(double* arr, int low, int high, bool reverse = false) {
    // Select the pivot element
    double pivot = arr[high];

    // Index of the smaller element
    int i = low - 1;

    // Iterate through the array and place the elements smaller than pivot on the left
    // and elements greater than pivot on the right
    for (int j = low; j <= high - 1; j++)
    {
        if (reverse){
            if (arr[j] > pivot)
            {
                i++;
                swap(arr[i], arr[j]);
            }
        } else {
            if (arr[j] < pivot)
            {
                i++;
                swap(arr[i], arr[j]);
            }
        }
    }

    // Place the pivot element in the correct position
    swap(arr[i + 1], arr[high]);

    // Return the pivot index
    return i + 1;
}

// Recursive function to sort the array using quicksort
void quicksort(double* arr, int low, int high, bool reverse = false) {
    // Base case: Return if the array has 0 or 1 elements
    if (low >= high)
        return;

    // Partition the array around a pivot element and get the pivot index
    int pivotIndex = partition(arr, low, high, reverse);

    // Recursively sort the elements before and after the pivot element
    quicksort(arr, low, pivotIndex - 1, reverse);
    quicksort(arr, pivotIndex + 1, high, reverse);
}

//int main() {
//    int arr[] = { 5, 4, 3, 2, 1 };
//    int n = sizeof(arr) / sizeof(arr[0]);
//
//    quicksort(arr, 0, n - 1);
//
//    // Print the sorted array
//    for (int i = 0; i < n; i++)
//        cout << arr[i] << " ";
//
//    return 0;
//}
