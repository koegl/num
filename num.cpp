//
// Created by Fryderyk Kögl on 23.12.22.
//

#include <list>
#include <stdexcept>
#include <iostream>
#include <limits>

#include "sorting.h"


class Array {
public:

    // CONSTRUCTORS
    Array() {
        length_of_array = 0;
        data = nullptr;
        dtype_value = "None";
    }

    explicit Array(const std::list<double> & myArguments) {

        length_of_array = myArguments.size();
        data = new double[length_of_array];

        length_of_array = myArguments.size();
        data = new double[length_of_array];

        auto it = myArguments.begin();

        for (int i = 0; i < length_of_array; i++) {
            data[i] = *it;
            it++;
        }

        dtype_value = "float64";
    }


    // OPERATORS
    // add
    Array operator+(const Array & other) const {

        if (length_of_array != other.length()){
            throw std::invalid_argument("Arrays must have the same length to perform addition (+).\nError in line " + std::to_string(__LINE__));
        }

        std::list<double> result_data = {};

        for (int i = 0; i < length_of_array; i++) {
            result_data.push_back(data[i] + other.data[i]);

        }

        Array result = Array(result_data);

        return result;
    }

    // subtract
    Array operator-(const Array & other) const {

        if (length_of_array != other.length()){
            throw std::invalid_argument("Arrays must have the same length to perform addition (+).\nError in line " + std::to_string(__LINE__));
        }

        std::list<double> result_data = {};

        for (int i = 0; i < length_of_array; i++) {
            result_data.push_back(data[i] - other.data[i]);

        }

        Array result = Array(result_data);

        return result;
    }

    // multiply element-wise
    Array operator*(const Array & other) const{

        if (length_of_array != other.length()){
            throw std::invalid_argument("Arrays must have the same length to perform addition (+).\nError in line " + std::to_string(__LINE__));
        }

        std::list<double> result_data = {};

        for (int i = 0; i < length_of_array; i++) {
            result_data.push_back(data[i] * other.data[i]);
        }

        Array result = Array(result_data);

        return result;
    }

    // divide element-wise
    Array operator/(const Array & other) const{

        if (length_of_array != other.length()){
            throw std::invalid_argument("Arrays must have the same length to perform addition (+).\nError in line " + std::to_string(__LINE__));
        }

        std::list<double> result_data = {};

        for (int i = 0; i < length_of_array; i++) {

            double divisor = other.data[i];

            if (divisor == 0){

                std::string text = "Error in line " + std::to_string(__LINE__) + "." +
                                   " Cannot divide by zero at index " + std::to_string(i) + "." +
                                   " Setting result to infinity (" + std::to_string(std::numeric_limits<double>::infinity()) + ").";
                result_data.push_back(std::numeric_limits<double>::infinity());
                std::cout << text << std::endl;
                continue;
            }

            result_data.push_back(data[i] / other.data[i]);
        }

        Array result = Array(result_data);

        return result;
    }

    // access
    double &operator[] (int idx) const{
        if (idx < 0) {
            throw std::out_of_range("Index must be positive");
        }
        else if (idx >= length_of_array) {
            throw std::out_of_range("Index too big. Maximal index is " + std::to_string(length_of_array - 1));
        }

        return data[idx];
    }


    // DESTRUCTOR
    ~Array(){
        delete[] data;
    }


    // METHODS
    void print() const {
        std::cout <<"Array([";

        for (int i = 0; i < length_of_array - 1; i++) {
            std::cout << data[i] << ", ";
        }

        std::cout << data[length_of_array - 1] << ")]" << std::endl;
    }

    void append(double new_value) {

        // create new array with one more element
        auto *new_data = new double[length_of_array + 1];

        // copy old data to new array
        for (int i = 0; i < length_of_array; i++) {
            new_data[i] = data[i];
        }

        // add new value to the end of the array
        new_data[length_of_array] = new_value;

        // delete old array
        delete[] data;

        // set new array as data
        data = new_data;

        // increase length of array
        length_of_array++;
    }

    double pop(int idx) {

        if (idx < 0) {
            throw std::out_of_range("Index must be positive");
        }
        else if (idx >= length_of_array) {
            throw std::out_of_range("Index too big. Maximal index is " + std::to_string(length_of_array - 1));
        }

        double popped_value = data[idx];

        // create new array with one less element
        auto *new_data = new double[length_of_array - 1];

        // copy old data to new array
        for (int i = 0; i < idx; i++) {
            new_data[i] = data[i];
        }

        for (int i = idx; i < length_of_array - 1; i++) {
            new_data[i] = data[i + 1];
        }

        // delete old array
        delete[] data;

        // set new array as data
        data = new_data;

        // decrease length of array
        length_of_array--;

        return popped_value;
    }

    void sort(bool reverse = false){
        // quicksort
        quicksort(data, 0, length_of_array - 1, reverse);
    }

    Array nonzero() const {
        std::list<double> result_data = {};

        for (int i = 0; i < length_of_array; i++) {
            if (data[i] != 0){
                result_data.push_back(data[i]);
            }
        }

        Array result = Array(result_data);

        return result;
    }

    Array cumsum() const {
        std::list<double> result_data = {};

        double sum = 0;

        for (int i = 0; i < length_of_array; i++) {
            sum += data[i];
            result_data.push_back(sum);
        }

        Array result = Array(result_data);

        return result;
    }

    Array cumprod() const {
        std::list<double> result_data = {};

        double product = 1;

        for (int i = 0; i < length_of_array; i++) {
            product *= data[i];
            result_data.push_back(product);
        }

        Array result = Array(result_data);

        return result;
    }

    int length() const {
        return length_of_array;
    }

    double max() const{
        double max = data[0];

        for (int i = 0; i < length_of_array; i++){
            if (data[i] > max) {
                max = data[i];
            }
        }

        return max;
    }
    int argmax() const{
        double max = data[0];
        int argmax = 0;

        for (int i = 0; i < length_of_array; i++){
            if (data[i] > max) {
                max = data[i];
                argmax = i;
            }
        }

        return argmax;
    }

    double min() const{
        double min = data[0];

        for (int i = 0; i < length_of_array; i++){
            if (data[i] < min) {
                min = data[i];
            }
        }

        return min;
    }
    int argmin() const{
        double min = data[0];
        int argmin = 0;

        for (int i = 0; i < length_of_array; i++){
            if (data[i] < min) {
                min = data[i];
                argmin = i;
            }
        }

        return argmin;
    }

    double sum() const{
        double sum = 0;

        for (int i = 0; i < length_of_array; i++){
            sum += data[i];
        }

        return sum;
    }
    std::string dtype() const{
        return dtype_value;
    }

private:
    double *data;
    std::string dtype_value;
    int length_of_array;

};

namespace {
    void print(const Array &myArray);


    void print(const Array &myArray) {



        std::cout << "Array([";
        for (int i = 0; i < myArray.length(); i++) {
            std::cout << myArray[i];
            if (i != myArray.length() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "])" << std::endl;
    }
}


