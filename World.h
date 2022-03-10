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
    World* _initCheck;

    std::vector<Road*> roads;
    std::vector<CarGen*> carGen;
public:
/**
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    World();

/**
\n REQUIRE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    void loadWorld(const char * worldName);
//////////////
private:
/**
\n REQUIRE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    void loadRoad(TiXmlElement* elem1);
/**
\n REQUIRE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    void loadLight(TiXmlElement* elem1);
/**
\n REQUIRE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    void loadCar(TiXmlElement* elem1);
/**
\n REQUIRE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    void loadCarGen(TiXmlElement* elem1);
//////////////
public:

/**
\n REQUIRE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    const std::vector<CarGen *> &getCarGen();

/**
\n REQUIRE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    void setCarGen(const std::vector<CarGen *> &carGen);
/**
\n REQUIRE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    void setRoad(const std::vector<Road *> &banen);
/**
\n REQUIRE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    const std::vector<Road *> &getRoads();
/**
\n REQUIRE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    void addCarGen(Road* road,int frequency);





    /////////////
protected:
    bool properlyInitialized ();

    /////////////
};



#endif //CAR_SIMULATOR_WORLD_H
