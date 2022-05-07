//
// Created by robbe on 07.05.22.
//

#include "GenerateIni.h"
#include "../Classes/World.h"

GenerateIni::GenerateIni(World *world, const std::string &filename, int filenumber)
    : world(world), filename(filename), filenumber(filenumber) {
    iniFile = std::ofstream();
    _initcheck = this;
}
/*
void GenerateIni::generate() {
    REQUIRE(world->isvalidSimulation(), "World is not valid when calling generate");
    error.close();
    std::vector<Road*> roadIt = getRoads();
    for (std::vector<Road*>::iterator itR = roadIt.begin(); itR != roadIt.end(); itR++) {
        delete (*itR);
    }
    std::vector<Junction*> junctionIT = getJunctions();
    for (std::vector<Junction*>::iterator itJ = junctionIT.begin(); itJ != junctionIT.end(); itJ++) {
        delete (*itJ);
    }
    ///////////////////////
    std::vector<CarData*> carDataIT = carData;
    for (std::vector<CarData*>::iterator itD = carDataIT.begin(); itD != carDataIT.end(); itD++) {
        delete (*itD);
    }
    ////////////////
}*/
