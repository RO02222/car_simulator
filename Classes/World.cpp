//
// Created by robbe on 3-3-2022.
//
#include <iostream>
#include <exception>
#include <vector>
#include <iterator>


#include "../Exception/ParserException.h"
#include "../DesignByContract.h"

#include "World.h"
#include "Road.h"
#include "Light.h"
#include "Car.h"
#include "../Functions.h"
#include "../Basic_Values.h"


World::World() {
    _initCheck = this;
    ENSURE(properlyInitialized(),"constructor must end in properlyInitialized state");
    time = 0;
}


void World::simulateWorld(std::ostream & onStream){
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling simulateWorld");
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

void World::updateWorld(double t) {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling updateWorld");
    time += t;
    std::vector<Road *> roadIt = getRoads();
    for (std::vector<Road *>::iterator itR = roadIt.begin(); itR != roadIt.end(); itR++) {
        (*itR)->updateRoad(t);
    }
}



///////////////////////
void World::loadWorld(const char *worldName) {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling loadWorld");
    TiXmlDocument doc;
    if (!doc.LoadFile(worldName)) {
        throw (doc.ErrorDesc());
    }
    TiXmlElement *root = doc.FirstChildElement();
    if (root == NULL) {
        throw (ParserException("Failed to load file: No root element."));
    }
    TiXmlElement *elem = root;
    if ((std::string) elem->Value() != "World") {
        throw (ParserException("Failed to load file: <World> ... </World>"));
    }
    for (TiXmlElement *elem1 = elem->FirstChildElement(); elem1 != 0; elem1 = elem1->NextSiblingElement()) {
        if ((std::string) elem1->Value() == "BAAN") {
            loadRoad(elem1);
        }
    }
    for (TiXmlElement *elem1 = elem->FirstChildElement(); elem1 != NULL; elem1 = elem1->NextSiblingElement()) {
        if ((std::string) elem1->Value() == "BAAN") {
            continue;
        }
        if ((std::string) elem1->Value() == "VERKEERSLICHT") {
            loadLight(elem1);
            continue;
        }
        if ((std::string) elem1->Value() == "VOERTUIG") {
            loadCar(elem1);
            continue;
        }
        if ((std::string) elem1->Value() == "VOERTUIGGENERATOR") {
            loadCarGen(elem1);
            continue;
        }
        std::string error = "Failed to load file: <" + (std::string) elem1->Value() + "> is not valid";
        throw (ParserException(error.c_str()));
    }
}

void World::loadRoad(TiXmlElement* elem1) {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling loadRoad");
    std::string name = "";
    std::string length = "";
    for (TiXmlElement *elem2 = elem1->FirstChildElement(); elem2 != 0; elem2 = elem2->NextSiblingElement()) {
        if ((std::string) elem2->Value() == "naam") {
            name = elem2->GetText();
        } else {
            if ((std::string) elem2->Value() == "lengte") {
                length = elem2->GetText();
            } else {
                std::string error = "Failed to load file: <BAAN> : <" + (std::string) elem2->Value() + "> is not valid";

                throw (ParserException(error.c_str()));
            }
        }
    }
    if (name == "") {
        throw (ParserException("Failed to load file: invalid <BAAN> : 'missing argument' <naam>"));
    }
    if (length == "") {
        throw (ParserException("Failed to load file: invalid <BAAN> : 'missing argument' <lengte>"));
    }
    std::vector<Road*> roadIt = getRoads();
    for (std::vector<Road*>::iterator it = roadIt.begin(); it != roadIt.end(); it++) {
        if ((*it)->getName() == name) {
            throw (ParserException("Failed to add road: road already exist"));
        }
    }
    roads.push_back(new Road(name, stringInt(length)));
}

void World::loadLight(TiXmlElement* elem1) {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling loadLight");
    std::string roadName = "";
    std::string position = "";
    std::string cycle = "";
    for (TiXmlElement *elem2 = elem1->FirstChildElement(); elem2 != 0; elem2 = elem2->NextSiblingElement()) {
        if ((std::string) elem2->Value() == "baan") {
            roadName = elem2->GetText();
        } else {
            if ((std::string) elem2->Value() == "positie") {
                position = elem2->GetText();
            } else {
                if ((std::string) elem2->Value() == "cyclus") {
                    cycle = elem2->GetText();
                } else {
                    std::string error =
                            "Failed to load file: <VERKEERSLICHT> : <" + (std::string) elem2->Value() +
                            "> is not valid";
                    throw (ParserException(error.c_str()));
                }
            }
        }
    }
    if (roadName == "") {
        throw (ParserException("Failed to load file: invalid <VERKEERSLICHT> : 'missing argument' <baan>"));
    }
    if (position == "") {
        throw (ParserException("Failed to load file: invalid <VERKEERSLICHT> : 'missing argument' <positie>"));
    }
    if (cycle == "") {
        throw (ParserException("Failed to load file: invalid <VERKEERSLICHT> : 'missing argument' <cyclus>"));
    }
    Road *road = NULL;
    std::vector<Road*> roadIt = getRoads();
    for (std::vector<Road*>::iterator it = roadIt.begin(); it != roadIt.end(); it++) {

        if ((*it)->getName() == roadName) {
            road = (*it);
            break;
        }
    }
    if (road == NULL){
        throw (ParserException("Failed to load file: invalid <VERKEERSLICHT> : '<baan>' does not exist"));
    }
    if (stringInt (position) > road->getLength()){
        throw (ParserException("Failed to load file: invalid <VERKEERSLICHT> : '<baan> is not long enough"));
    }
    road->addLight(stringInt(position),stringInt(cycle));
}

void World::loadCar(TiXmlElement *elem1) {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling loadCar");
    std::string roadName = "";
    std::string position = "";
    for (TiXmlElement *elem2 = elem1->FirstChildElement(); elem2 != 0; elem2 = elem2->NextSiblingElement()) {
        if ((std::string) elem2->Value() == "baan") {
            roadName = elem2->GetText();
        } else {
            if ((std::string) elem2->Value() == "positie") {
                position = elem2->GetText();
            } else {
                std::string error =
                        "Failed to load file: <VOERTUIG> : <" + (std::string) elem2->Value() + "> is not valid";
                throw (ParserException(error.c_str()));
            }
        }
    }
    if (roadName == "") {
        throw (ParserException("Failed to load file: invalid <VOERTUIG> : 'missing argument' <baan>"));
    }
    if (position == "") {
        throw (ParserException("Failed to load file: invalid <VOERTUIG> : 'missing argument' <positie>"));
    }
    Road *road = 0;
    std::vector<Road*> roadIt = getRoads();
    for (std::vector<Road*>::iterator it = roadIt.begin(); it != roadIt.end(); it++) {
        if ((*it)->getName() == roadName) {
            road = (*it);
            break;
        }
        throw (ParserException("Failed to load file: invalid <VOERTUIG> : '<baan> does not exist"));
    }
    if (stringInt (position) > road->getLength()){
        throw (ParserException("Failed to load file: invalid <VOERTUIG> : '<baan> is not long enough"));
    }
    road->addCar(stringInt(position));
}

void World::loadCarGen(TiXmlElement *elem1) {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling loadCarGen");
    std::string roadName = "";
    std::string frequency = "";
    for (TiXmlElement *elem2 = elem1->FirstChildElement(); elem2 != 0; elem2 = elem2->NextSiblingElement()) {
        if ((std::string) elem2->Value() == "baan") {
            roadName = elem2->GetText();
        } else {
            if ((std::string) elem2->Value() == "frequentie") {
                frequency = elem2->GetText();
            } else {
                std::string error =
                        "Failed to load file: <VOERTUIGGENERATOR> : <" + (std::string) elem2->Value() + "> is not valid";
                throw (ParserException(error.c_str()));
            }
        }
    }
    if (roadName == "") {
        throw (ParserException("Failed to load file: invalid <VOERTUIGGENERATOR> : 'missing argument' <baan>"));
    }
    if (frequency == "") {
        throw (ParserException("Failed to load file: invalid <VOERTUIGGENERATOR> : 'missing argument' <frequentie>"));
    }
    Road *road = 0;
    std::vector<Road*> roadIt = getRoads();
    for (std::vector<Road*>::iterator it = roadIt.begin(); it != roadIt.end(); it++) {
        if ((*it)->getName() == roadName) {
            road = (*it);
            break;
        }
        throw (ParserException("Failed to load file: invalid <VOERTUIGGENERATOR> : '<baan> does not exist"));
    }
    if (stringInt (frequency) > road->getLength()){
        throw (ParserException("Failed to load file: invalid <VOERTUIGGENERATOR> : '<baan> is not long enough"));
    }
    road->addCarGen(stringInt(frequency));
}
///////////////////////



//////////////
const std::vector<Road *> &World::getRoads() {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling getRoads");
    return roads;
}

void World::setRoad(const std::vector<Road *> &banen) {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling setRoad");
    World::roads = banen;
}

double World::getTime() const {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling getTime");
    return time;
}

void World::setTime(double t) {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling setTime");
    World::time = t;
}
//////////////



//////////////
bool World::properlyInitialized () const{
    return _initCheck == this;
}
//////////////





