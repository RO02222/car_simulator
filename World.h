//
// Created by robbe on 3-3-2022.
//

#ifndef CAR_SIMULATOR_WORLD_H
#define CAR_SIMULATOR_WORLD_H
#include <vector>
#include <iostream>
#include <cmath>
#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"
#include "Road.h"
#include "CarGen.h"

class World {
private:
    std::vector<Road*> roads;
    std::vector<CarGen*> carGen;
public:
    World(const char * worldName);

    void loadWorld(const char * worldName);
//////////////
private:
    void loadRoad(TiXmlElement* elem1);
    void loadLight(TiXmlElement* elem1);
    void loadCar(TiXmlElement* elem1);
    void loadCarGen(TiXmlElement* elem1);
//////////////
public:


    const std::vector<CarGen *> &getCarGen() const;

    void setCarGen(const std::vector<CarGen *> &carGen);

    void setRoad(const std::vector<Road *> &banen);

    const std::vector<Road *> &getRoads() const;

    void addCarGen(Road* road,int frequency);



};



#endif //CAR_SIMULATOR_WORLD_H
