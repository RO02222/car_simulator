#include "CarGen.h"
#include "Road.h"
#include "../DesignByContract.h"

CarGen::CarGen(int f,Road* road) : road(road), frequency(f) {
    _initCheck = this;
    this->road->addCar(0);
    ENSURE(properlyInitialized(),"constructor must end in properlyInitialized state");
}












/////////////
Road *CarGen::getRoad() {
    REQUIRE(this->properlyInitialized(), "CarGen wasn't initialized when calling getRoad");
    return road;
}
void CarGen::setRoad(Road *r) {
    REQUIRE(this->properlyInitialized(), "CarGen wasn't initialized when calling setRoad");
    CarGen::road = r;
}
int CarGen::getFrequency() {
    REQUIRE(this->properlyInitialized(), "CarGen wasn't initialized when calling getFrequency");

    return frequency;
}
void CarGen::setFrequency(int f) {
    REQUIRE(this->properlyInitialized(), "CarGen wasn't initialized when calling setFrequency");
    CarGen::frequency = f;
}
/////////////



//////////////
bool CarGen::properlyInitialized() const{
    return _initCheck == this;
}
//////////////