//============================================================================
// Name        : Car_SimDomainTest.cpp
// Date        : 19/03/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 1
//============================================================================

#include <iostream>
#include <iomanip>
#include <exception>
#include <vector>
#include <iterator>
#include <cstring>
#include "fstream"
#include "../Exception/ParserException.h"
#include "../DesignByContract.h"
#include "World.h"
#include "Road.h"
#include "Light.h"
#include "Car.h"
#include "Junction.h"
#include "CarData.h"
#include "BusStop.h"
#include "../Functions.h"
#include "../Basic_Values.h"


World::World() {
    error.open("../outputFile/error.txt");
    _initCheck = this;
    time = 0;

    //all carTypes (without none)
    carData.push_back(new CarData(car));
    carData.push_back(new CarData(bus));
    carData.push_back(new CarData(fire));
    carData.push_back(new CarData(ambulance));
    carData.push_back(new CarData(police));
    carData.push_back(new CarData(bugatti));
    ENSURE(properlyInitialized(),"constructor must end in properlyInitialized state");
}


World::~World() {
    REQUIRE(properlyInitialized(), "World wasn't initialized when calling ~World");
    error.close();
    std::vector<Road*> roadIt = getRoads();
    for (std::vector<Road*>::iterator itR = roadIt.begin(); itR != roadIt.end(); itR++) {
        delete (*itR);
    }
    std::vector<Junction*> junctionIT = getJunctions();
    for (std::vector<Junction*>::iterator itJ = junctionIT.begin(); itJ != junctionIT.end(); itJ++) {
        delete (*itJ);
    }
    ///////////////////////
    std::vector<CarData*> carDataIT = carData;
    for (std::vector<CarData*>::iterator itD = carDataIT.begin(); itD != carDataIT.end(); itD++) {
        delete (*itD);
    }
    ////////////////
}

void World::simpleSimulateWorld(std::ostream &onStream) {
    REQUIRE(properlyInitialized(), "World wasn't initialized when calling simpleSimulateWorld");
    REQUIRE(isvalidSimulation(), "Simulation is not valid");
    onStream << "Tijd: " <<time<<std::endl;
    int numVehicle = 1;
    std::vector<Road*> roadIt = getRoads();
    for (std::vector<Road*>::iterator itR = roadIt.begin(); itR != roadIt.end(); itR++) {
        std::vector<Car*> carIt = (*itR)->getCars();
        for (std::vector<Car*>::iterator itC = carIt.begin(); itC != carIt.end(); itC++) {
            onStream << "Voertuig " << numVehicle << std::endl;
            onStream << " -> baan: " << (*itR)->getName() << std::endl;
            onStream << " -> positie: " << (*itC)->getDistance() << std::endl;
            onStream << " -> snelheid: " << (*itC)->getSpeed() << std::endl << std::endl;
            numVehicle +=1;
        }
    }
}

