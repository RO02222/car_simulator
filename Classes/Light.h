//============================================================================
// Name        : Car_SimDomainTest.cpp
// Date        : 19/03/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 1
//============================================================================


#ifndef CAR_SIMULATOR_LIGHT_H
#define CAR_SIMULATOR_LIGHT_H

enum color {green,red};
class Road;

class Light{
private:
    Light* _initCheck;
    Road* road;

    double position;
    double cycle;
    double lastCycle;
    color state;
public:
/**
 * create a traffic light
 * @param name: name of the road
 * @param length: lengt of the road
 * @return: None
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    Light(double position, double cycle, Road* r);


/**
 * Update the traffic light, changes the first cars behavior depending on the lights state
 * @param t: time since last update
 * @return: None
\n REQUIRE(properlyInitialized(), "Light wasn't initialized when calling updateLight");
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
/////////////



/////////////
protected:
    bool properlyInitialized() const;

/////////////
};



#endif //CAR_SIMULATOR_LIGHT_H
