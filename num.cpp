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

#include "num.h"


// CONSTRUCTORS
Array::Array() {
    rows_v = 0;
    columns_v = 0;
    // intialize the data vector to an empty vector
    data = {{}};
    dtype = "None";
    // initialize vector dimensions
    dimensions = {0};
}

Array::Array(std::string input) {

    data = parse_input(input);
    rows_v = data.size();
    columns_v = data.at(0).size();
    dimensions = {rows_v, columns_v};
    dtype = "int";
}

Array::Array(const char input[]) : Array(std::string(input)) {
}

Array::Array(const Array &other) {

    rows_v = other.rows_v;
    columns_v = other.columns_v;
    dimensions = other.dimensions;
    dtype = other.dtype;

    for (const auto& row: other.data) {
        data.push_back(row);
    }
}

Array::Array(int **new_data, int rows, int columns, const std::string& new_dtype) {

    rows_v = rows;
    columns_v = columns;
    dimensions = {rows_v, columns_v};
    dtype = new_dtype;

    for (int i = 0; i < rows_v; i++) {
        std::vector<double> row;
        row.reserve(columns_v);

        for (int j = 0; j < columns_v; j++) {
            row.push_back(new_data[i][j]);
        }
        data.push_back(row);
    }
}

Array::Array(const std::vector<std::vector<double>>& new_data, const std::string &new_dtype) {

    rows_v = new_data.size();
    columns_v = new_data.at(0).size();
    dimensions = {rows_v, columns_v};
    dtype = new_dtype;

    for (const auto& row: new_data) {
        data.push_back(row);
    }
}

Array::Array(const std::vector<double> &new_data, int axis, const std::string &new_dtype) {

    if (axis == 1){
        rows_v = 1;
        columns_v = new_data.size();
    }
    else if (axis == 0) {
        rows_v = new_data.size();
        columns_v = 1;
    }
    else {
        throw std::invalid_argument("Axis must be 0 or 1.\nError in line " + std::to_string(__LINE__));
    }

    dimensions = {rows_v, columns_v};
    dtype = new_dtype;

    if (axis == 1) {
        data.push_back(new_data);
    }
    else if (axis == 0) {
        for (const auto& element: new_data) {
            data.push_back({element});
        }
    }
    else {
        throw std::invalid_argument("Axis must be 0 or 1.\nError in line " + std::to_string(__LINE__));
    }
}


// OPERATORS
Array Array::operator+(const Array &other) const {

    if (rows_v != other.rows() || columns_v != other.columns()) {
        throw std::invalid_argument("Arrays must have the same size to perform addition (+).\nError in line " + std::to_string(__LINE__));
    }

    std::vector<std::vector<double>> result_data = {};

    for (int i = 0; i < rows_v; i++) {
        std::vector<double> row = {};
        row.reserve(columns_v);

        for (int j = 0; j < columns_v; j++) {
            row.push_back(data.at(i).at(j) + other.data.at(i).at(j));
        }
        result_data.push_back(row);
    }

    Array result = Array(result_data);

    return result;
}

Array Array::operator-(const Array &other) const {

        if (rows_v != other.rows() || columns_v != other.columns()) {
            throw std::invalid_argument("Arrays must have the same size to perform subtraction (-).\nError in line " + std::to_string(__LINE__));
        }

        std::vector<std::vector<double>> result_data = {};

        for (int i = 0; i < rows_v; i++) {
            std::vector<double> row = {};
            row.reserve(columns_v);

            for (int j = 0; j < columns_v; j++) {
                row.push_back(data.at(i).at(j) - other.data.at(i).at(j));
            }
            result_data.push_back(row);
        }

        Array result = Array(result_data);

        return result;
}

Array Array::operator*(const Array &other) const { // element-wise multiplication

    if (rows_v != other.rows() || columns_v != other.columns()) {
        throw std::invalid_argument("Arrays must have the same size to perform element-wise multiplication (*).\nError in line " + std::to_string(__LINE__));
    }

    std::vector<std::vector<double>> result_data = {};

    for (int i = 0; i < rows_v; i++) {
        std::vector<double> row = {};
        row.reserve(other.columns());

        for (int j = 0; j < other.columns(); j++) {
            row.push_back(data.at(i).at(j) * other.data.at(i).at(j));
        }
        result_data.push_back(row);
    }

    Array result = Array(result_data);

    return result;
}

Array Array::operator*(const double &factor) const {

    Array result = Array(*this);

    for (int i = 0; i < rows_v; i++) {
        for (int j = 0; j < columns_v; j++) {
            result(i, j) *= factor;
        }
    }

    return result;
}

