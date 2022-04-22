//============================================================================
// Name        : Car_SimDomainTest.cpp
// Date        : 19/03/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 1
//============================================================================

#include "Junction.h"
#include "Car.h"
#include "Road.h"
#include "../Basic_Values.h"
#include "../DesignByContract.h"

Junction::Junction(std::pair<Road *, double> R1, std::pair<Road *, double> R2) : road1(R1), road2(R2){
    _initCheck = this;
    road1.first->addJunction(road1.second,this);
    road2.first->addJunction(road2.second,this);
    ENSURE(this->properlyInitialized(), "constructor must end in properlyInitialized state");
}


/////////////

Road* Junction::getRoad(int n) {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling getRoad");
    if (n == 1) {
        return road1.first;
    }
    return road2.first;
}


void Junction::setRoad(Road *r, int n) {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling setRoad");
    if (n == 1) {
        road1.first = r;
        return;
    }
    road2.first = r;
}


double Junction::getPosition(int n) {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling getPosition");
    if (n == 1) {
        return road1.second;
    }
    return road2.second;
}


void Junction::setPosition(double p, int n) {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling setPosition");
    if (n == 1) {
        road1.second = p;
        return;
    }
    road2.second = p;
}
/////////////



//////////////
bool Junction::properlyInitialized() const{
    return _initCheck == this;
}
//////////////