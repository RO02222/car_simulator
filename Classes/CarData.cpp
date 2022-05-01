//
// Created by robbe on 05.04.22.
//

#include "CarData.h"
#include "Car.h"
#include "../Basic_Values.h"
#include "../DesignByContract.h"

CarData::CarData(Type type) {
    _initCheck = this;
    switch (type) {
        case bus:
            this->type = type;
            priority = false;
            l = 12;
            vMax = 11.4;
            aMax = 1.22;
            bMax = 4.29;
            fMin = 12;
            return;
        case fire:
            this->type = type;
            priority = true;
            l = 10;
            vMax = 14.6;
            aMax = 1.33;
            bMax = 4.56;
            fMin = 10;
            return;
        case ambulance:
            this->type = type;
            priority = false;
            l = 8;
            vMax = 15.5;
            aMax = 1.44;
            bMax = 4.47;
            fMin = 8;
            return;
        case police:
            this->type = type;
            priority = true;
            l = 6;
            vMax = 17.2;
            aMax = 1.55;
            bMax = 4.92;
            fMin = 6;
            return;
        case bugatti:
            this->type = bugatti;
            priority = false;
            l = 4.5;
            vMax = 100.0;
            aMax = 4;
            bMax = 10;
            fMin = 1;
            return;
        default:
            this->type = car;
            priority = false;
            l = 4;
            vMax = 16.6;
            aMax = 1.44;
            bMax = 4.61;
            fMin = 4;
            return;
    }
}



Type CarData::getType() const {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling getType");
    return type;
}

double CarData::getlength() const {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling getlength");
    return l;
}

bool CarData::getpriority() const {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling getpriority");
    return priority;
}

double CarData::getvMax() const {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling getvMax");
    return vMax;
}

double CarData::getaMax() const {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling getaMax");
    return aMax;
}

double CarData::getbMax() const {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling getbMax");
    return bMax;
}

double CarData::getfMin() const {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling getfMin");
    return fMin;
}


//////////////

bool CarData::properlyInitialized () const{
    return _initCheck == this;
}
//////////////