//============================================================================
// Name        : Car_SimDomainTest.cpp
// Date        : 19/03/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 1
//============================================================================


#ifndef CAR_SIMULATOR_FUNCTIONS_H
#define CAR_SIMULATOR_FUNCTIONS_H
#include <string>
#include "vector"
namespace std {
    int stoi(std::string& text);

    string itos(int i);

    string dtos(double d);

    double stod(std::string& x);

    std::vector<std::string> splitString(std::string str);


}
#endif //CAR_SIMULATOR_FUNCTIONS_H
