//============================================================================
// Name        : Car_SimDomainTest.cpp
// Date        : 19/03/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 1
//============================================================================


#ifndef CAR_SIMULATION_JUNCTION_H
#define CAR_SIMULATION_JUNCTION_H

#include <iostream>
#include <vector>
#include "Light.h"

class Road;
class Car;
class Light;
class Junction {
public:
    std::ofstream* error;
private:
    Junction* _initCheck;
    std::vector<std::pair<Road* , double> > roads;
    std::vector<Car*> cars;

private:
    Light* clock;
    std::vector<Light*> lights;
    unsigned int numLight;


public:
/**
 * create a Junction
 * @param roads: the roads connected to the junction
 * @return: None
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    Junction(std::vector<std::pair<Road* , double> > roads, std::ofstream* error);


/**
 * Update the junction, update cars near the junction and switch lanes.
 * @param t: time since last update
 * @return: None
\n REQUIRE(properlyInitialized(), "Junction wasn't initialized when calling updateJunction");
*/
    void updateJunction(double t);

/**
 * add a car the junction, junction takes control of the car.
 * @param car: new car on the Junction
 * @param updated: already updated
 * @return: None
\n REQUIRE(properlyInitialized(), "Junction wasn't initialized when calling addCar");
*/
    void addCar(Car* car);

/**
 * check the Junction for lights and change on all road  of the Junction
 * @return: None
\n REQUIRE(properlyInitialized(), "Junction wasn't initialized when calling setPosition");
*/
    void checkJunctionLights();


/////////////
/**
 * get the n'th road of the junction (starting from 0)
 * @param n: the n road of the Junction
 * @return: (Road*), the n road of the junction
\n REQUIRE(properlyInitialized(), "Junction wasn't initialized when calling getRoad");
*/
    Road* getRoad(int n);

/**
 * get the cars near the junction that aren't udated by the road
 * @param n: the n road of the Junction
 * @return: (Road*), the n road of the junction
\n REQUIRE(properlyInitialized(), "Junction wasn't initialized when calling getRoad");
*/
    std::vector<Car*> getCars();

/**
 * change the n'th road of the Junction (starting from 0)
 * @param road: the new road of the Junction
 * @param n: the n road of the Junction
 * @return: None
\n REQUIRE(properlyInitialized(), "Light wasn't initialized when calling setRoad");
*/
    void setRoad(Road* road,unsigned int n);

/**
 * get the position of the Junction on the road
 * @param n: the n road of the Junction
 * @return: (double), the position of the Junction on the road
\n REQUIRE(properlyInitialized(), "Light wasn't initialized when calling getPosition");
*/
    double getPosition(int n);

/**
 * get the position of the Junction on the road
 * @param roadname: the name of the road from the Junction
 * @return: (double), the position of the Junction on the road
\n REQUIRE(properlyInitialized(), "Light wasn't initialized when calling getPosition");
*/
    double getPosition(std::string roadname);

/**
 * change the position of the Junction
 * @param n: the n road of the Junction
 * @param position: the new position of the Junction
 * @return: None
\n REQUIRE(properlyInitialized(), "Light wasn't initialized when calling setPosition");
*/
    void setPosition(double position,unsigned int n);

/**
 * get the position of the Junction on the road
 * @param roadname: the name of the road from the Junction
 * @return: (double), the position of the Junction on the road
\n REQUIRE(properlyInitialized(), "Light wasn't initialized when calling getPosition");
*/
    Light* getClock();

/**
 * change the position of the Junction
 * @param n: the n road of the Junction
 * @param position: the new position of the Junction
 * @return: None
\n REQUIRE(properlyInitialized(), "Light wasn't initialized when calling setPosition");
*/
    void setClock(Light* light);

/////////////



/////////////
public:
    bool properlyInitialized() const;

    bool onRoad(long unsigned int n) const;

    bool onRoad(std::string roadname);

    bool isvalid() const;
/////////////
};


#endif //CAR_SIMULATION_JUNCTION_H
