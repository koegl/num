//
// Created by Fryderyk Kögl on 23.12.22.
//

#include <list>
#include <string>
#include <iostream>

#include <stdexcept>

#include "num.cpp"
#include "print.h"




int main(){

    Array m1 = Array({{2.0, 0.20001, 2.2, 44},
                                    {1, 2, 3, 55}});
    Array m2 = Array({{0.01, 0.20001, 2.2, 44},
                                    {1, 2, 3, 55}});

    Array m3 = m1 / m2;

    m3.print();

    m3[0][0] = 1;

    m3.print();

    return 0;
}