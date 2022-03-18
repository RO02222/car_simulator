//
// Created by simon on 18.03.22.
//

#ifndef CAR_SIMULATION_CAR_SIMUTILS_H
#define CAR_SIMULATION_CAR_SIMUTILS_H

#include <iostream>

bool DirectoryExists(const std::string dirname);

bool FileExists(const std::string dirname);

bool FileIsEmpty(const std::string filename);

bool FileCompare(const std::string leftFileName, const std::string rightFileName);


#endif //CAR_SIMULATION_CAR_SIMUTILS_H
