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

class Road;
class Car;
class Junction {
private:
    Junction* _initCheck;
    std::vector<std::pair<Road* , double> > roads;
    std::vector<std::pair<Car*,bool> > cars;
public:
/**
 * create a Junction
 * @param roads: the roads connected to the junction
 * @return: None
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    Junction(std::vector<std::pair<Road* , double> > roads);


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
    void addCar(Car* car, bool updated);




/////////////
/**
 * get the n'th road of the junction (starting from 0)
 * @param n: the n road of the Junction
 * @return: (Road*), the n road of the junction
\n REQUIRE(properlyInitialized(), "Junction wasn't initialized when calling getRoad");
*/
    Road* getRoad(int n);


protected:
/**
 * change the n'th road of the Junction (starting from 0)
 * @param road: the new road of the Junction
 * @param n: the n road of the Junction
 * @return: None
\n REQUIRE(properlyInitialized(), "Light wasn't initialized when calling setRoad");
*/
    void setRoad(Road* road, int n);

public:
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
    void setPosition(double position, int n);


/////////////



/////////////
protected:
    bool properlyInitialized() const;

/////////////
};


#endif //CAR_SIMULATION_JUNCTION_H
