//============================================================================
// Name        : Car_SimDomainTest.cpp
// Date        : 19/03/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 1
//============================================================================


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
    World *_initCheck;

    std::vector<Road *> roads;
    double time;
public:
/**
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    World();



/**
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling simulateWorld);
*/
    void simulateWorld(std::ostream &onStream);

/**
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling updateWorld);
*/
    void updateWorld(double t);



//////////////
public:
    /**
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling loadWorld);
*/
    void loadWorld(const char *worldName);

private:
/**
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling loadRoad);
*/
    void loadRoad(TiXmlElement *elem1);

/**
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling loadLight);
*/
    void loadLight(TiXmlElement *elem1);

/**
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling loadCar);
*/
    void loadCar(TiXmlElement *elem1);

/**
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling loadCarGen);
*/
    void loadCarGen(TiXmlElement *elem1);
//////////////



/////////////
public:
/**
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling getRoads);
*/
    const std::vector<Road *> &getRoads();

/**
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling setRoad);
*/
    void setRoad(const std::vector<Road *> &r);

/**
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling getTime);
*/
    double getTime() const;

/**
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling setTime);
*/
    void setTime(double t);
/////////////



//////////////
public:
    bool properlyInitialized() const;
//////////////
};



#endif //CAR_SIMULATOR_WORLD_H
