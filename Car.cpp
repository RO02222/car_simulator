//
// Created by robbe on 3-3-2022.
//

#include "Car.h"

Car::Car(int distance)
: distance(distance) {}

Car::~Car() {}


int Car::getDistance() const {
    return distance;
}
void Car::setDistance(int distance) {
    Car::distance = distance;
}
