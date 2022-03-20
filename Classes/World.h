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
 * create a simulationWorld
 * @return: None
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    World();

/**
function:
 * delete a simulationWorld and everything in the world
 * @return: None
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling ~Road);
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling ~World);
*/
    ~World();


/**
 * write the current state of all cars to the file
 * @param onStream: a stream where the current state of all cars is written to
 * @return: None
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling simulateWorld);
*/
    void simulateWorld(std::ostream &onStream);

/**
 * Update the world, update all the roads
 * @param t: time since last update
 * @return: None
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling updateWorld);
*/
    void updateWorld(double t);


//////////////
/**
 * Basic Getters/Setters
*/
public:
/**
 * load a World from a file
 * @param worldName: name of the file
 * @return: None
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling loadWorld);
*/
    void loadWorld(const char *worldName);

private:
/**
 * load a Road from a file
 * @param elem1: part of the file
 * @return: None
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling loadRoad);
*/
    void loadRoad(TiXmlElement *elem1);

/**
 * load a Light from a file
 * @param elem1: part of the file
 * @return: None
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling loadLight);
*/
    void loadLight(TiXmlElement *elem1);

/**
 * load a Car from a file
 * @param elem1: part of the file
 * @return: None
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling loadCar);
*/
    void loadCar(TiXmlElement *elem1);

/**
 * load a CarGen from a file
 * @param elem1: part of the file
 * @return: None
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling loadCarGen);
*/
    void loadCarGen(TiXmlElement *elem1);
//////////////



/////////////
public:
/**
 * get all the roads of the simulationWorld
 * @return: (std::vector<Road*>), the roads in the simulationWorld
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling getRoads);
*/
    const std::vector<Road *> &getRoads();

/**
 * change the roads of the simulationWorld
 * @param r: the new roads of the simulationWorld
 * @return: None
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling setRoad);
*/
    void setRoad(const std::vector<Road *> &r);

/**
 * get the time of the simulationWorld
 * @return: (double), the simulationTime
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling getTime);
*/
    double getTime() const;

/**
 * change the simulationTime of the simulationWorld
 * @param t: the new simulationTime of the simulationWorld
 * @return: None
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
