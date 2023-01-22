//
// Created by Fryderyk Kögl on 22.01.23.
//

#include "parsing.h"

std::string clean(std::string& input){

        std::string output;

        for (char i: input) {
            if (i != ' ' and i != '{' and i != '}') {
                output += i;
            }
        }

        return output;
}

std::vector<std::vector<int>> parse_input(std::string& input){

    std::vector<std::vector<int>> output;

    // Remove the outer curly braces
    input = input.substr(1, input.size() - 2);

    // Split the string by '},'
    std::stringstream ss(input);
    std::string item;
    while (std::getline(ss, item, '}')) {
        // Split the inner vectors by ','
        std::vector<int> inner;
        std::stringstream inner_ss(item);
        std::string inner_item;
        while (std::getline(inner_ss, inner_item, ',')) {
            // Convert the string element to int and add to the inner vector

            inner_item = clean(inner_item);

            if (inner_item.empty()) {
                continue;
            }

            inner.push_back(std::stoi(inner_item));
        }
        // Add the inner vector to the outer vector
        output.push_back(inner);
    }

    return output;
}