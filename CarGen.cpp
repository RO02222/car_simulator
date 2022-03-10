#include "CarGen.h"
#include "DesignByContract.h"

CarGen::CarGen(Road* road,int frequency) : road(road), frequency(frequency) {
    _initCheck = this;
    ENSURE(properlyInitialized(),"constructor must end in properlyInitialized state");

}

int CarGen::getFrequency() {
    REQUIRE(this->properlyInitialized(), "CarGen wasn't initialized when calling getFrequency");

    return frequency;
}
void CarGen::setFrequency(int frequency) {
    REQUIRE(this->properlyInitialized(), "CarGen wasn't initialized when calling setFrequency");
    CarGen::frequency = frequency;
}

Road *CarGen::getRoad() {
    REQUIRE(this->properlyInitialized(), "CarGen wasn't initialized when calling getRoad");
    return road;
}
void CarGen::setRoad(Road *road) {
    REQUIRE(this->properlyInitialized(), "CarGen wasn't initialized when calling setRoad");
    CarGen::road = road;
}




//////////////
bool CarGen::properlyInitialized() {
    return _initCheck == this;
}
//////////////