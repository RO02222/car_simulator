//
// Created by robbe on 3-3-2022.
//

#include "Light.h"

Light::Light(int position, int cycle)
: position(position), cycle(cycle) {}

Light::~Light() {}


int Light::getPosition() const {
    return position;
}
void Light::setPosition(int position) {
    Light::position = position;
}


int Light::getCycle() const {
    return cycle;
}
void Light::setCycle(int cycle) {
    Light::cycle = cycle;
}
