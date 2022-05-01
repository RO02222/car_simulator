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
        BusStop* _initCheck;

        Road* road;
        double position;
        double stoptime;
        double timestopped;
        Car* currentBus;
public:
        bool bussy;
    public:
/**
 * create a BusStop
 * @param position: position of the BusStop light
 * @param road: the road where the Busstop is placed on
 * @return: None
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    BusStop(double position, double stoptime, Road* road);

/**
 * Update the BusStop, changes the first bus his behavior
 * @param t: time since last update
 * @return: None
\n REQUIRE(properlyInitialized(), "BusStop wasn't initialized when calling updateBusStop");
*/
    void updateBusStop(double t);


/**
 * check if the busstop is valid
 * @param road: the road of the busstop
 * @return: none
\n REQUIRE(properlyInitialized(), "World wasn't initialized when calling updateWorld);
*/
    void isvalid(Road* road);

/////////////
/**
 * get the road where the BusStop is positioned
 * @return: (Road*), the road where the BusStop is positioned
\n REQUIRE(properlyInitialized(), "BusStop wasn't initialized when calling getRoad");
*/
        Road* getRoad();

    protected:
/**
 * change the road of the BusStop
 * @param road: the new road of the BusStop
 * @return: None
\n REQUIRE(properlyInitialized(), "BusStop wasn't initialized when calling setRoad");
*/
        void setRoad(Road* road);

    public:
/**
 * get the position of the BusStop on the road
 * @return: (double), the position of the BusStop on the road
\n REQUIRE(properlyInitialized(), "BusStop wasn't initialized when calling getPosition");
*/
        double getPosition();
/**
 * change the position of the BusStop
 * @param position: the new position of the BusStop
 * @return: None
\n REQUIRE(properlyInitialized(), "BusStop wasn't initialized when calling setPosition");
*/
        void setPosition(double position);
/**
 * get the stoptime of the Busstop
 * @return: (double), the stoptime of the Busstop
\n REQUIRE(properlyInitialized(), "Busstop wasn't initialized when calling getStopTime");
*/
        double getStopTime();

/**
* get the waittime of the getWaitTime
* @return: (double), the waittime the getWaitTime
\n REQUIRE(properlyInitialized(), "Busstop wasn't initialized when calling getTimeStopped");
*/
        double getTimeStopped();

/////////////
    protected:
        bool properlyInitialized() const;

/////////////
};
#endif //CAR_SIMULATION_BUSSTOP_H
