//
// Created by Fryderyk Kögl on 23.12.22.
//

#include <list>
#include <stdexcept>
#include <iostream>
#include <limits>
#include <vector>
#include <sstream>
#include <iomanip>
#include <string>

#include "sorting.h"

class Array {
public:
    // todo add shape

    // CONSTRUCTORS
    Array() {
        rows_v = 0;
        columns_v = 0;
        data = nullptr;
        dtype_value = "None";
    }


    Array(const std::list<std::list<double>> & myArguments) {

        rows_v = myArguments.size();
        columns_v = myArguments.front().size();

        int current = columns_v;

        // check if all rows have the same length
        auto it = myArguments.begin();
        for (int i = 0; i < rows_v; i++) {

            if ((*it).size() != current) {
                throw std::invalid_argument("All rows must have the same length");
            }
            it++;
        }

        // Allocate memory for the rows of the array
        Array::allocate_data(&data, rows_v, columns_v);

        auto it_rows = myArguments.begin();
        for (int i = 0; i < rows_v; i++) {

            auto it_cols = (*it_rows).begin();

            for (int j = 0; j < columns_v; j++) {
                data[i][j] = *it_cols;
                it_cols++;
            }
            it_rows++;
        }

        dtype_value = "float64";
    }

    Array(const Array & other) {

        rows_v = other.rows_v;
        columns_v = other.columns_v;
        dtype_value = other.dtype_value;

        // Allocate memory for the rows of the array
        Array::allocate_data(&data, rows_v, columns_v);

        for (int i = 0; i < rows_v; i++) {
            for (int j = 0; j < columns_v; j++) {
                data[i][j] = other.data[i][j];
            }
        }
    }

    explicit Array(const std::list<double> & myArguments){
        rows_v = myArguments.size();
        columns_v = 1;

        // Allocate memory for the rows of the array
        Array::allocate_data(&data, rows_v, columns_v);

        auto it_rows = myArguments.begin();
        for (int i = 0; i < rows_v; i++) {
            data[i][0] = *it_rows;
            it_rows++;
        }

        dtype_value = "float64";
    }

    Array(double **new_data, int rows, int columns, const std::string& dtype="float64") {
        data = new_data;

        rows_v = rows;
        columns_v = columns;

        dtype_value = dtype;
    }

    // OPERATORS
    // add
    Array operator+(const Array & other) const {

        if (rows_v != other.rows() || columns_v != other.columns()) {
            throw std::invalid_argument("Arrays must have the same size to perform addition (+).\nError in line " + std::to_string(__LINE__));
        }

        std::list<std::list<double>> result_data = {};

        for (int i = 0; i < rows_v; i++) {
            std::list<double> row = {};
            for (int j = 0; j < columns_v; j++) {
                row.push_back(data[i][j] + other.data[i][j]);
            }
            result_data.push_back(row);
        }


        Array result = Array(result_data);

        return result;
    }

    // subtract
    Array operator-(const Array & other) const {

        if (rows_v != other.rows() || columns_v != other.columns()) {
            throw std::invalid_argument("Arrays must have the same size to perform subtraction (-).\nError in line " + std::to_string(__LINE__));
        }

        std::list<std::list<double>> result_data = {};

        for (int i = 0; i < rows_v; i++) {
            std::list<double> row = {};
            for (int j = 0; j < columns_v; j++) {
                row.push_back(data[i][j] - other.data[i][j]);
            }
            result_data.push_back(row);
        }

        Array result = Array(result_data);

        return result;
    }

    // multiply element-wise
    Array operator*(const Array & other) const {

        if (rows_v != other.rows() || columns_v != other.columns()) {
            throw std::invalid_argument("Arrays must have the same size to perform elementwise multiplication (*).\nError in line " + std::to_string(__LINE__));
        }

        std::list<std::list<double>> result_data = {};

        for (int i = 0; i < rows_v; i++) {
            std::list<double> row = {};
            for (int j = 0; j < columns_v; j++) {
                row.push_back(data[i][j] * other.data[i][j]);
            }
            result_data.push_back(row);
        }


        Array result = Array(result_data);

        return result;
    }

