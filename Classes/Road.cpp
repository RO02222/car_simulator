//============================================================================
// Name        : Car_SimDomainTest.cpp
// Date        : 19/03/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 1
//============================================================================

#include <cmath>
#include "Road.h"
#include "Light.h"
#include "Car.h"
#include "CarGen.h"
#include "BusStop.h"
#include "Junction.h"
#include "../DesignByContract.h"
#include "../Basic_Values.h"

Road::Road(const std::string &name, double l, std::ofstream* error) : error(error), name(name), length(l)  {
    _initCheck = this;
    if (l < 1){
        length = 1;
    }
    ENSURE(properlyInitialized(),"constructor must end in properlyInitialized state");
}

Road::~Road() {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling ~Road");
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
    std::vector<BusStop *> busStopIt = getBusStops();
    for (std::vector<BusStop *>::iterator itB = busStopIt.begin(); itB != busStopIt.end(); itB++) {
        delete(*itB);
    }
}


void Road::updateRoad(double t) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling updateRoad");
    std::vector<Car *> carIt = getCars();
    for (std::vector<Car *>::iterator itC = carIt.begin(); itC != carIt.end(); itC++) {
        bool update = true;
        for (unsigned int i = 0; i < junctions.size(); i++) {
            if (std::abs((*itC)->getDistance() - *junctions[i].second) <= gStopDistance) {
                update = false;
                junctions[i].first->addCar(*itC);
                break;
            }
        }
        if (update) {
            (*itC)->updateCar(t);
        }
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



void Road::deleteCar(Car* car) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling removeCars");
    std::vector<Car *> carIt = getCars();
    for (unsigned int i = 0; i<cars.size();i++) {
        if (cars[i] == car){
            cars.erase(cars.begin()+i);
            delete car;
            return;
        }
    }
}

void Road::removeCar(Car* car) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling removeCars");
    std::vector<Car *> carIt = getCars();
    for (unsigned int i = 0; i<cars.size();i++) {
        if (cars[i] == car){
            cars.erase(cars.begin()+i);
            return;
        }
    }
}

void Road::isvalid() {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling ~Road");
    ENSURE(properlyInitialized(), "Road not initialized");
    ENSURE(length >= gStopDistance, "Road to short");
    std::vector<Car *> carIt = getCars();
    for (std::vector<Car *>::iterator itC = carIt.begin(); itC != carIt.end(); itC++) {
        (*itC)->isvalid(this);
    }
    std::vector<Light *> lightIt = getLights();
    for (std::vector<Light *>::iterator itL = lightIt.begin(); itL != lightIt.end(); itL++) {
        (*itL)->isvalid(this);
    }
    std::vector<CarGen *> carGenIt = getCarGen();
    for (std::vector<CarGen *>::iterator itG = carGenIt.begin(); itG != carGenIt.end(); itG++) {
        (*itG)->isvalid(this);
        for (std::vector<CarGen *>::iterator itG2 = carGenIt.begin(); itG2 != carGenIt.end(); itG2++){
            if (itG == itG2){
                continue;
            }
        }
    }
    std::vector<BusStop *> busStopIt = getBusStops();
    for (std::vector<BusStop *>::iterator itB = busStopIt.begin(); itB != busStopIt.end(); itB++) {
        (*itB)->isvalid(this);
    }
}


/////////////

void Road::addLight(double position, double cycle) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling addLight");
    if (position > getLength() or position < 0) {
        *error<<"Failed to add light: position is not on the road"<<std::endl;
        return;
    }
    lights.push_back(new Light(position, cycle,this, error));
}

void Road::addCar(double distance, CarData* data) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling addCar");
    if (distance > getLength() or distance < 0) {
        *error<<"Failed to add car: position is not on the road"<<std::endl;
        return;
    }
    Road::cars.push_back(new Car (distance, data, this));
}

void Road::addCar(Car *car) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling addCar");
    cars.push_back(car);
    car->setRoad(this);
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
        *error<<"Failed to add BusStop: position is not on the road"<<std::endl;
        return;
    }
    busStops.push_back(new BusStop(position, stoptime, this));
}


void Road::addJunction(std::pair<Junction*, double*> junction) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling addJuction");
    if (*junction.second > getLength() or *junction.second < 0) {
        *error<<"Failed to add Junction: position is not on the road"<<std::endl;
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


const std::vector<std::pair<Junction *, double *> > &Road::getJunctions() {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling getJunctions");
    return junctions;
}


void Road::setJunctions(const std::vector<std::pair<Junction *, double *> > &Junctions) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling setJunctions");
    Road::junctions = Junctions;
}
/////////////



//////////////
bool Road::properlyInitialized() const{
    return _initCheck == this;
}
//////////////