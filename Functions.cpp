//
// Created by robbe on 17-3-2022.
//

#include "Functions.h"
#include <iostream>
#include <sstream>

int stringInt(std::string text) {
std::istringstream iss(text);
int number;
iss >> number;
return number;
}