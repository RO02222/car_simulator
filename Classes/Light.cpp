//
// Created by robbe on 3-3-2022.
//

#include "Light.h"
#include "../DesignByContract.h"

Light::Light(double position, double c, Road* r): road(r), position(position), cycle(c) {
    _initCheck = this;
    if (cycle < 1){
        cycle = 1;
    }
    lastCycle = 0;
    state = green;
    ENSURE(this->properlyInitialized(), "constructor must end in properlyInitialized state");
}

void Light::updateLight(double t) {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling updateLight");
    if (lastCycle > cycle){
        if (state == green){
            state = red;
        } else{
            state = green;
        }
    }
    if (state == green){


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
/////////////



//////////////
bool Light::properlyInitialized () const{
    return _initCheck == this;
}
//////////////