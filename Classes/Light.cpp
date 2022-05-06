//============================================================================
// Name        : Car_SimDomainTest.cpp
// Date        : 19/03/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 1
//============================================================================

#include <cmath>
#include "Light.h"
#include "Car.h"
#include "Road.h"
#include "CarData.h"
#include "../Basic_Values.h"
#include "../DesignByContract.h"

Light::Light(double position, double c, Road* r, std::ofstream* error): error(error), road(r), position(position), cycle(c) {
    _initCheck = this;
    if (c < 1){
        cycle = 1;
    }
    lastCycle = rand() % lround(cycle);
    state = color(rand() % 2);
    clock = true;
    update = true;
    ENSURE(this->properlyInitialized(), "constructor must end in properlyInitialized state");
}

Light::Light(double c, std::ofstream* error): error(error), road(NULL), position(0), cycle(c) {
    _initCheck = this;
    if (c < 1){
        cycle = 1;
    }
    lastCycle = rand() % lround(cycle);
    state = color(rand() % 2);
    clock = true;
    update = false;
    ENSURE(this->properlyInitialized(), "constructor must end in properlyInitialized state");
}

void Light::updateLight(double t) {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling updateLight");
    REQUIRE(t>=0, "Time cannot be negative");
    if (clock) {
        lastCycle += t;
        if (state == green and lastCycle >= cycle){
            lastCycle -= cycle;
            setState(orange);
        }
        if (state == orange and lastCycle >= cycle/10.0){
            lastCycle -= cycle/10.0;
            setState(red);
        }
        if (state == red and lastCycle >= cycle){
            lastCycle -= cycle;
            setState(green);
        }
    }
    if (update) {
        std::vector<Car *> carsOnRoad = getRoad()->getCars();
        Car *firstCar = NULL;
        for (std::vector<Car *>::iterator itC = carsOnRoad.begin(); itC != carsOnRoad.end(); itC++) {
            if (!(*itC)->getData()->getpriority()) {//geen prioriteitsvoertuigen
                if ((*itC)->getDistance() < getPosition()) {//VOOR het licht
                    if (((*itC)->getDistance() + gStopDistance < getPosition() and getState() != orange) or (*itC)->getAction() == slow or
                        (*itC)->getAction() == stop) {
                        if (firstCar == NULL or (*itC)->getDistance() > firstCar->getDistance()) {
                            firstCar = (*itC);
                        }
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
        if (getState() == red or getState() == orange) {
            if ((firstCar->getDistance() + gStopDistance) > getPosition()) {
                if (getState() == red) {
                    firstCar->setAction(stop);
                }
                return;
            } else if ((firstCar->getDistance() + gBreakDistance) > getPosition()) {
                firstCar->setAction(slow);
            }
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


double Light::getLastCycle() {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling getLastCycle");
    return lastCycle;
}


void Light::setLastCycle(double c) {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling setLastCycle");
    Light::lastCycle = c;
}


color Light::getState() {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling getState");
    return state;
}


void Light::setState(color s) {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling setState");
    Light::state = s;
}

bool Light::getClock() {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling getClock");
    ENSURE(clock >= 0.0, "Clock cannot be negative");
    return clock;
}


void Light::setClock(bool s) {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling setState");
    REQUIRE(s >= 0.0, "Clock cannot be negative");
    clock = s;
    ENSURE(clock == s,"clock hasn't changed");
}
/////////////



//////////////

bool Light::properlyInitialized () const{
    return _initCheck == this;
}
//////////////