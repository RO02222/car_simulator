#include "Road.h"
#include "Light.h"
#include "Car.h"
#include "../DesignByContract.h"

Road::Road(const std::string &name, int length) : name(name), length(length) {
    _initCheck = this;
    ENSURE(properlyInitialized(),"constructor must end in properlyInitialized state");
}

const std::string &Road::getName() {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling getName");
    return name;
}
void Road::setName(const std::string &n) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling setName");
    Road::name = n;
}


int Road::getLength() {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling getLength");
    return length;
}
void Road::setLength(int l) {
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
void Road::addLights(int position, int cycle) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling addLights");
    lights.push_back(new Light(position, cycle));
}


const std::vector<Car *> &Road::getCars() {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling getCars");
    return cars;
}
void Road::setCars(const std::vector<Car *> &c) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling setCars");
    Road::cars = c;
}
void Road::addCars(int distance) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling addCars");
    Road::cars.push_back(new Car (distance,this));
}
void Road::removeCars(Car* carToDelete) {
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




//////////////
bool Road::properlyInitialized() {
    return _initCheck == this;
}
//////////////