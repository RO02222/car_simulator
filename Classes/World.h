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
#include <fstream>
#include "../tinyxml/tinyxml.h"
#include "../tinyxml/tinystr.h"
#include "Road.h"
#include "CarGen.h"
#include "CarData.h"
#include "Car.h"


class Junction;
class CarData;

class World {
public:
    std::ofstream error;
private:
    World *_initCheck;

    std::vector<CarData*> carData;
    std::vector<Junction*> junctions;
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
    void simpleSimulateWorld(std::ostream &onStream);

/**
 * draw the current state of the simulation to the file
 * @param onStream: a stream where the current state of all cars is written to
 * @return: None
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling simulateWorld);
*/
    void graficImpSimulateWorld(std::ostream &onStream);

/**
 * Update the world, update all the roads
 * @param t: time since last update
 * @return: None
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling updateWorld);
*/
    void updateWorld(double t);


/**
 * check the simulation if valid
 * @return: none
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling updateWorld);
*/
    void isvalid();


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
 * add a road to the simulationWorld
 * @param name: the name of the new road
 * @param length: the length of the new road
 * @return: None
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling addRoad);
*/
    void addRoad(std::string name, double length);

/**
 * add a road to the simulationWorld
 * @param road: the new road
 * @return: None
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling addRoad);
*/
    void addRoad(Road* road);


/**
 * get all the Junctions of the simulationWorld
 * @return: (std::vector<Junction*>), the Junctions in the simulationWorld
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling getJunctions);
*/
    const std::vector<Junction *> &getJunctions();

/**
 * change the Junctions of the simulationWorld
 * @param junction: the new Junctions of the simulationWorld
 * @return: None
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling setJunctions);
*/
    void setJunctions(const std::vector<Junction *> & junction);

/**
 * add a Junction to the simulation
 * @param roads: roads with the position of the junction on that road
 * @return: None
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling addJunction);
*/
    void addJunction(std::vector<std::pair<Road* , double> > roads);

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

/**
 * get data of a specific carType
 * @param type: the type of carData
 * @return: (double), the carData
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling getCarData);
*/
    CarData* getCarData(Type type);

/**
 * get the data of all the cars
 * @return: (std::vector<CarData*>*), all the carData
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling getAllData);
*/
    std::vector<CarData*>* getAllData();
/////////////



//////////////
public:
    bool properlyInitialized() const;
//////////////
};



#endif //CAR_SIMULATOR_WORLD_H
