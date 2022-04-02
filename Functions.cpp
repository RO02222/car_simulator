//============================================================================
// Name        : Car_SimDomainTest.cpp
// Date        : 19/03/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 1
//============================================================================


#include "Functions.h"
#include <iostream>
#include <sstream>

int stoi(std::string text) {
    std::istringstream iss(text);
    int number;
    iss >> number;
    return number;
}