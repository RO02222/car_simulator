//============================================================================
// Name        : Car_SimDomainTest.cpp
// Date        : 19/03/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 1
//============================================================================

#include <cmath>
#include "Junction.h"
#include "Car.h"
#include "Road.h"
#include "../Basic_Values.h"
#include "../DesignByContract.h"

Junction::Junction(std::vector<std::pair<Road*, double> > roads) : roads(roads){
    _initCheck = this;
    for (unsigned int i = 0; i < roads.size(); i++){
        roads[i].first->addJunction(std::pair<Junction*,double*> (this,&this->roads[i].second));
    }
    ENSURE(this->properlyInitialized(), "constructor must end in properlyInitialized state");
}


void Junction::updateJunction(double t) {
    REQUIRE(this->properlyInitialized(), "Junction wasn't initialized when calling updateJunction");
    std::vector<std::pair<Car*, bool> > newCars;
    for (unsigned int i = 0; i< cars.size();i++) {
        if (cars[i].second) {
            cars[i].second = false;
            newCars.push_back(cars[i]);
            break;
        }
        double oldPos = cars[i].first->getDistance();
        cars[i].first->updateCar(t, true);
        for (unsigned int j = 0; j < roads.size(); j++) {
            if (roads[j].first == cars[i].first->getRoad()) {
                //move car
                if (oldPos < roads[j].second and cars[i].first->getDistance() > roads[j].second) {
                    unsigned int x = rand() % roads.size();
                    while (roads[x].first->getLength() == roads[x].second){
                        x = rand() % roads.size();
                    }
                    if (x != j) {
                        double newPos = cars[i].first->getDistance() - roads[j].second + roads[x].second;
                        cars[i].first->moveCar(roads[x].first, newPos);
                        newCars.push_back(cars[i]);
                        break;
                    }
                }
                //check if car is still near
                if (std::abs(cars[i].first->getDistance() - roads[j].second) < gStopDistance) {
                    newCars.push_back(cars[i]);
                    break;
                }
            }
        }
    }
    cars = newCars;
}


void Junction::addCar(Car *car, bool updated) {
    REQUIRE(this->properlyInitialized(), "Junction wasn't initialized when calling addCar");
    cars.push_back(std::pair<Car*,bool>(car,updated));
}


/////////////

Road* Junction::getRoad(int n) {
    REQUIRE(this->properlyInitialized(), "Junction wasn't initialized when calling getRoad");
    return roads[n].first;
}


void Junction::setRoad(Road *r, int n) {
    REQUIRE(this->properlyInitialized(), "Junction wasn't initialized when calling setRoad");
    roads[n].first = r;
}


double Junction::getPosition(int n) {
    REQUIRE(this->properlyInitialized(), "Junction wasn't initialized when calling getPosition");
    return roads[n].second;
}


void Junction::setPosition(double p, int n) {
    REQUIRE(this->properlyInitialized(), "Junction wasn't initialized when calling setPosition");
    roads[n].second = p;
}
/////////////



//////////////
bool Junction::properlyInitialized() const{
    return _initCheck == this;
}
//////////////