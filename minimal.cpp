//
// Created by Fryderyk Kögl on 23.12.22.
//

#include <list>
#include <string>
#include <iostream>


class minimal {
public:
    minimal(const std::list<std::string> & myArguments) {

        length_of_array = myArguments.size();
        data = new double[length_of_array];

        length_of_array = myArguments.size();
        data = new double[length_of_array];

        auto it = myArguments.begin();

        for (int i = 0; i < length_of_array; i++) {
            data[i] = std::stod(*it);
            it++;
        }

        dtype_value = "float64";
    }

    minimal operator+(const minimal & other) const {

        std::list<std::string> result_data = {};

        for (int i = 0; i < length_of_array; i++) {
            result_data.push_back(std::to_string(data[i] + other.data[i]));

        }

        minimal result = minimal(result_data);

        // double result = data[0] + other.data[0];

        //minimal result_object = minimal({"result"});
        //result_object.data[0] = result;

        return result;
    }

    ~minimal(){
        delete[] data;
    }

    double *data;
    int length_of_array;
    std::string dtype_value;
};


int main(){

    minimal m1 = minimal({"1", "3"});
    minimal m2 = minimal({"7", "6"});

    minimal m3 = m1 + m2;

    std::cout<< m3.data[1] << std::endl;

//    Array test({"4", "2.5", "77"});
//    Array test2({"4", "2.5", "3.11"});
//
//    Array result = test + test2;
//
//    delete[] result.data;
//    delete[] test.data;
//    delete[] test2.data;


    return 0;
}