    // divide element-wise
    Array operator/(const Array & other) const {

        if (rows_v != other.rows() || columns_v != other.columns()) {
            throw std::invalid_argument("Arrays must have the same size to perform addition (+).\nError in line " + std::to_string(__LINE__));
        }

        std::list<std::list<double>> result_data = {};

        for (int i = 0; i < rows_v; i++) {
            std::list<double> row = {};
            for (int j = 0; j < columns_v; j++) {

                double divisor = other.data[i][j];

                if (divisor == 0){

                    std::string text = "Error in line " + std::to_string(__LINE__) + "." +
                                       " Cannot divide by zero at index " + std::to_string(i) + "." +
                                       " Setting result to infinity (" + std::to_string(std::numeric_limits<double>::infinity()) + ").";
                    row.push_back(std::numeric_limits<double>::infinity());
                    std::cout << text << std::endl;
                    continue;
                }

                row.push_back(data[i][j] / other.data[i][j]);
            }
            result_data.push_back(row);
        }


        Array result = Array(result_data);

        return result;
    }

    // access
    double* operator[](std::size_t row) const{

        checkIndex(row, 0);

        return data[row];
    }

    // assignment operator
    Array& operator=(const Array & other) {

        if (this != &other) {

            // Copy data
            rows_v = other.rows();
            columns_v = other.columns();

            Array::delete_data(data, rows_v);

            // Allocate memory for the rows of the array
            Array::allocate_data(&data, rows_v, columns_v);

            for (int i = 0; i < rows_v; i++) {
                for (int j = 0; j < columns_v; j++) {
                    data[i][j] = other.data[i][j];
                }
            }

            dtype_value = other.dtype();
        }

        return *this;
    }

    void checkIndex(std::size_t row, std::size_t col) const {

        if (row < 0 || col < 0) {
            throw std::out_of_range("Index must be positive");
        }

        if (row >= rows_v || col >= columns_v) {
            std::string text = "Index out of range. Maximal row index index is " + std::to_string(row - 1) +
                               " and maximal column index is " + std::to_string(col - 1);

            throw std::out_of_range(text);
        }
    }

    // DESTRUCTOR
    ~Array(){
        delete_data(data, rows_v);
    }

    // todo when the array is 1x1 print without brackets, same for 1d (only one bracket)
    void print() const {

        std::vector<std::string> output;
        std::string row;

        row += "[";

        for (int i = 0; i < rows_v; i++) {

            if (i == 0) {
                row += "[";
            }
            else {
                row += " [";
            }

            for (int j = 0; j < columns_v-1; j++) {

                std::ostringstream oss;
                oss << std::setprecision(8) << std::noshowpoint << data[i][j];

                row += oss.str();
                row += ", ";
            }

            std::ostringstream oss;
            oss << std::setprecision(15) << std::noshowpoint << data[i][columns_v-1];

            row += oss.str();
            row += "]";

            if (i != rows_v-1) {
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

/*
    // METHODS
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
*/
    int rows() const {
        return rows_v;
    }
    int columns() const {
        return columns_v;
    }

    double max() const{
        double max = data[0][0];

        for (int i = 0; i < rows_v; i++){
            for (int j = 0; j < columns_v; j++){
                if (data[i][j] > max){
                    max = data[i][j];
                }
            }
        }

        return max;
    }

    std::vector<int> argmax() const{
        double max = data[0][0];
        std::vector<int> indices = {0, 0};

        for (int i = 0; i < rows_v; i++){
            for (int j = 0; j < columns_v; j++){
                if (data[i][j] > max){
                    max = data[i][j];
                    indices[0] = i;
                    indices[1] = j;
                }
            }
        }

        return indices;
    }

    double min() const{
        double min = data[0][0];

        for (int i = 0; i < rows_v; i++){
            for (int j = 0; j < columns_v; j++){
                if (data[i][j] < min){
                    min = data[i][j];
                }
            }
        }

        return min;
    }

    std::vector<int> argmin() const{
        double min = data[0][0];
        std::vector<int> indices = {0, 0};

        for (int i = 0; i < rows_v; i++){
            for (int j = 0; j < columns_v; j++){
                if (data[i][j] < min){
                    min = data[i][j];
                    indices[0] = i;
                    indices[1] = j;
                }
            }
        }

        return indices;
    }

    Array sum() const {
        double **result_data;

        Array::allocate_data(&result_data, 1, 1);

        result_data[0][0] = 0;

        for (int i = 0; i < rows_v; i++){
            for (int j = 0; j < columns_v; j++){
                result_data[0][0] += data[i][j];
            }
        }

        Array result = Array(result_data, 1,1);

        return result;
    }

    Array sum(int axis) const {
        if (axis == 0){
            return sum_rows();
        }
        else if (axis == 1){
            return sum_columns();
        }
        else {
            throw std::invalid_argument("Axis must be 0 or 1");
        }
    }

    void transpose() {
        double **result;
        allocate_data(&result, columns_v, rows_v);

        for (int i = 0; i < rows_v; i++) {
            for (int j = 0; j < columns_v; j++) {
                result[j][i] = data[i][j];
            }
        }

        int temp = rows_v;
        rows_v = columns_v;
        columns_v = temp;

        Array::delete_data(data, columns_v);

        data = result;
    }

    static Array mult(const Array &a1, const Array &a2){

        if (a1.rows() != a2.columns() || a1.columns() != a2.rows()){
            throw std::invalid_argument("Incompatible array shapes");
        }

        // Allocate memory for the rows of the array
        double **result;
        allocate_data(&result, a1.rows(), a2.columns());

        double sum = 0;

        for (int i = 0; i < a1.rows(); i++){
            for (int j = 0; j < a2.columns(); j++){
                for (int k = 0; k < a1.columns(); k++){
                    sum += a1.data[i][k] * a2.data[k][j];
                }
                result[i][j] = sum;
                sum = 0;
            }
        }

        return Array(result, a1.rows(), a2.columns());
    }

    // identity
    static Array eye(int n) {

        double **result;

        Array::allocate_data(&result, n, n);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    result[i][j] = 1;
                }
                else {
                    result[i][j] = 0;
                }
            }
        }

        return Array(result, n, n);
    }

