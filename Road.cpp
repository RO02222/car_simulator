#include "Road.h"
#include "Light.h"
#include "Car.h"
#include "DesignByContract.h"

Road::Road(const std::string &name, int length) : name(name), length(length) {
    _initCheck = this;
    lights = {};
    cars = {};
    ENSURE(properlyInitialized(),"constructor must end in properlyInitialized state");
}

const std::string &Road::getName() {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling getName");
    return name;
}
void Road::setName(const std::string &name) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling setName");
    Road::name = name;
}


int Road::getLength() {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling getLength");
    return length;
}
void Road::setLength(int length) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling setLength");
    Road::length = length;
}


const std::vector<Light *> &Road::getLights() {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling getLights");
    return lights;
}
void Road::setLights(const std::vector<Light *> &lights) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling setLights");
    Road::lights = lights;
}
void Road::addLights(int position, int cycle) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling addLights");
    lights.emplace_back(new Light(position, cycle));
}


const std::vector<Car *> &Road::getCars() {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling getCars");
    return cars;
}
void Road::setCars(const std::vector<Car *> &cars) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling setCars");
    Road::cars = cars;
}
void Road::addCars(int distance) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling addCars");
    Road::cars.emplace_back(new Car (distance));
}




//////////////
bool Road::properlyInitialized() {
    return _initCheck == this;
}
//////////////