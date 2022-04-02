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
    std::pair<Road* , double> road1;
    std::pair<Road* , double> road2;
    std::vector<Car*> cars;
public:
/**
 * create a Junction
 * @param R1: the first road of the Junction
 * @param R2: the second road of the Junction
 * @return: None
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    Junction(std::pair<Road* , double> R1,std::pair<Road* , double> R2);


/**
 * Update the traffic light, changes the first cars behavior depending on the lights state
 * @param t: time since last update
 * @return: None
\n REQUIRE(properlyInitialized(), "Light wasn't initialized when calling updateLight");
*/
    void updateLight(double t);









/////////////
/**
 * get the first road of the junction
 * @param n: the n road of the Junction
 * @return: (Road*), the n road of the junction
\n REQUIRE(properlyInitialized(), "Junction wasn't initialized when calling getRoad");
*/
    Road* getRoad(int n);


protected:
/**
 * change the n road of the Junction
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
