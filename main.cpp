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


#include "num.h"
#include "print.h"
#include "parsing.h"


int main(){

    std::string s = "{{1, 2, 3},"
                   "{4, 5, 6},"
                   "{7, 8, 9}}";

    Array m = Array(s);

    Array m2 = m.sum(0);
    Array m3 = m.sum(1);

    m2.print();
    m3.print();


    Array m4 = Array::mult(m2, m3);

    m4.print();


    return 0;
}


