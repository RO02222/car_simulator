//============================================================================
// Name        : Car_SimDomainTest.cpp
// Date        : 19/03/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 1
//============================================================================


#ifndef CAR_SIMULATOR_LIGHT_H
#define CAR_SIMULATOR_LIGHT_H
#include <iostream>

enum color {green,red,orange};
class Road;
class Junction;

class Light{
public:
    std::ofstream* error;
private:
    Light* _initCheck;
    Road* road;

    double position;
    double cycle;
    double lastCycle;
    color state;

private:
    bool clock;
    bool update;
public:
/**
 * create a traffic light
 * @param position: position of the traffic light
 * @param cycle: the time a cycle takes for a traffic light
 * @param road: the road where the traffic light is placed on
 * @param error: errorfile
 * @return: None
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    Light(double position, double cycle, Road* road, std::ofstream* error);

/**
 * create a traffic light for a junction as a clock
 * @param cycle: the time a cycle takes for a traffic light
 * @param error: errorfile
 * @return: None
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    Light(double cycle, std::ofstream* error);


/**
 * create a traffic controller for a junction
 * @param junction: junction with lights
 * @param error: errorfile
 * @return: None
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    Light(Junction junction, std::ofstream* error);


/**
 * Update the traffic light, changes the first (not priority) car his behavior depending on the lights state
 * @param t: time since last update
 * @return: None

\n REQUIRE(t >= 0, "Time cannot be negative");

    As Light
\n REQUIRE(properlyInitialized(), "Light wasn't initialized when calling updateLight");
\n REQUIRE(isvalid(road), "Light wasn't initialized when calling updateLight");

    As clock
\n REQUIRE(isvalidClock(), "Clock wasn't initialized when calling updateLight");
\n REQUIRE(isvalidClock(), "Clock wasn't initialized when calling updateLight");
*/
    void updateLight(double t);


/////////////
/**
 * get the road where the traffic light is positioned
 * @return: (Road*), the road where the traffic light is driving
\n REQUIRE(properlyInitialized(), "Light wasn't initialized when calling getRoad");
*/
    Road* getRoad();

protected:
/**
 * change the road of the traffic light
 * @param road: the new road of the traffic light
 * @return: None
\n REQUIRE(properlyInitialized(), "Light wasn't initialized when calling setRoad");
*/
    void setRoad(Road* road);

public:
/**
 * get the position of the traffic light on the road
 * @return: (double), the position of the traffic light on the road
\n REQUIRE(properlyInitialized(), "Light wasn't initialized when calling getPosition");
*/
    double getPosition();
/**
 * change the position of the traffic light
 * @param position: the new position of the traffic light
 * @return: None
\n REQUIRE(properlyInitialized(), "Light wasn't initialized when calling setPosition");
*/
    void setPosition(double position);
/**
 * get the cycleTime the traffic light
 * @return: (double), the cycleTime the traffic light
\n REQUIRE(properlyInitialized(), "Light wasn't initialized when calling getCycle");
*/
    double getCycle();
/**
 * change cycle of the traffic light
 * @param cycle: the new cycle of the traffic light
 * @return: None
\n REQUIRE(properlyInitialized(), "Light wasn't initialized when calling setCycle");
*/
    void setCycle(double cycle);
/**
 * get the time since the last cycle the traffic light
 * @return: (double), the cycleTime the traffic light
\n REQUIRE(properlyInitialized(), "Light wasn't initialized when calling getCycle");
*/
    double getLastCycle();
/**
 * set the time since the last cycle the traffic light
 * @param cycle: the new cycle of the traffic light
 * @return: None
\n REQUIRE(properlyInitialized(), "Light wasn't initialized when calling setCycle");
*/
    void setLastCycle(double cycle);
/**
 * get the state the traffic light
 * @return: (color), the state the traffic light
\n REQUIRE(properlyInitialized(), "Light wasn't initialized when calling getState");
*/
    color getState();
/**
 * change state of the traffic light
 * @param state: the new state of the traffic light
 * @return: None
\n REQUIRE(properlyInitialized(), "Light wasn't initialized when calling setState");
*/
    void setState(color state);
/**
 * get the state the traffic light
 * @return: (color), the state the traffic light
\n REQUIRE(properlyInitialized(), "Light wasn't initialized when calling getClock");
*/
    bool getClock();
/**
 * enable/disable the clock of the traffic light
 * @param state: the new state of the traffic light
 * @return: None
\n REQUIRE(properlyInitialized(), "Light wasn't initialized when calling setClock");
*/
    void setClock(bool state);
/////////////



/////////////
public:
    bool properlyInitialized() const;

    bool onRoad() const;

    bool onRoad(int d) const;

    bool isvalid(Road* road) const;

    bool isvalidClock() const;
/////////////
};



#endif //CAR_SIMULATOR_LIGHT_H
