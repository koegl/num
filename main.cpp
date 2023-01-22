//
// Created by Fryderyk Kögl on 23.12.22.
//
//
#include <list>
#include <string>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <sstream>


#include "num.cpp"
#include "print.h"
#include "parsing.h"

int main(){

//    Array m1 = Array({{3, -9, -8},
//                                    {2, 4, 3},
//                                  {2, 4, 3}});
//    Array m2 = Array({{7, -3, 7},
//                                  {-2, 3, 8},
//                                  {6, 2, -4}});
//    Array m3 = Array({{1, 2, 3},
//                                  {4, 5, 6},
//                                  {7, 8, 9}});

   std::string s = "{{1, 2, 3},"
                   "{4, 5, 6},"
                   "{7, 8, 9}}";

   std::vector<std::vector<int>> output = parse_input(s);

   for (auto a: output) {
       for (auto b: a) {
           std::cout << b << std::endl;
       }
   }

   std::cout << s << std::endl;

    return 0;
}


//#include <utility>
//#include <vector>
//#include <iostream>
//
//
//int get_amount_of_rows(const std::string& text) {
//
//    int amount = 0;
//
//    for (char i: text) {
//        if (i == '[') {
//            amount++;
//        }
//    }
//
//    return amount - 1;  // one less because 0D array has 1 bracket
//}
//
//
//int get_amount_of_columns(const std::string& text){
//
//    std::string new_text;
//
//    for (char i: text) {
//        if (i != '[') {
//
//            if (i == ']') {
//                break;
//            }
//
//            new_text += i;
//        }
//    }
//
//    int amount = 0;
//
//    for (char i: new_text) {
//        if (i == ',') {
//            amount++;
//        }
//    }
//
//        return amount + 1;  // one more because there is one less comma than columns
//}
//
//
//double** parse_input(const std::string& input_array){
//
//    int rows = get_amount_of_rows(input_array);
//    int columns = get_amount_of_columns(input_array);
//
//    std::cout << rows << std::endl;
//    std::cout << columns << std::endl;
//
//    double** data_array;
//    data_array = new double*[rows];
//    for (int i = 0; i < rows; i++) {
//        data_array[i] = new double[columns];
//    }
//
//    return data_array;
//
//}
//
//int main() {
//
//    double** my_array = parse_input("[[1]]");
//
//    return 0;
//}
