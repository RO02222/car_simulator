//============================================================================
// Name        : Car_SimDomainTest.cpp
// Date        : 19/03/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 1
//============================================================================


#include "BusStop.h"
#include "Light.h"
#include "Car.h"
#include "Road.h"
#include "../Basic_Values.h"
#include "../DesignByContract.h"

BusStop::BusStop(double position, double stoptime, Road *road) : road(road), position(position), stoptime(stoptime) {
    _initCheck = this;
    if (this->stoptime < 1) {
        this->stoptime = 1;
    }
    timestopped = 0;
    ENSURE(this->properlyInitialized(), "constructor must end in properlyInitialized state");
}


/////////////

Road* BusStop::getRoad() {
    REQUIRE(this->properlyInitialized(), "BusStop wasn't initialized when calling getRoad");
    return road;
}


void BusStop::setRoad(Road *r) {
    REQUIRE(this->properlyInitialized(), "BusStop wasn't initialized when calling setRoad");
    BusStop::road = r;
}


double BusStop::getPosition() {
    REQUIRE(this->properlyInitialized(), "BusStop wasn't initialized when calling getPosition");
    return position;
}


void BusStop::setPosition(double p) {
    REQUIRE(this->properlyInitialized(), "BusStop wasn't initialized when calling setPosition");
    BusStop::position = p;
}


double BusStop::getStopTime() {
    REQUIRE(this->properlyInitialized(), "BusStop wasn't initialized when calling getStopTime");
    return stoptime;
}


double BusStop::getTimeStopped() {
    REQUIRE(this->properlyInitialized(), "BusStop wasn't initialized when calling getTimeStopped");
    return timestopped;
}

/////////////



//////////////

bool BusStop::properlyInitialized () const{
    return _initCheck == this;
}
//////////////