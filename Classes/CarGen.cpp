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
    REQUIRE(t>=0, "Time cannot be negative");
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
    ENSURE(road->properlyInitialized(), "Road is not properly initialised");
    return road;
}


void CarGen::setRoad(Road *r) {
    REQUIRE(this->properlyInitialized(), "CarGen wasn't initialized when calling setRoad");
    REQUIRE(r->properlyInitialized(), "Road is not properly initialised");
    REQUIRE(r->isvalid(), "Road isn't valid");
    CarGen::road = r;
    ENSURE(road == r,"Road hasn't changed");
}


double CarGen::getFrequency() {
    REQUIRE(this->properlyInitialized(), "CarGen wasn't initialized when calling getFrequency");
    ENSURE(frequency>0, "Frequancy cannot be negative or zero");
    return frequency;
}


void CarGen::setFrequency(double f) {
    REQUIRE(this->properlyInitialized(), "CarGen wasn't initialized when calling setFrequency");
    REQUIRE(f>0, "frequency cannot be negative or zero");
    CarGen::frequency = f;
    ENSURE(frequency == f,"Road hasn't changed");
}


double CarGen::getCycle() {
    REQUIRE(this->properlyInitialized(), "CarGen wasn't initialized when calling getCycle");
    ENSURE(lastCycle>=0, "Lastcycle cannot be negative");
    return lastCycle;
}


void CarGen::setCycle(double c) {
    REQUIRE(this->properlyInitialized(), "CarGen wasn't initialized when calling setCycle");
    REQUIRE(c>=0, "Lastcycle cannot be negative");
    CarGen::lastCycle = c;
    ENSURE(lastCycle == c,"Road hasn't changed");
}

CarData* CarGen::getData() {
    REQUIRE(this->properlyInitialized(), "CarGen wasn't initialized when calling getCycle");
    ENSURE(data->properlyInitialized(), "The data is not properly initialised");
    return data;
}
/////////////



//////////////

bool CarGen::properlyInitialized() const{
    return _initCheck == this;
}

bool CarGen::isvalid(Road* r) const{
    if (!properlyInitialized()){
        return false;
    }
    if(road != r){
        return false;
    }
    if(frequency < 1){
        return false;
    }
    if(lastCycle > frequency){
        return false;
    }
    if(lastCycle < 0){
        return false;
    }
    if(data != NULL and !data->properlyInitialized()){
        return false;
    }
    return true;
}
//////////////