void World::graficImpSimulateWorld(std::ostream &onStream) {
    REQUIRE(properlyInitialized(), "World wasn't initialized when calling graficImpSimulateWorld");
    REQUIRE(isvalidSimulation(), "Simulation is not valid");
    const char separator = ' ';
    unsigned int nameWidth = 17;
    std::vector<Road*> roadIt = getRoads();
    for (std::vector<Road*>::iterator itR = roadIt.begin(); itR != roadIt.end(); itR++) {
        if ((*itR)->getName().size() > nameWidth){
            nameWidth = (*itR)->getName().size();
        }
    }
    nameWidth += 3;
    unsigned int roadlength = 110 - nameWidth;
    //std::cout << "Tijd: " <<time<<std::endl;
    unsigned  int i = 0;
    for (std::vector<Road*>::iterator itR = roadIt.begin(); itR != roadIt.end(); itR++) {
        i++;
        //////////////////
        std::string road = std::string(roadlength,'=');
        std::string light = std::string(roadlength,' ');
        std::string bus = std::string(roadlength,' ');
        std::string junction = std::string(roadlength,' ');
        //////////////////
        const double numWidth = (*itR)->getLength()/roadlength;
        std::vector<Car*> carIt = (*itR)->getCars();
        std::vector<Light*> lightIt = (*itR)->getLights();
        std::vector<BusStop*> busIt = (*itR)->getBusStops();
        //std::vector<BusStop*> JunIt = (*itR)->getJunctions();
        //////////////////
        /*for (std::vector<Junction*>::iterator itJ = busIt.begin(); itJ != busIt.end(); itB++) {
            unsigned int x = floor((*itB)->getPosition()/numWidth);
            if (x >= roadlength){
                x = roadlength -1;
            }
            bus[x] = 'B';
            light[x] = '|';
        }*/
        for (std::vector<BusStop*>::iterator itB = busIt.begin(); itB != busIt.end(); itB++) {
            unsigned int x = floor((*itB)->getPosition()/numWidth);
            if (x >= roadlength){
                x = roadlength -1;
            }
            bus[x] = 'B';
            light[x] = '|';
        }
        for (std::vector<Light*>::iterator itL = lightIt.begin(); itL != lightIt.end(); itL++) {
            unsigned int x = floor((*itL)->getPosition() / numWidth);
            if (x >= roadlength) {
                x = roadlength - 1;
            }
            switch ((*itL)->getState()) {
                case red:
                    light[x] = 'R';
                    continue;
                case orange:
                    light[x] = 'O';
                    continue;
                case green:
                    light[x] = 'G';
                    continue;
            }
        }
        for (std::vector<Car*>::iterator itC = carIt.begin(); itC != carIt.end(); itC++) {
            unsigned int x = lround((*itC)->getDistance()/numWidth);
            if (x >= roadlength){
                x = roadlength -1;
            }
            switch ((*itC)->getData()->getType()) {
                case car:
                    road[x] = 'C';
                    continue;
                case ::bus:
                    road[x] = 'B';
                    continue;
                case fire:
                    road[x] = 'F';
                    continue;
                case police:
                    road[x] = 'P';
                    continue;
                case ambulance:
                    road[x] = 'A';
                    continue;
                case bugatti:
                    road[x] = 'b';
                    continue;
                case none:
                    continue;
            }
        }

#if VERSION == 14
        std::cout << "\033[2J" << "\033[0;0H";
        //////////////////
        std::cout << "\033[1;31m" << std::left << std::setw(nameWidth) << std::setfill(separator) << (*itR)->getName();
        std::cout << "\033[1;35m" << std::left << std::setw(4) << std::setfill(separator) << "|";
        std::cout << "\033[1;36m" << std::left << std::setw(4) << std::setfill(separator) << road << std::endl;
        //////////////////
        std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) <<  "> verkeerslichten";
        std::cout << std::left << std::setw(4) << std::setfill(separator) << "|";
        std::cout << std::left << std::setw(4) << std::setfill(separator) << light << std::endl;
        //////////////////
        std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) <<  "> bushaltes";
        std::cout << std::left << std::setw(4) << std::setfill(separator) << "|";
        std::cout << std::left << std::setw(4) << std::setfill(separator) << bus << std::endl;
        //////////////////
        std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) <<  "> kruispunten";
        std::cout << std::left << std::setw(4) << std::setfill(separator) << "|";
        std::cout << std::left << std::setw(4) << std::setfill(separator) << junction << std::endl;
        //////////////////
        std::cout << std::endl;
        //////////////////
#endif


        //////////////////
        onStream << std::left << std::setw(nameWidth) << std::setfill(separator) << (*itR)->getName();
        onStream << std::left << std::setw(4) << std::setfill(separator) << "|";
        onStream << std::left << std::setw(4) << std::setfill(separator) << road;
        onStream << std::left << std::setw(4) << std::setfill(separator) << "   |" << std::endl;
        //////////////////
        onStream << std::left << std::setw(nameWidth) << std::setfill(separator) <<  "> verkeerslichten";
        onStream << std::left << std::setw(4) << std::setfill(separator) << "|";
        onStream << std::left << std::setw(4) << std::setfill(separator) << light;
        onStream << std::left << std::setw(4) << std::setfill(separator) << "   |" << std::endl;
        //////////////////
        onStream << std::left << std::setw(nameWidth) << std::setfill(separator) <<  "> bushaltes";
        onStream << std::left << std::setw(4) << std::setfill(separator) << "|";
        onStream << std::left << std::setw(4) << std::setfill(separator) << bus;
        onStream << std::left << std::setw(4) << std::setfill(separator) << "   |" << std::endl;
        //////////////////
        onStream << std::endl;
        //////////////////

    }
    onStream << std::endl;
}


void World::updateWorld(double t) {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling updateWorld");
    REQUIRE(isvalidSimulation(), "Simulation is not valid");
    time += t;
    std::vector<Road *> roadIt = getRoads();
    for (std::vector<Road *>::iterator itR = roadIt.begin(); itR != roadIt.end(); itR++) {
        (*itR)->updateRoad(t);
    }
    std::vector<Junction *> junctionIt = getJunctions();
    for (std::vector<Junction *>::iterator itJ = junctionIt.begin(); itJ != junctionIt.end(); itJ++) {
        (*itJ)->updateJunction(t);
    }
    ENSURE(isvalidSimulation(),"Simulation isn't Valid");
}


