//
// Created by Fryderyk Kögl on 23.12.22.
//

#ifndef NUMPY_CPP_NUMPY_H
#define NUMPY_CPP_NUMPY_H

#include <list>
#include <iostream>
#include <typeinfo>
#include<math.h>

#include "parsing.h"

class Array {
public:
    // todo add shape

    // CONSTRUCTORS
    Array();
    explicit Array(std::string input);
    explicit Array(const char input[]);
    Array(const Array &other);
    Array(int **new_data, int rows, int columns, const std::string& new_dtype="float64");
    explicit Array(const std::vector<std::vector<double>>& new_data, const std::string& new_dtype="float64");
    explicit Array(const std::vector<double> &new_data, int axis, const std::string& new_dtype="float64");


    // OPERATORS
    Array operator+(const Array &other) const;
    Array operator-(const Array &other) const;
    Array operator*(const Array &other) const;
    Array operator*(const double &factor) const;
    Array operator/(const Array &other) const;
    double& operator()(int x, int y);
    double operator()(int x);
    Array& operator=(const Array &other);


    // METHODS
    void print() const;

    unsigned long rows() const;
    unsigned long columns() const;
    std::string get_dtype() const;

    void checkIndex(int i, int j) const;

    double max() const;
    double min() const;
    std::vector<int> argmax() const;
    std::vector<int> argmin() const;

    double sum() const;
    Array sum(int axis);
    static Array mult(const Array &a1, const Array &a2);
    double determinant_rec(const std::vector<std::vector<double>>& matrix, unsigned long size) const;
    double determinant() const;

    void transpose();
    void inverse();


    // VARIABLES
    std::vector<std::vector<double>> data;

private:

    std::string dtype;
    unsigned long rows_v{};
    unsigned long  columns_v{};

    std::vector<unsigned long > dimensions;

    void print_1d() const;
};

#endif //NUMPY_CPP_NUMPY_H
