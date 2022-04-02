//============================================================================
// Name        : Car_SimDomainTest.cpp
// Date        : 19/03/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 1
//============================================================================

#include "Light.h"
#include "Car.h"
#include "Road.h"
#include "../Basic_Values.h"
#include "../DesignByContract.h"

Light::Light(double position, double c, Road* r): road(r), position(position), cycle(c) {
    _initCheck = this;
    if (c < 1){
        cycle = 1;
    }
    lastCycle = 0;
    state = red;
    ENSURE(this->properlyInitialized(), "constructor must end in properlyInitialized state");
}

void Light::updateLight(double t) {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling updateLight");
    lastCycle += t;
    if (lastCycle > cycle) {
        lastCycle -= cycle;
        if (getState() == green) {
            setState(red);
        } else {
            setState(green);
        }
    }
    std::vector<Car *> carsOnRoad = getRoad()->getCars();
    Car *firstCar = NULL;
    for (std::vector<Car *>::iterator itC = carsOnRoad.begin(); itC != carsOnRoad.end(); itC++) {
        if ((*itC)->getDistance()< getPosition()){
            if ((*itC)->getDistance() + gStopDistance < getPosition() or (*itC)->getAction() == slow or (*itC)->getAction() == stop){
                if (firstCar == NULL or (*itC)->getDistance() > firstCar->getDistance()) {
                    firstCar = (*itC);
                }
            }
        }
    }
    if (firstCar == NULL) {
        return;
    }
    if (getState() == green) {
        firstCar->setAction(fast);
        return;
    }
    if (getState() == red) {
        if ((firstCar->getDistance() + gStopDistance) > getPosition()) {
            firstCar->setAction(stop);
            return;
        } else if ((firstCar->getDistance() + gBreakDistance) > getPosition()) {
            firstCar->setAction(slow);
        }
    }
    return;
}














/////////////

Road* Light::getRoad() {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling getRoad");
    return road;
}


void Light::setRoad(Road *r) {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling setRoad");
    Light::road = r;
}


double Light::getPosition() {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling getPosition");
    return position;
}


void Light::setPosition(double p) {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling setPosition");
    Light::position = p;
}


double Light::getCycle() {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling getCycle");
    return cycle;
}


void Light::setCycle(double c) {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling setCycle");
    Light::cycle = c;
}


color Light::getState() {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling getState");
    return state;
}


void Light::setState(color s) {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling setState");
    Light::state = s;
}
/////////////



//////////////

bool Light::properlyInitialized () const{
    return _initCheck == this;
}
//////////////