Array Array::operator/(const Array &other) const {

    if (rows_v != other.rows() || columns_v != other.columns()) {
        throw std::invalid_argument("Arrays must have the same size to perform element-wise division (/).\nError in line " + std::to_string(__LINE__));
    }

    std::vector<std::vector<double>> result_data = {};

    for (int i = 0; i < rows_v; i++) {
        std::vector<double> row = {};
        row.reserve(other.columns());

        for (int j = 0; j < other.columns(); j++) {

            double divisor = other.data.at(i).at(j);

            if (divisor == 0){
                std::string text = "Error in line " + std::to_string(__LINE__) + "." +
                                   " Cannot divide by zero at index " + std::to_string(i) + "." +
                                   " Setting result to infinity (" + std::to_string(std::numeric_limits<double>::infinity()) + ").";
                row.push_back(std::numeric_limits<double>::infinity());
                std::cout << text << std::endl;
                continue;
            }

            row.push_back(data.at(i).at(j) / other.data.at(i).at(j));
        }
        result_data.push_back(row);
    }

    Array result = Array(result_data);

    return result;
}

double& Array::operator()(int x, int y){

    checkIndex(x, y);

    return data.at(x).at(y);
}

double Array::operator()(int x) {
    return data.at(x).at(0);
}

Array &Array::operator=(const Array &other) {
    if (this != &other) {

        // Copy data
        rows_v = other.rows();
        columns_v = other.columns();
        dimensions = other.dimensions;
        dtype = other.dtype;

        data.clear();
        for (const auto& row: other.data) {
            data.push_back(row);
        }
    }

    return *this;
}


// METHODS
int Array::rows() const {
    return rows_v;
}

int Array::columns() const {
    return columns_v;
}

std::string Array::get_dtype() const {
    return dtype;
}

void Array::print() const {

    if (rows_v == 1 || columns_v == 1){
        print_1d();
    }
    else {
        if (dimensions.size() == 1) {
            std::cout << "[]" << std::endl;
            return;
        } else if (dimensions.size() == 2 && dimensions.at(0) == 1 && dimensions.at(0) == 1) {
            std::cout << "[" << data.at(0).at(0) << "]" << std::endl;
            return;
        } else if (dimensions.size() == 2 && dimensions.at(1) == 1) {
            std::cout << "[";
            for (int i = 0; i < rows_v - 1; i++) {
                std::cout << data.at(i).at(0) << " ";
            }
            std::cout << data.at(rows_v - 1).at(0) << "]" << std::endl;
            return;
        } else if (dimensions.size() == 2 && dimensions.at(1) == 1) {
            std::cout << "[";
            for (int i = 0; i < columns_v; i++) {
                std::cout << data.at(0).at(i) << std::endl;
            }
            std::cout << "]" << std::endl;
            return;
        }

        std::vector<std::string> output;
        std::string row;

        row += "[";

        for (int i = 0; i < rows_v; i++) {

            if (i == 0) {
                row += "[";
            } else {
                row += " [";
            }

            for (int j = 0; j < columns_v - 1; j++) {

                std::ostringstream oss;
                oss << std::setprecision(8) << std::noshowpoint << data.at(i).at(j);

                row += oss.str();
                row += ", ";
            }

            std::ostringstream oss;
            oss << std::setprecision(15) << std::noshowpoint << data.at(i).at(columns_v - 1);

            row += oss.str();
            row += "]";

            if (i != rows_v - 1) {
                row += ",";
            } else {
                row += "]";
            }

            output.push_back(row);
            row = "";

        }

        for (auto &i: output) {
            std::cout << i << std::endl;
        }
    }
}

void Array::print_1d() const{

    if (rows_v == 1) {

        std::cout << "[";

        for (int i = 0; i < columns_v - 1; i++) {
            std::cout << data.at(0).at(i) << ", ";
        }
        std::cout << data.at(0).at(columns_v - 1) << "]" << std::endl;
    }
    else if (columns_v == 1) {

        std::cout << "[";

        for (int i = 0; i < rows_v - 1; i++) {
            std::cout << data.at(i).at(0) << ", ";
        }
        std::cout << data.at(rows_v - 1).at(0) << "]" << std::endl;
    }
}

void Array::checkIndex(int i, int j) const{

    if (i < 0){
        throw std::out_of_range("Row index cannot be negative.");
    }
    if (j < 0){
        throw std::out_of_range("Column index cannot be negative.");
    }

    std::string text;

    if (i >= rows_v) {
        text = "Row index out of range. Maximal row index index is " + std::to_string(rows_v - 1);
        throw std::out_of_range(text);
    }
    if (j >= columns_v) {
        text = "Column index out of range. Maximal column index index is " + std::to_string(columns_v - 1);
        throw std::out_of_range(text);
    }
}

