//
// Created by robbe on 3-3-2022.
//
#include <iostream>
#include <exception>


#include "../Exception/ParserException.h"
#include "../DesignByContract.h"

#include "World.h"
#include "Road.h"
#include "Light.h"
#include "Car.h"


World::World() {
    _initCheck = this;
    roads = {};
    carGen = {};
    ENSURE(properlyInitialized(),"constructor must end in properlyInitialized state");
}

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
    for (TiXmlElement *elem1 = elem->FirstChildElement(); elem1 != nullptr; elem1 = elem1->NextSiblingElement()) {
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
///////////////////////
void World::loadRoad(TiXmlElement* elem1) {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling loadRoad");
    std::string name = "";
    std::string length = "";
    for (TiXmlElement *elem2 = elem1->FirstChildElement(); elem2 != nullptr; elem2 = elem2->NextSiblingElement()) {
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
        throw ("Failed to load file: invalid <BAAN> : 'missing argument' <naam>");
    }
    if (length == "") {
        throw ("Failed to load file: invalid <BAAN> : 'missing argument' <lengte>");
    }
    for (Road *i: getRoads()) {
        if (i->getName() == name) {
            throw ("Failed to add road: road already exist");
        }
    }
    roads.emplace_back(new Road(name, stoi(length)));
}

void World::loadLight(TiXmlElement* elem1) {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling loadLight");
    std::string roadName = "";
    std::string position = "";
    std::string cycle = "";
    for (TiXmlElement *elem2 = elem1->FirstChildElement(); elem2 != nullptr; elem2 = elem2->NextSiblingElement()) {
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
        throw ("Failed to load file: invalid <VERKEERSLICHT> : 'missing argument' <baan>");
    }
    if (position == "") {
        throw ("Failed to load file: invalid <VERKEERSLICHT> : 'missing argument' <positie>");
    }
    if (cycle == "") {
        throw ("Failed to load file: invalid <VERKEERSLICHT> : 'missing argument' <cyclus>");
    }
    Road *road = nullptr;
    for (Road *i: getRoads()) {
        if (i->getName() == roadName) {
            road = i;
            break;
        }
        throw ("Failed to load file: invalid <VERKEERSLICHT> : '<baan> does not exist");
    }
    if (stoi (position) > road->getLength()){
        throw ("Failed to load file: invalid <VERKEERSLICHT> : '<baan> is not long enough");
    }
    road->addLights(stoi(position),stoi(cycle));
}

void World::loadCar(TiXmlElement *elem1) {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling loadCar");
    std::string roadName = "";
    std::string position = "";
    for (TiXmlElement *elem2 = elem1->FirstChildElement(); elem2 != nullptr; elem2 = elem2->NextSiblingElement()) {
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
        throw ("Failed to load file: invalid <VOERTUIG> : 'missing argument' <baan>");
    }
    if (position == "") {
        throw ("Failed to load file: invalid <VOERTUIG> : 'missing argument' <positie>");
    }
    Road *road = nullptr;
    for (Road *i: getRoads()) {
        if (i->getName() == roadName) {
            road = i;
            break;
        }
        throw ("Failed to load file: invalid <VOERTUIG> : '<baan> does not exist");
    }
    if (stoi (position) > road->getLength()){
        throw ("Failed to load file: invalid <VOERTUIG> : '<baan> is not long enough");
    }
    road->addCars(stoi(position));
}

void World::loadCarGen(TiXmlElement *elem1) {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling loadCarGen");
    std::string roadName = "";
    std::string frequency = "";
    for (TiXmlElement *elem2 = elem1->FirstChildElement(); elem2 != nullptr; elem2 = elem2->NextSiblingElement()) {
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
        throw ("Failed to load file: invalid <VOERTUIGGENERATOR> : 'missing argument' <baan>");
    }
    if (frequency == "") {
        throw ("Failed to load file: invalid <VOERTUIGGENERATOR> : 'missing argument' <frequentie>");
    }
    Road *road = nullptr;
    for (Road *i: getRoads()) {
        if (i->getName() == roadName) {
            road = i;
            break;
        }
        throw ("Failed to load file: invalid <VOERTUIGGENERATOR> : '<baan> does not exist");
    }
    if (stoi (frequency) > road->getLength()){
        throw ("Failed to load file: invalid <VOERTUIGGENERATOR> : '<baan> is not long enough");
    }
    addCarGen(road,stoi(frequency));
}
///////////////////////


const std::vector<Road *> &World::getRoads() {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling getRoads");
    return roads;
}
void World::setRoad(const std::vector<Road *> &banen) {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling setRoad");
    World::roads = banen;
}

const std::vector<CarGen *> &World::getCarGen()  {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling getCarGen");
    return carGen;
}

void World::setCarGen(const std::vector<CarGen *> &carGen) {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling setCarGen");
    World::carGen = carGen;
}

void World::addCarGen(Road *road, int frequency) {
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling addCarGen");
    carGen.emplace_back(new CarGen(road,frequency));
}



void World::simulateWorld(std::ostream & onStream){
    REQUIRE(this->properlyInitialized(), "World wasn't initialized when calling simulateWorld");
    onStream << "Tijd: " <<time<<std::endl;
    int numVehicle = 1;
    for (Road* i:roads){
        for (Car* car: i->getCars()){
            onStream << "Voertuig " << std::to_string(numVehicle) << time << std::endl;
            onStream << " -> baan: " << i->getName() << std::endl;
            onStream << " -> positie: " << car->getDistance() << std::endl;
            onStream << " -> positie: " << "carspeed" << std::endl << std::endl;
            numVehicle +=1;

        }
    }
}






//////////////
bool World::properlyInitialized () {
    return _initCheck == this;
}
//////////////





