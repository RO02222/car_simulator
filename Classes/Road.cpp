//============================================================================
// Name        : Car_SimDomainTest.cpp
// Date        : 19/03/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 1
//============================================================================


#include "Road.h"
#include "Light.h"
#include "Car.h"
#include "CarGen.h"
#include "BusStop.h"
#include "../DesignByContract.h"

Road::Road(const std::string &name, double l) : name(name), length(l) {
    _initCheck = this;
    if (l < 1){
        length = 1;
    }
    ENSURE(properlyInitialized(),"constructor must end in properlyInitialized state");
}

Road::~Road() {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling ~Road");
    std::vector<Car *> carIt = getCars();
    for (std::vector<Car *>::iterator itC = carIt.begin(); itC != carIt.end(); itC++) {
        delete(*itC);
    }
    std::vector<Light *> lightIt = getLights();
    for (std::vector<Light *>::iterator itL = lightIt.begin(); itL != lightIt.end(); itL++) {
        delete(*itL);
    }
    std::vector<CarGen *> carGenIt = getCarGen();
    for (std::vector<CarGen *>::iterator itG = carGenIt.begin(); itG != carGenIt.end(); itG++) {
        delete(*itG);
    }
    std::vector<BusStop *> busStopsIt = getBusStops();
    for (std::vector<BusStop *>::iterator itB = busStopsIt.begin(); itB != busStopsIt.end(); itB++) {
        delete(*itB);
    }
}


void Road::updateRoad(double t) {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling updateWorld");
    std::vector<Car *> carIt = getCars();
    for (std::vector<Car *>::iterator itC = carIt.begin(); itC != carIt.end(); itC++) {
        (*itC)->updateCar(t);
    }
    std::vector<Light *> lightIt = getLights();
    for (std::vector<Light *>::iterator itL = lightIt.begin(); itL != lightIt.end(); itL++) {
        (*itL)->updateLight(t);
    }
    std::vector<CarGen *> carGenIt = getCarGen();
    for (std::vector<CarGen *>::iterator itG = carGenIt.begin(); itG != carGenIt.end(); itG++) {
        (*itG)->updateCarGen(t);
    }
    for (std::vector<BusStop *>::iterator itB = busStops.begin(); itB != busStops.end(); itB++) {
        (*itB)->updateBusStop(t);
    }
}



void Road::removeCar(Car* carToDelete) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling removeCars");
    std::vector<Car *> carIt = getCars();
    for (unsigned int i = 0; i<cars.size();i++) {
        if (cars[i] == carToDelete){
            cars.erase(cars.begin()+i);
            delete carToDelete;
            return;
        }
    }
}



/////////////

void Road::addLight(double position, double cycle) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling addLight");
    if (position > getLength() or position < 0) {
        std::cerr<<"Failed to add light: position is not on the road"<<std::endl;
        return;
    }
    lights.push_back(new Light(position, cycle,this));
}


void Road::addCar(double distance, CarData* data) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling addCar");
    if (distance > getLength() or distance < 0) {
        std::cerr<<"Failed to add car: position is not on the road"<<std::endl;
        return;
    }
    Road::cars.push_back(new Car (distance, data, this));
}


void Road::addCarGen(double frequency, CarData* data) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling addCarGen");
    if (frequency < 1){
        frequency = 1;
    }
    carGen.push_back(new CarGen(frequency, this, data));
}

void Road::addCarGen(double frequency, std::vector<CarData*>* allData) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling addCarGen");
    if (frequency < 1){
        frequency = 1;
    }
    carGen.push_back(new CarGen(frequency, this, allData));
}


void Road::addBusStop(double position, double stoptime) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling addCarGen");
    if (stoptime < 1){
        stoptime = 1;
    }
    if (position > getLength() or position < 0) {
        std::cerr<<"Failed to add BusStop: position is not on the road"<<std::endl;
        return;
    }
    busStops.push_back(new BusStop(position, stoptime, this));
}


void Road::addJunction(double position, Junction *junction) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling addJuction");
    if (position > getLength() or position < 0) {
        std::cerr<<"Failed to add Junction: position is not on the road"<<std::endl;
        return;
    }
    junctions.push_back( junction );
}
/////////////



/////////////

const std::string &Road::getName() {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling getName");
    return name;
}


void Road::setName(const std::string &n) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling setName");
    Road::name = n;
}


double Road::getLength() {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling getLength");
    return length;
}


void Road::setLength(double l) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling setLength");
    Road::length = l;
}


const std::vector<Light *> &Road::getLights() {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling getLights");
    return lights;
}


void Road::setLights(const std::vector<Light *> &l) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling setLights");
    Road::lights = l;
}


const std::vector<Car *> &Road::getCars() {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling getCars");
    return cars;
}


void Road::setCars(const std::vector<Car *> &c) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling setCars");
    Road::cars = c;
}


const std::vector<CarGen *> &Road::getCarGen()  {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling getCarGen");
    return carGen;
}


void Road::setCarGen(const std::vector<CarGen *> &carGens) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling setCarGen");
    Road::carGen = carGens;
}

const std::vector<BusStop *> &Road::getBusStops() {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling getBusStops");
    return busStops;
}


void Road::setbusStops(const std::vector<BusStop *> &BusStops) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling setBusStops");
    Road::busStops = BusStops;
}
/////////////



//////////////
bool Road::properlyInitialized() const{
    return _initCheck == this;
}
//////////////