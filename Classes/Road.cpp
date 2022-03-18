#include "Road.h"
#include "Light.h"
#include "Car.h"
#include "CarGen.h"
#include "../DesignByContract.h"

Road::Road(const std::string &name, double l) : name(name), length(l) {
    _initCheck = this;
    if (l < 1){
        length = 1;
    }
    ENSURE(properlyInitialized(),"constructor must end in properlyInitialized state");
}

void Road::updateRoad(double t) {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling updateWorld");
    std::vector<Car *> carIt = getCars();
    for (std::vector<Car *>::iterator itC = carIt.begin(); itC != carIt.end(); itC++) {
        (*itC)->updateCar(t);
    }
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



/////////////
void Road::addLight(double position, double cycle) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling addLight");
    if (position>getLength()) {
        position = getLength();
    }
    if (position<0){
        position = 0;
    }
    std::vector<Light*> l = getLights();
    lights.push_back(new Light(position, cycle,this));
}

void Road::addCar(double distance) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling addCar");
    if (distance > getLength()) {
        distance = getLength();
    }
    if (distance<0){
        distance = 0;
    }
    Road::cars.push_back(new Car (distance,this));
}

void Road::addCarGen(double frequency) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling addCarGen");
    carGen.push_back(new CarGen(frequency, this));
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
void Road::setCarGen(const std::vector<CarGen *> &cG) {
    REQUIRE(this->properlyInitialized(), "Road wasn't initialized when calling setCarGen");
    Road::carGen = cG;
}
/////////////



//////////////
bool Road::properlyInitialized() const{
    return _initCheck == this;
}
//////////////