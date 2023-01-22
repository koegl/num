//
// Created by Fryderyk Kögl on 22.01.23.
//

#ifndef NUMPY_CPP_PARSING_H
#define NUMPY_CPP_PARSING_H

#include <sstream>
#include <vector>
#include <iostream>

std::vector<std::vector<double>> parse_input( std::string& input);

int ret(std::string& input);

std::string clean(std::string& input);

#endif //NUMPY_CPP_PARSING_H
