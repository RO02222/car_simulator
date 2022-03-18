//
// Created by robbe on 3-3-2022.
//

#include "Light.h"
#include "../DesignByContract.h"

Light::Light(double position, double cycle): position(position), cycle(cycle) {
    _initCheck = this;
    if (cycle < 1){
        cycle = 1;
    }
    ENSURE(this->properlyInitialized(), "constructor must end in properlyInitialized state");
}
















/////////////
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
/////////////



//////////////
bool Light::properlyInitialized () const{
    return _initCheck == this;
}
//////////////