//============================================================================
// Name        : Car_SimDomainTest.cpp
// Date        : 19/03/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 1
//============================================================================

#ifndef CAR_SIMULATION_BUSSTOP_H
#define CAR_SIMULATION_BUSSTOP_H

class Light;
class Road;
class Car;
class BusStop {
private:
    BusStop *_initCheck;

    Road *road;
    double position;
    double stoptime;
    double timestopped;
    Car *currentBus;
    bool bussy;
public:
/**
 * create a BusStop
 * @param position: position of the BusStop light
 * @param road: the road where the Busstop is placed on
 * @return: None
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    BusStop(double position, double stoptime, Road *road);

/**
 * Update the BusStop, changes the first bus his behavior
 * @param t: time since last update
 * @return: None
\n REQUIRE(properlyInitialized(), "BusStop wasn't initialized when calling updateBusStop");
   REQUIRE(t>=0, "Time cannot be negative");
*/
    void updateBusStop(double t);


/////////////
/**
 * get the road where the BusStop is positioned
 * @return: (Road*), the road where the BusStop is positioned
\n REQUIRE(this->properlyInitialized(), "BusStop wasn't initialized when calling getRoad");
    ENSURE(road->properlyInitialized(), "Road is not properly initialised");

*/
    Road *getRoad();

protected:
/**
 * change the road of the BusStop
 * @param road: the new road of the BusStop
 * @return: None
\n REQUIRE(this->properlyInitialized(), "BusStop wasn't initialized when calling setRoad");
    REQUIRE(r->properlyInitialized(), "Road is not properly initialised");
    REQUIRE(r->isvalid(),"Road isn't valid");
    ENSURE(road == r,"Road hasn't changed");
*/
    void setRoad(Road *road);

public:
/**
 * get the position of the BusStop on the road
 * @return: (double), the position of the BusStop on the road
\n REQUIRE(this->properlyInitialized(), "BusStop wasn't initialized when calling getPosition");
    ENSURE(onRoad(), "Busstop is not on road");
*/
    double getPosition();

/**
 * change the position of the BusStop
 * @param position: the new position of the BusStop
 * @return: None
\n REQUIRE(this->properlyInitialized(), "BusStop wasn't initialized when calling setPosition");
    REQUIRE(onRoad(p), "Busstop is not on road");
    ENSURE(position == p,"Position hasn't changed");
*/
    void setPosition(double position);

/**
 * get the stoptime of the Busstop
 * @return: (double), the stoptime of the Busstop
\n REQUIRE(this->properlyInitialized(), "BusStop wasn't initialized when calling getStopTime");
    ENSURE(stoptime>=0, "stoptime cannot be negative");
*/
    double getStopTime();

/**
* get the waittime of the getWaitTime
* @return: (double), the waittime the getWaitTime
\n REQUIRE(this->properlyInitialized(), "BusStop wasn't initialized when calling getTimeStopped");
    ENSURE(timestopped>=0, "Timestopped cannot be negative");
*/
    double getTimeStopped();

/**
 * get the state of the Busstop
 * @return: (double), the stoptime of the Busstop
\n REQUIRE(properlyInitialized(), "Busstop wasn't initialized when calling getbussy");
*/
    bool getbussy();

/**
 * set the state of the Busstop
 * @param bussey: the new state of the BusStop
 * @return: none
\n REQUIRE(properlyInitialized(), "Busstop wasn't initialized when calling setbussy");
   ENSURE(bussy==b, "Bussy hasn't changed");
*/
    void setbussy(bool bussy);

/////////////
/**
 * set the state of the Busstop
 * @param bussey: the new state of the BusStop
 * @return: none
*/
    bool properlyInitialized() const;

/**
 * set the state of the Busstop
 * @param bussey: the new state of the BusStop
 * @return: none
*/
    bool onRoad() const;

/**
 * set the state of the Busstop
 * @param bussey: the new state of the BusStop
 * @return: none
*/
    bool onRoad(int p) const;

/**
 * set the state of the Busstop
 * @param bussey: the new state of the BusStop
 * @return: none
*/
    bool isvalid(Road *road);

/////////////
};
#endif //CAR_SIMULATION_BUSSTOP_H
