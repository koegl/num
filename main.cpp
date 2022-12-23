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

    Array m1 = Array({2.0, 100, 2, 44});
    Array m2 = Array({7, 11.24, 7, 1.0001});

    Array m3 = m1 + m2;

    m3.append(17);

    print(m3);

    m3.pop(2);

    print(m3);

    print(m3.cumsum());

    print(m3.cumprod());

    return 0;
}