    void inverse() {

        int n = rows();

        if (n != columns()){
            throw std::invalid_argument("Matrix must be square");
        }

        double** result;
        allocate_data(&result, n, n);

        double** temp;
        allocate_data(&temp, n, n);

        double** identity;
        allocate_data(&identity, n, n);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    identity[i][j] = 1;
                }
                else {
                    identity[i][j] = 0;
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                temp[i][j] = data[i][j];
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                result[i][j] = identity[i][j];
            }
        }

        for (int i = 0; i < n; i++) {

            double pivot = temp[i][i];
            for (int j = 0; j < n; j++) {
                temp[i][j] /= pivot;
                result[i][j] /= pivot;
            }

            for (int j = 0; j < n; j++) {
                if (j != i) {
                    double factor = temp[j][i];
                    for (int k = 0; k < n; k++) {
                        temp[j][k] -= factor * temp[i][k];
                        result[j][k] -= factor * result[i][k];
                    }
                }
            }
        }

    data = result;
    }

    std::string dtype() const{
        return dtype_value;
    }

    double **data;

private:

    std::string dtype_value;
    int rows_v;
    int columns_v;

    static void allocate_data(double ***data_array, int rows, int columns) {
        *data_array = new double*[rows];
        for (int i = 0; i < rows; i++) {
            (*data_array)[i] = new double[columns];
        }
    }

    static void delete_data(double** data_to_delete, int n_rows){
        for (int i = 0; i < n_rows; i++){
            delete[] data_to_delete[i];
        }
        delete[] data_to_delete;
    }

    // sum along rows
    Array sum_rows() const{

        // Allocate memory for the rows of the array
        double **result_data;

        Array::allocate_data(&result_data, rows_v, 1);

        for (int i = 0; i < rows_v; i++){
            double sum = 0;
            for (int j = 0; j < columns_v; j++){
                sum += data[i][j];
            }
            result_data[i][0] = sum;
        }

        Array result = Array(result_data, rows_v, 1);


        return result;
    }

    Array sum_columns() const{

        // Allocate memory for the rows of the array
        double **result_data;

        Array::allocate_data(&result_data, 1, columns_v);

        for (int i = 0; i < columns_v; i++){
            double sum = 0;
            for (int j = 0; j < rows_v; j++){
                sum += data[j][i];
            }
            result_data[0][i] = sum;
        }

        Array result = Array(result_data, 1, columns_v);

        return result;
    }

};

namespace {
    void print(const Array &myArray);

    void print(const Array &myArray) {

        std::cout << "Array([";
        for (int i = 0; i < myArray.rows(); i++) {
            std::cout << myArray.data[i];
            if (i != myArray.columns() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "])" << std::endl;
    }

    // multiply by scalar
    Array operator*(const Array other, const double &factor) {

        std::list<std::list<double>> result_data = {};

        for (int i = 0; i < other.rows(); i++) {
            std::list<double> row = {};
            for (int j = 0; j < other.columns(); j++) {
                row.push_back(other.data[i][j] * factor);
            }
            result_data.push_back(row);
        }

        Array result = Array(result_data);

        return result;
    }
    Array operator*(const double &factor, const Array other) {

        std::list<std::list<double>> result_data = {};

        for (int i = 0; i < other.rows(); i++) {
            std::list<double> row = {};
            for (int j = 0; j < other.columns(); j++) {
                row.push_back(other.data[i][j] * factor);
            }
            result_data.push_back(row);
        }

        Array result = Array(result_data);

        return result;
    }
}


