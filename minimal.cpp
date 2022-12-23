#include <iostream>
#include <list>

int main(){

    std::list<std::list<double>> myArguments = {
            {1.0, 2.0, 3, 4},
            {2.0, 4.0, 6.0, 8}
    };

    std::cout << myArguments.front().size() << std::endl;

    auto it = myArguments.begin();

    int current = myArguments.front().size();

    for (int i = 0; i < myArguments.size(); i++) {
        if ((*it).size() != current) {
            throw std::invalid_argument("All rows must have the same length");
        }
        it++;
    }

    return 0;
}