double Array::max() const {
    double max = data.at(0).at(0);

    for (int i = 0; i < rows_v; i++){
        for (int j = 0; j < columns_v; j++){
            if (data.at(i).at(j) > max){
                max = data.at(i).at(j);
            }
        }
    }

    return max;
}

double Array::min() const {
    double min = data.at(0).at(0);

    for (int i = 0; i < rows_v; i++){
        for (int j = 0; j < columns_v; j++){
            if (data.at(i).at(j) < min){
                min = data.at(i).at(j);
            }
        }
    }

    return min;
}

std::vector<int> Array::argmax() const{
    double max = data.at(0).at(0);
    std::vector<int> indices = {0, 0};

    for (int i = 0; i < rows_v; i++){
        for (int j = 0; j < columns_v; j++){
            if (data.at(i).at(j) > max){
                max = data.at(i).at(j);
                indices[0] = i;
                indices[1] = j;
            }
        }
    }

    return indices;
}

std::vector<int> Array::argmin() const{
    double min = data.at(0).at(0);
    std::vector<int> indices = {0, 0};

    for (int i = 0; i < rows_v; i++){
        for (int j = 0; j < columns_v; j++){
            if (data.at(i).at(j) < min){
                min = data.at(i).at(j);
                indices[0] = i;
                indices[1] = j;
            }
        }
    }

    return indices;
}

double Array::sum() const {
    double sum = 0;

    for (int i = 0; i < rows_v; i++){
        for (int j = 0; j < columns_v; j++){
            sum += data.at(i).at(j);
        }
    }

    return sum;
}

Array Array::sum(int axis) {
    if (axis == 0){

        std::vector<double> sum(columns_v);

        for (int i = 0; i < rows_v; i++){
            for (int j = 0; j < columns_v; j++){
                sum.at(j) += data.at(i).at(j);
            }
        }

        Array ret = Array(sum, 1);

        return ret;
    }
    else if (axis == 1){

        std::vector<double> sum(rows_v);

        for (int i = 0; i < columns_v; i++){
            for (int j = 0; j < rows_v; j++){
                sum.at(j) += data.at(j).at(i);
            }
        }

        Array ret = Array(sum, 0);

        return ret;
    }
    else {
        throw std::invalid_argument("Axis must be 0 or 1.");
    }
}

Array Array::mult(const Array &a1, const Array &a2){

    if (a1.rows() != a2.columns() || a1.columns() != a2.rows()){
        throw std::invalid_argument("Incompatible array shapes");
    }

    // Allocate memory for the rows of the array
    std::vector<std::vector<double>> result(a1.rows(), std::vector<double>(a2.columns()));

    double sum = 0;

    for (int i = 0; i < a1.rows(); i++){
        for (int j = 0; j < a2.columns(); j++){
            for (int k = 0; k < a1.columns(); k++){
                sum += a1.data[i][k] * a2.data[k][j];
            }
            result.at(i).at(j) = sum;
            sum = 0;
        }
    }

    return Array(result);
}

double Array::determinant_rec(const std::vector<std::vector<double>>& matrix, unsigned long size) const {

    if (size == 1){
        return matrix.at(0).at(0);
    }

    if (size == 2){
        return matrix.at(0).at(0) * matrix.at(1).at(1) - matrix.at(0).at(1) * matrix.at(1).at(0);
    }

    double det = 0;

    for (int i = 0; i < size; i++){
        std::vector<std::vector<double>> submatrix(size - 1, std::vector<double>(size - 1));

        for (int j = 1; j < size; j++){
            for (int k = 0; k < size; k++){
                if (k < i){
                    submatrix.at(j - 1).at(k) = matrix.at(j).at(k);
                }
                else if (k > i){
                    submatrix.at(j - 1).at(k - 1) = matrix.at(j).at(k);
                }
            }
        }

        det += pow(-1, i) * matrix.at(0).at(i) * determinant_rec(submatrix, size - 1);
    }

    return det;
}

double Array::determinant() const {

    if (rows_v != columns_v){
        throw std::invalid_argument("Matrix must be square");
    }

    return determinant_rec(data, rows_v);
}

void Array::transpose() {
    std::vector<std::vector<double>> result(columns_v, std::vector<double>(rows_v));

    for (int i = 0; i < rows_v; i++){
        for (int j = 0; j < columns_v; j++){
            result.at(j).at(i) = data.at(i).at(j);
        }
    }

    data = result;
    std::swap(rows_v, columns_v);
}

}


}

/*


// todo when the array is 1x1 print without brackets, same for 1d (only one bracket)


// todo those functions have to work when it's 1D

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
 */


