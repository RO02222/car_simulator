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
#include "Light.h"
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
    REQUIRE(t>=0, "Time cannot be negative");
    for (unsigned int i = 0; i < cars.size(); i++) {
        double oldPos = cars[i]->getDistance();
        cars[i]->updateCar(t, true);
        for (unsigned int j = 0; j < roads.size(); j++) {
            if (roads[j].first == cars[i]->getRoad()) {
                //move car
                if (oldPos < roads[j].second and cars[i]->getDistanceNV() >= roads[j].second) {
                    unsigned int x = rand() % roads.size();
                    while (roads[x].first->getLength() == roads[x].second) {

                        x = rand() % roads.size();
                    }
                    if (x != j) {
                        double newPos = cars[i]->getDistanceNV() - roads[j].second + roads[x].second;
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
        if (!cars[i]->onRoad()){
            cars[i]->getRoad()->deleteCar(cars[i]);
        }
    }
    cars.clear();
    //update lights
    if (lights.size() != 0) {
        clock->updateLight(t);
        lights[numLight]->setState(clock->getState());
        if (clock->getState() == red) {
            clock->setState(green);
            numLight = (numLight + 1)%lights.size();
            lights[numLight]->setState(clock->getState());
        }
    }
}


void Junction::addCar(Car *car) {
    REQUIRE(this->properlyInitialized(), "Junction wasn't initialized when calling addCar");
    cars.push_back(car);
}

void Junction::checkJunctionLights() {
    double cycle = 0;
    std::vector<Light*> light;
    for (std::vector<std::pair<Road*,double> >::iterator itR = roads.begin(); itR != roads.end(); itR++){
        if ((*itR).second == 0){
            continue;
        }
        std::vector<Light*> L = (*itR).first->getLights();
        bool lightOnRoad = false;
        for (std::vector<Light*>::iterator itL = L.begin();itL != L.end(); itL++){
            if ((*itL)->getPosition() == (itR->second)){
                if (cycle == 0){
                    cycle = (*itL)->getCycle();
                }
                lightOnRoad = true;
                light.push_back(*itL);
                break;
            }
        }
        if (!lightOnRoad){
            return;
        }
    }
    if (cycle == 0 or light.size() < 2){
        return;
    }
    lights = light;
    clock = new Light(cycle,error);
    clock->setState(green);
    numLight = 0;
    for (std::vector<Light*>::iterator itL = lights.begin(); itL != lights.end(); itL++){
        (*itL)->setClock(false);
        (*itL)->setState(red);
    }
    lights[numLight]->setState(clock->getState());
}


/////////////

Road* Junction::getRoad(int n) {
    REQUIRE(this->properlyInitialized(), "Junction wasn't initialized when calling getRoad");
    return roads[n].first;
}


std::vector<Car*> Junction::getCars() {
    REQUIRE(this->properlyInitialized(), "Junction wasn't initialized when calling getCars");
    return cars;
}


void Junction::setRoad(Road *r,unsigned int n) {
    REQUIRE(this->properlyInitialized(), "Junction wasn't initialized when calling setRoad");
    roads[n].first = r;
}


double Junction::getPosition(int n) {
    REQUIRE(this->properlyInitialized(), "Junction wasn't initialized when calling getPosition");
    return roads[n].second;
}


double Junction::getPosition(std::string roadname) {
    REQUIRE(this->properlyInitialized(), "Junction wasn't initialized when calling getPosition");
    for (std::vector<std::pair<Road*,double> >::iterator x = roads.begin(); x != roads.end(); x++){
        if (x->first->getName() == roadname){
            return x->second;
        }
    }
    return roads[0].second;
}


void Junction::setPosition(double p,unsigned int n) {
    REQUIRE(this->properlyInitialized(), "Junction wasn't initialized when calling setPosition");
    roads[n].second = p;
}
/////////////



//////////////
bool Junction::properlyInitialized() const{
    return _initCheck == this;
}
//////////////