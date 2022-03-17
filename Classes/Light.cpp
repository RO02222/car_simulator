//
// Created by robbe on 3-3-2022.
//

#include "Light.h"
#include "../DesignByContract.h"

Light::Light(int position, int cycle): position(position), cycle(cycle) {
    _initCheck = this;
    ENSURE(this->properlyInitialized(), "constructor must end in properlyInitialized state");
}

int Light::getPosition() {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling getPosition");
    return position;
}
void Light::setPosition(int p) {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling setPosition");
    Light::position = p;
}


int Light::getCycle() {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling getCycle");
    return cycle;
}
void Light::setCycle(int c) {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling setCycle");
    Light::cycle = c;
}



//////////////
bool Light::properlyInitialized () {
    return _initCheck == this;
}
//////////////