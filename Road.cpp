//
// Created by robbe on 3-3-2022.
//

#include "Road.h"
#include "Light.h"
#include "Car.h"

Road::Road(const std::string &name, int length)
: name(name), length(length) {
    lights = {};
    cars = {};
}

Road::~Road() {
    for (Light* light : lights){
        delete light;
    }
    for (Car* car : cars){
        delete car;
    }
}

const std::string &Road::getName() const {
    return name;
}
void Road::setName(const std::string &name) {
    Road::name = name;
}


int Road::getLength() const {
    return length;
}
void Road::setLength(int length) {
    Road::length = length;
}


const std::vector<Light *> &Road::getLights() const {
    return lights;
}
void Road::setLights(const std::vector<Light *> &lights) {
    Road::lights = lights;
}
void Road::addLights(int position, int cycle) {
    lights.emplace_back(new Light(position, cycle));
}


const std::vector<Car *> &Road::getCars() const {
    return cars;
}
void Road::setCars(const std::vector<Car *> &cars) {
    Road::cars = cars;
}
void Road::addCars(int distance) {
    Road::cars.emplace_back(new Car (distance));
}


