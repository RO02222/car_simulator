//============================================================================
// Name        : Car_SimDomainTest.cpp
// Date        : 19/03/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 1
//============================================================================


#include "CarGen.h"
#include "Road.h"
#include "Car.h"
#include "../DesignByContract.h"

CarGen::CarGen(double f,Road* road) : road(road), frequency(f) {
    _initCheck = this;
    if (frequency < 1){
        frequency = 1;
    }
    lastCycle = frequency;
    ENSURE(properlyInitialized(),"constructor must end in properlyInitialized state");
}

/*
 *
 * @param t:
 * @return:
 */
void CarGen::updateCarGen(double t) {
    REQUIRE(this->properlyInitialized(), "Light wasn't initialized when calling updateCarGen");
    lastCycle += t;
    if (lastCycle < frequency) {
        return;
    }
    lastCycle -= frequency;
    std::vector<Car *> carsOnRoad = getRoad()->getCars();
    for (std::vector<Car *>::iterator itC = carsOnRoad.begin(); itC != carsOnRoad.end(); itC++) {
        if ((*itC)->getDistance() <= 2) {
            return;
        }
    }
    getRoad()->addCar(0);
}









/////////////
/*
 *
 * @return:
 */
Road *CarGen::getRoad() {
    REQUIRE(this->properlyInitialized(), "CarGen wasn't initialized when calling getRoad");
    return road;
}

/*
 *
 * @param r:
 * @return:
 */
void CarGen::setRoad(Road *r) {
    REQUIRE(this->properlyInitialized(), "CarGen wasn't initialized when calling setRoad");
    CarGen::road = r;
}

/*
 *
 * @return:
 */
double CarGen::getFrequency() {
    REQUIRE(this->properlyInitialized(), "CarGen wasn't initialized when calling getFrequency");
    return frequency;
}

/*
 *
 * @param f:
 * @return:
 */
void CarGen::setFrequency(double f) {
    REQUIRE(this->properlyInitialized(), "CarGen wasn't initialized when calling setFrequency");
    CarGen::frequency = f;
}

/*
 *
 * @return:
 */
double CarGen::getCycle() {
    REQUIRE(this->properlyInitialized(), "CarGen wasn't initialized when calling getCycle");
    return lastCycle;
}

/*
 *
 * @param c:
 * @return:
 */
void CarGen::setCycle(double c) {
    REQUIRE(this->properlyInitialized(), "CarGen wasn't initialized when calling setCycle");
    CarGen::lastCycle = c;
}
/////////////



//////////////
/*
 *
 * @return:
 */
bool CarGen::properlyInitialized() const{
    return _initCheck == this;
}
//////////////