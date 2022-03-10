#include "CarGen.h"

CarGen::CarGen(Road* road,int frequency)
        : road(road), frequency(frequency) {}

CarGen::~CarGen() {}

int CarGen::getFrequency() const {
    return frequency;
}
void CarGen::setFrequency(int frequency) {
    CarGen::frequency = frequency;
}

Road *CarGen::getRoad() const {
    return road;
}
void CarGen::setRoad(Road *road) {
    CarGen::road = road;
}

