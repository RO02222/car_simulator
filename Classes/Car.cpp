#include "Car.h"
#include "../DesignByContract.h"

Car::Car(int distance) : distance(distance) {
    _initCheck = this;
    ENSURE(properlyInitialized(),"constructor must end in properlyInitialized state");

}

int Car::getDistance() {
    REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling getDistance");
    return distance;
}
void Car::setDistance(int d) {
    REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling setDistance");
    Car::distance = d;
}



int Car::getSpeed() {
    REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling getDistance");
    return speed;
}
void Car::setSpeed(double s) {
    REQUIRE(this->properlyInitialized(), "Car wasn't initialized when calling setDistance");
    Car::speed = s;
}





//////////////
bool Car::properlyInitialized() {
    return _initCheck == this;
}
//////////////