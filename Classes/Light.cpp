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
    if (clock and !update){
        REQUIRE(isvalidClock(), "Clock wasn't initialized when calling updateLight");
    } else {
        REQUIRE(isvalid(road), "Light wasn't initialized when calling updateLight");
    }
    REQUIRE(t >= 0, "Time cannot be negative");
    if (clock) {
        double ensureLastCycle = lastCycle;
        lastCycle += t;
        ENSURE(lastCycle == ensureLastCycle + t, "LastCycle hasn't been updated");
        if (state == green and lastCycle >= cycle) {
            lastCycle -= cycle;
            ENSURE(lastCycle == ensureLastCycle + t - cycle, "LastCycle hasn't been updated");
            setState(orange);
        }
        if (state == orange and lastCycle >= cycle / 10.0) {
            lastCycle -= cycle / 10.0;
            ENSURE(lastCycle == ensureLastCycle + t - cycle / 10.0, "LastCycle hasn't been updated");
            setState(red);
        }
        if (state == red and lastCycle >= cycle) {
            lastCycle -= cycle;
            ENSURE(lastCycle == ensureLastCycle + t - cycle, "LastCycle hasn't been updated");
            setState(green);
        }
    }
    if (update) {
        std::vector<Car *> carsOnRoad = getRoad()->getCars();
        Car *firstCar = NULL;
        for (std::vector<Car *>::iterator itC = carsOnRoad.begin(); itC != carsOnRoad.end(); itC++) {
            if (!(*itC)->getData()->getpriority()) {//geen prioriteitsvoertuigen
                if ((*itC)->getDistance() < getPosition()) {//VOOR het licht
                    if (((*itC)->getDistance() + gStopDistance < getPosition() and getState() != orange) or
                        (*itC)->getAction() == slow or
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
        ENSURE(firstCar->isvalid(road), "firstCar isn't valid");
        if (getState() == green) {
            firstCar->setAction(fast);
        } else if (getState() == red or getState() == orange) {
            if ((firstCar->getDistance() + gStopDistance) > getPosition()) {
                if (getState() == red) {
                    firstCar->setAction(stop);
                }
            } else if ((firstCar->getDistance() + gBreakDistance) > getPosition()) {
                firstCar->setAction(slow);
            }
        }
    }
    if (clock and !update){
        REQUIRE(isvalidClock(), "Clock wasn't initialized when calling updateLight");
    } else {
        REQUIRE(isvalid(road), "Light wasn't initialized when calling updateLight");
    }
}







/////////////

Road* Light::getRoad() {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling getRoad");
    ENSURE(road->properlyInitialized(), "Road is not properly initialised");
    return road;
}


void Light::setRoad(Road *r) {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling setRoad");
    REQUIRE(r->properlyInitialized(), "Road is not properly initialised");
    REQUIRE(r->isvalid(), "Road is not valid");
    Light::road = r;
    ENSURE(road == r,"Road hasn't changed");
}


double Light::getPosition() {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling getPosition");
    ENSURE(onRoad(), "Light is not on road");
    return position;
}


void Light::setPosition(double p) {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling setPosition");
    REQUIRE(onRoad(p), "Light not on road");
    Light::position = p;
    ENSURE(position == p,"Position hasn't changed");
}


double Light::getCycle() {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling getCycle");
    ENSURE(cycle>0, "Cycle cannot be negative or zero");
    return cycle;
}


void Light::setCycle(double c) {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling setCycle");
    REQUIRE(c>0, "Cycle cannot be negative or zero");
    Light::cycle = c;
    ENSURE(cycle == c,"Cycle hasn't changed");
}


double Light::getLastCycle() {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling getLastCycle");
    ENSURE(lastCycle>=0, "LastCycle cannot be negative");
    return lastCycle;
}


void Light::setLastCycle(double c) {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling setLastCycle");
    REQUIRE(c>=0, "LastCycle cannot be negative");
    Light::lastCycle = c;
    ENSURE(lastCycle == c,"Lastcycle hasn't changed");
}


color Light::getState() {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling getState");
    ENSURE(state==green or state==red or state==orange, "Color does not exist ");
    return state;
}


void Light::setState(color s) {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling setState");
    REQUIRE(s==green or s==red or s==orange, "Color does not exist ");
    Light::state = s;
    ENSURE(state == s,"State hasn't changed");
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

bool Light::onRoad() const{
    if (position<0 or position>road->getLength()){
        return false;
    }
    return true;
}

bool Light::onRoad(int p) const{
    if (p<0 or p>road->getLength()){
        return false;
    }
    return true;
}

bool Light::isvalid(Road* r) const {
    if(!properlyInitialized()){
        return false;
        }
    if(!r->properlyInitialized()){
        return false;
        }
    if(road != r){
        return false;
    }
    if(!onRoad()){
        return false;
    }
    if(cycle < 1){
        return false;
    }
    if(lastCycle > cycle){
        return false;
    }
    if(lastCycle < 0){
        return false;
    }
    if(state != green and state != red and state != orange){
        return false;
    }
    return true;
}

bool Light::isvalidClock() const {
    if(!properlyInitialized()){
        return false;
    }
    if(!clock or update){
        return false;
    }
    if(cycle < 1){
        return false;
    }
    if(lastCycle > cycle){
        return false;
    }
    if(lastCycle < 0){
        return false;
    }
    if(state != green and state != red and state != orange){
        return false;
    }
    return true;
}
//////////////