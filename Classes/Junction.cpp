//============================================================================
// Name        : Car_SimDomainTest.cpp
// Date        : 19/03/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 1
//============================================================================

#include <cmath>
#include <fstream>
#include "Junction.h"
#include "Car.h"
#include "Road.h"
#include "../Basic_Values.h"
#include "../DesignByContract.h"

Junction::Junction(std::vector<std::pair<Road*, double> > roads, std::ofstream* error) : error(error), roads(roads){
    _initCheck = this;
    for (unsigned int i = 0; i < roads.size(); i++){
        roads[i].first->addJunction(std::pair<Junction*,double*> (this,&this->roads[i].second));
    }
    ENSURE(this->properlyInitialized(), "constructor must end in properlyInitialized state");
}


void Junction::updateJunction(double t) {
    REQUIRE(this->properlyInitialized(), "Junction wasn't initialized when calling updateJunction");
    for (unsigned int i = 0; i< cars.size();i++) {
        double oldPos = cars[i]->getDistance();
        cars[i]->updateCar(t, true);
        for (unsigned int j = 0; j < roads.size(); j++) {
            if (roads[j].first == cars[i]->getRoad()) {
                //move car
                if (oldPos < roads[j].second and cars[i]->getDistance() >= roads[j].second) {
                    unsigned int x = rand() % roads.size();
                    while (roads[x].first->getLength() == roads[x].second){
                        x = rand() % roads.size();
                    }
                    if (x != j) {
                        double newPos = cars[i]->getDistance() - roads[j].second + roads[x].second;
                        cars[i]->moveCar(roads[x].first, newPos);
                        break;
                    }
                }
                //check if car is still near
                if (std::abs(cars[i]->getDistance() - roads[j].second) <= gStopDistance) {
                    break;
                }
            }
        }
    }
    cars.clear();
}


void Junction::addCar(Car *car) {
    REQUIRE(this->properlyInitialized(), "Junction wasn't initialized when calling addCar");
    cars.push_back(car);
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


double Junction::getPosition(std::string roadname) {
    REQUIRE(this->properlyInitialized(), "Junction wasn't initialized when calling getPosition");
    for (std::vector<std::pair<Road*,double>>::iterator x = roads.begin(); x != roads.end(); x++){
        if (x->first->getName() == roadname){
            return x->second;
        }
    }
    return roads[0].second;
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