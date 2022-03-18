//
// Created by robbe on 3-3-2022.
//

#ifndef CAR_SIMULATOR_WORLD_H
#define CAR_SIMULATOR_WORLD_H
#include <vector>
#include <iostream>
#include <cmath>
#include "../tinyxml/tinyxml.h"
#include "../tinyxml/tinystr.h"
#include "Road.h"
#include "CarGen.h"

class World {
private:
    World* _initCheck;

    std::vector<Road*> roads;
    std::vector<CarGen*> carGen;
    double time;
public:
/**
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    World();
/**
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling loadWorld);
*/
    void loadWorld(const char * worldName);

//////////////
private:
/**
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling loadRoad);
*/
    void loadRoad(TiXmlElement* elem1);
/**
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling loadLight);
*/
    void loadLight(TiXmlElement* elem1);
/**
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling loadCar);
*/
    void loadCar(TiXmlElement* elem1);
/**
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling loadCarGen);
*/
    void loadCarGen(TiXmlElement* elem1);
//////////////
public:

/**
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling getCarGen);
*/
    const std::vector<CarGen *> &getCarGen();
/**
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling setCarGen);
*/
    void setCarGen(const std::vector<CarGen *> &carGen);
/**
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling setRoad);
*/
    void setRoad(const std::vector<Road *> &banen);
/**
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling getRoads);
*/
    const std::vector<Road *> &getRoads();
/**
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling addCarGen);
*/
    void addCarGen(Road* road,int frequency);

/**
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling simulateWorld);
*/
    void simulateWorld(std::ostream & onStream);

/**
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling updateWorld);
*/
    void updateWorld(double t);
//////////////


    /////////////
protected:
    bool properlyInitialized ();
    /////////////
};



#endif //CAR_SIMULATOR_WORLD_H
