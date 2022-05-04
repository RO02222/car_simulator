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
#include "CarData.h"
#include "../Basic_Values.h"
#include "../DesignByContract.h"

BusStop::BusStop(double position, double stoptime, Road *road) : road(road), position(position), stoptime(stoptime),
                                                                 currentBus(NULL), bussy(false) {
    _initCheck = this;
    if (this->stoptime < 1) {
        this->stoptime = 1;
    }
    timestopped = 0;
    ENSURE(this->properlyInitialized(), "constructor must end in properlyInitialized state");
}



void BusStop::updateBusStop(double t) {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling updateLight");
    std::vector<Car *> carsOnRoad = getRoad()->getCars();
    Car *firstBus = NULL;
    for (std::vector<Car *>::iterator itC = carsOnRoad.begin(); itC != carsOnRoad.end(); itC++) {
        if ((*itC)->getData()->getType() == bus) {
            if ((*itC)->getDistance() < getPosition()) {
                if ((*itC) == currentBus) {
                    firstBus = (*itC);
                    break;
                }
                if (firstBus == NULL or (*itC)->getDistance() > firstBus->getDistance()) {
                    firstBus = (*itC);
                }
            }
        }
    }
    if (firstBus == NULL) {
        bussy = false;
        return;
    }
    if (firstBus != currentBus){
        bussy = false;
    }
    if (bussy) {
        timestopped += t;
        if (timestopped > stoptime) {
            currentBus->setAction(fast);
        }
        return;
    }
    currentBus = firstBus;
    if (currentBus->getDistance() + gBreakDistance < getPosition()) {
        return;
    }
    if (currentBus->getDistance() + gStopDistance < getPosition()) {
        currentBus->setAction(slow);
        return;
    }
    currentBus->setAction(stop);
    if (currentBus->getSpeed() < 0.01) {
        bussy = true;
        timestopped = 0;
    }
}

void BusStop::isvalid(Road* r) {
    ENSURE(properlyInitialized(), "BusStop not initialized");
    ENSURE(road == r, "BusStop is on a wrong Road");
    ENSURE(position >= gStopDistance, "Position is at least the stopdistance");
    ENSURE(position <= road->getLength(), "Position is of the road");
    ENSURE(stoptime >= 1, "stoptime can not be less than 1");
    ENSURE(timestopped >= 0, "timestoped can not be negative");
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