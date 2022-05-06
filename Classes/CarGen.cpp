//============================================================================
// Name        : Car_SimDomainTest.cpp
// Date        : 19/03/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 1
//============================================================================

#include <stdlib.h>
#include <cmath>
#include "CarGen.h"
#include "Road.h"
#include "Car.h"
#include "CarData.h"
#include "../DesignByContract.h"

CarGen::CarGen(double frequency, Road *road, CarData *data) : road(road), frequency(frequency), random(false), data(data), AllData(NULL) {
    _initCheck = this;
    if (frequency < 1){
        frequency = 1;
    }
    lastCycle = rand() % lround(frequency);
    ENSURE(properlyInitialized(),"constructor must end in properlyInitialized state");
}

CarGen::CarGen(double frequency, Road *road, std::vector<CarData *>* allData)  : road(road), frequency(frequency), random(true), data(NULL), AllData(allData)  {
    _initCheck = this;
    if (frequency < 1){
        frequency = 1;
    }
    lastCycle = frequency;
    ENSURE(properlyInitialized(),"constructor must end in properlyInitialized state");
}


void CarGen::updateCarGen(double t) {
    REQUIRE(this->properlyInitialized(), "CarGen wasn't initialized when calling updateCarGen");
    lastCycle += t;
    if (lastCycle < frequency) {
        return;
    }
    lastCycle -= frequency;
    if (random){
        unsigned int v1 = rand() % 10;
        if (v1 < 6){
            data = (*AllData)[v1];
        } else {
            for (std::vector<CarData *>::iterator alldata = (*AllData).begin();
                 alldata != (*AllData).end(); alldata++) {
                if ((*alldata)->getType() == car) {
                    data = *alldata;
                    continue;
                }
            }
        }
        if (data == NULL){
            data = (*AllData)[0];
        }
    }
    std::vector<Car *> carsOnRoad = getRoad()->getCars();
    for (std::vector<Car *>::iterator itC = carsOnRoad.begin(); itC != carsOnRoad.end(); itC++) {
        if ((*itC)->getDistance() <= 2*(*itC)->getData()->getlength()) {
            return;
        }
    }
    getRoad()->addCar(0, data);
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


double CarGen::getFrequency() {
    REQUIRE(this->properlyInitialized(), "CarGen wasn't initialized when calling getFrequency");
    return frequency;
}


void CarGen::setFrequency(double f) {
    REQUIRE(this->properlyInitialized(), "CarGen wasn't initialized when calling setFrequency");
    CarGen::frequency = f;
}


double CarGen::getCycle() {
    REQUIRE(this->properlyInitialized(), "CarGen wasn't initialized when calling getCycle");
    return lastCycle;
}


void CarGen::setCycle(double c) {
    REQUIRE(this->properlyInitialized(), "CarGen wasn't initialized when calling setCycle");
    CarGen::lastCycle = c;
}

CarData* CarGen::getData() {
    REQUIRE(this->properlyInitialized(), "CarGen wasn't initialized when calling getCycle");
    return data;
}
/////////////



//////////////

bool CarGen::properlyInitialized() const{
    return _initCheck == this;
}
//////////////