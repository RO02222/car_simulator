//============================================================================
// Name        : Car_SimDomainTest.cpp
// Date        : 19/03/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 1
//============================================================================


#include "Car.h"
#include "../Basic_Values.h"
#include "../DesignByContract.h"
#include "Road.h"
#include <cmath>

Car::Car(double distance, Road* road) : road(road), distance(distance) {
    _initCheck = this;
    speed = gMaxSpeed;
    maxSpeed = gMaxSpeed;
    acceleration = 0;
    action = fast;
    ENSURE(properlyInitialized(),"constructor must end in properlyInitialized state");
}



void Car::updateCar(double t) {
    REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling updateCar");
    if (getAction() == fast) {
        maxSpeed = gMaxSpeed;
    } else if (getAction() == slow) {
        maxSpeed = gSlowFactor * gMaxSpeed;
    }
    double v0 = getSpeed();

    double a;
    if (getAction() != stop) {
        std::vector<Car *> carsOnRoad = getRoad()->getCars();
        Car *nextCar = NULL;
        for (std::vector<Car *>::iterator itC = carsOnRoad.begin(); itC != carsOnRoad.end(); itC++) {
            if ((*itC)->getDistance() > this->getDistance()) {
                if (nextCar == NULL or (*itC)->getDistance() < nextCar->getDistance()) {
                    nextCar = (*itC);
                }
            }
        }
        double delta = 0.0;
        if (nextCar == NULL) {
            delta = 0.0;
        } else {
            double dx = nextCar->getDistance() - getDistance() - gLength;
            double dv = getSpeed() - nextCar->getSpeed();
            delta = (gMinDistance + std::max(0.0, v0 + ((v0 * dv) / (2 * sqrt(gMaxAcceleration * gMaxBrake))))) / dx;
        }
        a = (gMaxAcceleration)*(1.0 - (pow(v0 / getMaxSpeed(), 4)) - pow(delta, 2));
    }else{
        a = -(gMaxBrake*v0)/getMaxSpeed();
    }
    setAcceleration(a);
    double v1 = v0 + a * t;
    if (v1 < 0) {
        setDistance(distance - pow(v0, 2) / (2 * a));
        setSpeed(0);
        return;
    }
    setSpeed(v1);
    setDistance(distance + v0 * t + a * (pow(t, 2) / 2.0));
    if (getDistance() > road->getLength()) {
        road->removeCars(this);
    }
    return;
}





//////////////
Road *Car::getRoad() const {
    REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling getRoad");
    return road;
}
void Car::setRoad(Road *r) {
    REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling setRoad");
    Car::road = r;
}
double Car::getDistance() {
    REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling getDistance");
    return distance;
}
void Car::setDistance(double d) {
    REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling setDistance");
    Car::distance = d;
}
double Car::getSpeed() {
    REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling getSpeed");
    return speed;
}
void Car::setSpeed(double s) {
    REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling setSpeed");
    Car::speed = s;
}
double Car::getMaxSpeed() {
    REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling getMaxSpeed");
    return maxSpeed;
}
void Car::setMaxSpeed(double s) {
    REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling setMaxSpeed");
    Car::maxSpeed = s;
}
double Car::getAcceleration() {
    REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling getAcceleration");
    return acceleration;
}
void Car::setAcceleration(double a) {
    REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling setAcceleration");
    Car::acceleration = a;
}
Action Car::getAction() {
    REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling getAction");
    return action;
}
void Car::setAction(Action a) {
    REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling setAction");
    Car::action = a;
}
//////////////



//////////////
bool Car::properlyInitialized() const{
    return _initCheck == this;
}
//////////////