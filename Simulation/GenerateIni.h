//
// Created by robbe on 07.05.22.
//

#ifndef CAR_SIMULATION_GENERATEINI_H
#define CAR_SIMULATION_GENERATEINI_H
#include <fstream>

class World;

class GenerateIni {
public:
    GenerateIni* _initcheck;
    World* world;
    std::ofstream iniFile;
    std::string filename;
    int filenumber;

public:
    GenerateIni(World *world, const std::string &filename, int filenumber);
    void generate();
};


#endif //CAR_SIMULATION_GENERATEINI_H
