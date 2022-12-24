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

    explicit Array(const std::list<std::list<double>> & myArguments) {

        rows = myArguments.size();
        columns = myArguments.front().size();

        int current = columns;

        // check if all rows have the same length
        auto it = myArguments.begin();
        for (int i = 0; i < rows; i++) {

            std::cout << (*it).size() << std::endl;

            if ((*it).size() != current) {
                throw std::invalid_argument("All rows must have the same length");
            }


            it++;
        }

        // Allocate memory for the rows of the array
        data = new double* [rows];

        // Allocate memory for the columns of the array
        for (int i = 0; i < rows; i++)
            data[i] = new double[columns];

        auto it_rows = myArguments.begin();
        for (int i = 0; i < rows; i++) {

            auto it_cols = (*it_rows).begin();

            for (int j = 0; j < columns; j++) {
                data[i][j] = *it_cols;
                it_cols++;
            }
            it_rows++;
        }

        dtype_value = "float64";
    }


    // OPERATORS
    // add
//    Array operator+(const Array & other) const {
//
//        if (length_of_array != other.length()){
//            throw std::invalid_argument("Arrays must have the same length to perform addition (+).\nError in line " + std::to_string(__LINE__));
//        }
//
//        std::list<double> result_data = {};
//
//        for (int i = 0; i < length_of_array; i++) {
//            result_data.push_back(data[i] + other.data[i]);
//
//        }
//
//        Array result = Array(result_data);
//
//        return result;
//    }

    /*
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
    */

    // DESTRUCTOR
    ~Array(){
        for (int i = 0; i < rows; i++)
            delete[] data[i];
        delete[] data;
    }

    void print() const {

        std::vector<std::string> output;
        std::string row;

        row += "[";

        for (int i = 0; i < rows; i++) {

            if (i == 0) {
                row += "[";
            }
            else {
                row += " [";
            }

            for (int j = 0; j < columns-1; j++) {

                std::ostringstream oss;
                oss << std::setprecision(8) << std::noshowpoint << data[i][j];

                row += oss.str();
                row += ", ";
            }

            std::ostringstream oss;
            oss << std::setprecision(15) << std::noshowpoint << data[i][columns-1];

            row += oss.str();
            row += "]";

            if (i != rows-1) {
                row +=  ",";
            }
            else {
                row += "]";
            }

            output.push_back(row);
            row = "";

        }

        for (auto & i : output) {
            std::cout << i << std::endl;
        }
    }
//        std::cout <<"[";
//
//        for (int i = 0; i < rows; i++) {
//
//            if (i == 0) {
//                std::cout << "[";
//            }
//            else {
//                std::cout << " [";
//            }
//
//            for (int j = 0; j < columns-1; j++) {
//
//                std::cout << data[i][j] << ", ";
//            }
//            std::cout <<data[i][columns-1] << "]";
//
//            if (i != rows-1) {
//                std::cout << "," << std::endl;
//            }
//            else {
//                std::cout << "]" << std::endl;
//            }
//        }
//    }

//    // METHODS
//    void print() const {
//        std::cout <<"[";
//
//        for (int i = 0; i < length_of_array - 1; i++) {
//            std::cout << data[i] << ", ";
//        }
//
//        std::cout << data[length_of_array - 1] << "]" << std::endl;
//    }
//
//    void append(double new_value) {
//
//        // create new array with one more element
//        auto *new_data = new double[length_of_array + 1];
//
//        // copy old data to new array
//        for (int i = 0; i < length_of_array; i++) {
//            new_data[i] = data[i];
//        }
//
//        // add new value to the end of the array
//        new_data[length_of_array] = new_value;
//
//        // delete old array
//        delete[] data;
//
//        // set new array as data
//        data = new_data;
//
//        // increase length of array
//        length_of_array++;
//    }
//
//    double pop(int idx) {
//
//        if (idx < 0) {
//            throw std::out_of_range("Index must be positive");
//        }
//        else if (idx >= length_of_array) {
//            throw std::out_of_range("Index too big. Maximal index is " + std::to_string(length_of_array - 1));
//        }
//
//        double popped_value = data[idx];
//
//        // create new array with one less element
//        auto *new_data = new double[length_of_array - 1];
//
//        // copy old data to new array
//        for (int i = 0; i < idx; i++) {
//            new_data[i] = data[i];
//        }
//
//        for (int i = idx; i < length_of_array - 1; i++) {
//            new_data[i] = data[i + 1];
//        }
//
//        // delete old array
//        delete[] data;
//
//        // set new array as data
//        data = new_data;
//
//        // decrease length of array
//        length_of_array--;
//
//        return popped_value;
//    }
//
//    void sort(bool reverse = false){
//        // quicksort
//        quicksort(data, 0, length_of_array - 1, reverse);
//    }
//
//    Array nonzero() const {
//        std::list<double> result_data = {};
//
//        for (int i = 0; i < length_of_array; i++) {
//            if (data[i] != 0){
//                result_data.push_back(data[i]);
//            }
//        }
//
//        Array result = Array(result_data);
//
//        return result;
//    }
//
//    Array cumsum() const {
//        std::list<double> result_data = {};
//
//        double sum = 0;
//
//        for (int i = 0; i < length_of_array; i++) {
//            sum += data[i];
//            result_data.push_back(sum);
//        }
//
//        Array result = Array(result_data);
//
//        return result;
//    }
//
//    Array cumprod() const {
//        std::list<double> result_data = {};
//
//        double product = 1;
//
//        for (int i = 0; i < length_of_array; i++) {
//            product *= data[i];
//            result_data.push_back(product);
//        }
//
//        Array result = Array(result_data);
//
//        return result;
//    }
//
//    int length() const {
//        return length_of_array;
//    }
//
//    double max() const{
//        double max = data[0];
//
//        for (int i = 0; i < length_of_array; i++){
//            if (data[i] > max) {
//                max = data[i];
//            }
//        }
//
//        return max;
//    }
//    int argmax() const{
//        double max = data[0];
//        int argmax = 0;
//
//        for (int i = 0; i < length_of_array; i++){
//            if (data[i] > max) {
//                max = data[i];
//                argmax = i;
//            }
//        }
//
//        return argmax;
//    }
//
//    double min() const{
//        double min = data[0];
//
//        for (int i = 0; i < length_of_array; i++){
//            if (data[i] < min) {
//                min = data[i];
//            }
//        }
//
//        return min;
//    }
//    int argmin() const{
//        double min = data[0];
//        int argmin = 0;
//
//        for (int i = 0; i < length_of_array; i++){
//            if (data[i] < min) {
//                min = data[i];
//                argmin = i;
//            }
//        }
//
//        return argmin;
//    }
//
//    double sum() const{
//        double sum = 0;
//
//        for (int i = 0; i < length_of_array; i++){
//            sum += data[i];
//        }
//
//        return sum;
//    }
    std::string dtype() const{
        return dtype_value;
    }

    // 2d pointer data
    double **data;
    int rows;
    int columns;
private:


    std::string dtype_value;
    int length_of_array;


};

namespace {
    void print(const Array &myArray);


    void print(const Array &myArray) {

        std::cout << "Array([";
        for (int i = 0; i < myArray.rows; i++) {
            std::cout << myArray.data[i];
            if (i != myArray.columns - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "])" << std::endl;
    }
}


