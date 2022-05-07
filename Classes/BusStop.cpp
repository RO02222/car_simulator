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
    REQUIRE(t>=0, "Time cannot be negative");
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






/////////////

Road* BusStop::getRoad() {
    REQUIRE(this->properlyInitialized(), "BusStop wasn't initialized when calling getRoad");
    ENSURE(road->properlyInitialized(), "Road is not properly initialised");
    return road;
}


void BusStop::setRoad(Road *r) {
    REQUIRE(this->properlyInitialized(), "BusStop wasn't initialized when calling setRoad");
    REQUIRE(r->properlyInitialized(), "Road is not properly initialised");
    REQUIRE(r->isvalid(),"Road isn't valid");
    BusStop::road = r;
    ENSURE(road == r,"Road hasn't changed");
}


double BusStop::getPosition() {
    REQUIRE(this->properlyInitialized(), "BusStop wasn't initialized when calling getPosition");
    ENSURE(onRoad(), "Busstop is not on road");
    return position;
}


void BusStop::setPosition(double p) {
    REQUIRE(this->properlyInitialized(), "BusStop wasn't initialized when calling setPosition");
    REQUIRE(onRoad(p), "Busstop is not on road");
    BusStop::position = p;
    ENSURE(position == p,"Position hasn't changed");
}


double BusStop::getStopTime() {
    REQUIRE(this->properlyInitialized(), "BusStop wasn't initialized when calling getStopTime");
    ENSURE(stoptime>=0, "stoptime cannot be negative");
    return stoptime;
}


double BusStop::getTimeStopped() {
    REQUIRE(this->properlyInitialized(), "BusStop wasn't initialized when calling getTimeStopped");
    ENSURE(timestopped>=0, "Timestopped cannot be negative");
    return timestopped;
}


bool BusStop::getbussy() {
    REQUIRE(this->properlyInitialized(), "BusStop wasn't initialized when calling getbussy");
    return bussy;
}


void BusStop::setbussy(bool b) {
    REQUIRE(this->properlyInitialized(), "BusStop wasn't initialized when calling setbussy");
    bussy = b;
    ENSURE(bussy==b, "Bussy hasn't changed");
}

/////////////



//////////////

bool BusStop::properlyInitialized () const{
    return _initCheck == this;
}

bool BusStop::onRoad() const {
    REQUIRE(road->properlyInitialized(), "Road wasn't initialized when calling onRoad");
    if (position < 0 or position > road->getLength()) {
        return false;
    }
    return true;
}

bool BusStop::onRoad(int p) const{
    if (p<0 or p>road->getLength()){
        return false;
    }
    return true;
}


bool BusStop::isvalid(Road* r) {
    if(!properlyInitialized()){
        return false;
    }
    if(road != r){
        return false;
    }
    if(position < gStopDistance){
        return false;
    }
    if(!onRoad()){
        return false;
    }
    if(stoptime < 1){
        return false;
    }
    if(timestopped < 0){
        return false;
    }
    if(!currentBus->properlyInitialized()){
        return false;
    }
    return true;
}
//////////////