//////////////

const std::vector<Road *> &World::getRoads() {
    REQUIRE(properlyInitialized(), "World wasn't initialized when calling getRoads");
    for(unsigned int i=0; i<roads.size(); i++){
        ENSURE(roads[i]->properlyInitialized(), "Road is not properly initialised");
    }
    return roads;
}


void World::setRoad(const std::vector<Road *> &banen) {
    REQUIRE(properlyInitialized(), "World wasn't initialized when calling setRoad");
    for(unsigned int i=0; i<banen.size(); i++){
        REQUIRE(banen[i]->properlyInitialized(), "Road not properly initialised");
    }
    World::roads = banen;
    ENSURE(World::roads == banen,"Roads hasn't changed");
}

void World::addRoad(std::string name, double length) {
    REQUIRE(properlyInitialized(), "World wasn't initialized when calling addRoad");
    if (length < 0){
        error<<"Failed to add road: length can't be negative"<<std::endl;
        return;
    }
    for (std::vector<Road *>::iterator it = roads.begin(); it != roads.end(); it++) {
        if ((*it)->getName() == name) {
            error<<"Failed to add road: road already exist"<<std::endl;
            return;
        }
    }
    Road* r = new Road(name,length, &error);
    roads.push_back(r);
    ENSURE(roads[roads.size()-1] == r, "Road is not added");
}

void World::addRoad(Road* r) {
    REQUIRE(properlyInitialized(), "World wasn't initialized when calling addRoad");
    REQUIRE(r->isvalid(), "Road isn't valid");
    for (std::vector<Road *>::iterator it = roads.begin(); it != roads.end(); it++) {
        if ((*it)->getName() == r->getName()) {
            error<<"Failed to add road: road already exist"<<std::endl;
            return;
        }
    }
    roads.push_back(r);
    ENSURE(roads[roads.size()-1] == r, "Road is not added");
}

std::vector<Junction *> &World::getJunctions() {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling getJunctions");
    for(unsigned int i=0; i<junctions.size(); i++){
        ENSURE(junctions[i]->properlyInitialized(), "Junction is not initialised");
    }
    return junctions;
}


void World::setJunctions(const std::vector<Junction *> & junction) {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling setJunctions");
    for(unsigned int i=0; i<junction.size(); i++) {
        REQUIRE(junction[i]->properlyInitialized(), "Junction not properly initialised");
    }
    World::junctions = junction;
    ENSURE(World::junctions == junction,"Junctions hasn't changed");
}


void World::addJunction(std::vector<std::pair<Road* , double> > road) {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling addJuction");
    Junction* j = new Junction(road, &error);
    junctions.push_back(j);
    ENSURE(junctions[junctions.size()-1] == j, "Junction is not added");
}


double World::getTime() const {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling getTime");
    ENSURE(time>=0, "Time cannot be negative");
    return time;
}


void World::setTime(double t) {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling setTime");
    REQUIRE(t>=0, "time cannot be negative");
    World::time = t;
    ENSURE(World::time == t,"Time hasn't changed");
}

CarData* World::getCarData(Type type)  {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling getCarData");
    for (std::vector<CarData*>::iterator data = carData.begin(); data != carData.end(); data++){
        if ((*data)->getType() == type){
            ENSURE((*data)->properlyInitialized(), "Data is not properly initialised");
            return (*data);
        }
    }
    ENSURE(carData[0]->properlyInitialized(), "The cardata is not properly initialised");
    return carData[0];
}

std::vector<CarData*>* World::getAllData() {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling getCarData");
    for(unsigned int i=0; i<carData.size(); i++){
        ENSURE(carData[i]->properlyInitialized(), "Cardata is not properly initialised");
    }
    return &carData;
}
//////////////



//////////////

bool World::properlyInitialized () const{
    return _initCheck == this;
}

bool World::isvalid() const{
    if (!properlyInitialized()){
        return false;
    }
    if (time < 0){
        return false;
    }
    return true;
}

bool World::isvalidSimulation() const {
    if (!isvalid()) {
        return false;
    }
    std::vector<Road *> RoadIt = roads;
    for (std::vector<Road *>::iterator itR = RoadIt.begin(); itR != RoadIt.end(); itR++) {
        if (!(*itR)->isvalid()) {
            return false;
        }
    }
    std::vector<Junction *> junctionIt = junctions;
    for (std::vector<Junction *>::iterator itJ = junctionIt.begin(); itJ != junctionIt.end(); itJ++) {
        if (!(*itJ)->isvalid()) {
            return false;
        }
    }
    return true;
}
//////////////




