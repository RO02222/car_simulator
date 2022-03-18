#include "Car.h"
#include "../Basic_Values.h"
#include "../DesignByContract.h"
#include "Road.h"

#include <cmath>

Car::Car(int distance, Road* road) : road(road), distance(distance) {
    _initCheck = this;
    speed = gMaxSpeed;
    acceleration = 0;
    ENSURE(properlyInitialized(),"constructor must end in properlyInitialized state");

}



void Car::updateCar(double t) {
    REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling getDistance");
    double v0 = getSpeed();
    double a = getAcceleration();
    double v1 = v0 + a * t;
    if (v1 < 0) {
        setDistance(distance - pow(v0, 2) / (2 * a));
        setSpeed(0);
    }
    if (getDistance() > road->getLength()) {
        road->removeCars(this);
        return;
    }
    setSpeed(v1);
    setDistance(distance + v0 * t + a * (pow(t, 2) / 2.0));
    if (getDistance() > road->getLength()) {
        road->removeCars(this);
    }
    return;
}



int Car::getDistance() {
    REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling getDistance");
    return distance;
}
void Car::setDistance(int d) {
    REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling setDistance");
    Car::distance = d;
}



double Car::getSpeed() {
    REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling getDistance");
    return speed;
}
void Car::setSpeed(double s) {
    REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling setDistance");
    Car::speed = s;
}

double Car::getAcceleration() {
    REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling getDistance");
    return acceleration;
}
void Car::setAcceleration(double a) {
    REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling setDistance");
    Car::acceleration = a;
}





//////////////
bool Car::properlyInitialized() {
    return _initCheck == this;
}
//////////////