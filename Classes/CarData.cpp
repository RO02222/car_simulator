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
            l = gl_bus;
            vMax = gvMax_bus;
            aMax = gaMax_bus;
            bMax = gbMax_bus;
            fMin = gfMin_bus;
            return;
        case fire:
            this->type = type;
            priority = true;
            l = gl_brandweerwagen;
            vMax = gvMax_brandweerwagen;
            aMax = gaMax_brandweerwagen;
            bMax = gbMax_brandweerwagen;
            fMin = gfMin_brandweerwagen;
            return;
        case ambulance:
            this->type = type;
            priority = true;
            l = gl_ziekenwagen;
            vMax = gvMax_ziekenwagen;
            aMax = gaMax_ziekenwagen;
            bMax = gbMax_ziekenwagen;
            fMin = gfMin_ziekenwagen;
            return;
        case police:
            this->type = type;
            priority = true;
            l = gl_politiecombi;
            vMax = gvMax_politiecombi;
            aMax = gaMax_politiecombi;
            bMax = gbMax_politiecombi;
            fMin = gfMin_politiecombi;
            return;
        default:
            this->type = car;
            priority = false;
            l = gl_auto;
            vMax = gvMax_auto;
            aMax = gaMax_auto;
            bMax = gbMax_auto;
            fMin = gfMin_auto;
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