//
// Created by robbe on 3-3-2022.
//

#include "World.h"
#include "Road.h"
#include "Light.h"
#include "Car.h"
#include <iostream>

World::World(const char * worldName) {
    loadWorld(worldName);
}

const std::vector<Road *> &World::getRoads() const {
    return roads;
}
void World::setRoad(const std::vector<Road *> &banen) {
    World::roads = banen;
}
bool World::addRoad(std::string name, int length, bool errormessage) {
    for (Road* i :getRoads()){
        if (i->getName() == name){
            if (errormessage){
                std::cerr << "Failed to add road: road already exist" << std::endl;
            }
            return false;
        }
    }
    roads.emplace_back(new Road(name,length));
    return true;
}


bool World::addCar(std::string road, int distance, bool errormessage) {
    Road *road1 = nullptr;
    for (Road *roads: getRoads()) {
        if (roads->getName() == road) {
            road1 = roads;
            break;
        }
    }
    if (road1 == nullptr) {
        if (errormessage) {
            std::cerr << "Failed to add car: road does not exist" << std::endl;
        }
        return false;
    }
    road1->addCars(distance);
    return true;
}


bool World::loadWorld(const char *worldName) {
    TiXmlDocument doc;
    if (!doc.LoadFile(worldName)) {
        std::cerr << doc.ErrorDesc() << std::endl;
        return false;
    }
    TiXmlElement *root = doc.FirstChildElement();
    if (root == NULL) {
        std::cerr << "Failed to load file: No root element." << std::endl;
        doc.Clear();
        return false;
    }
    TiXmlElement *elem = root;
    if ((std::string) elem->Value() != "World") {
        std::cerr << "Failed to load file: <World> ... </World>" << std::endl;
        return false;
    }
    for (TiXmlElement *elem1 = elem->FirstChildElement(); elem1 != nullptr; elem1 = elem1->NextSiblingElement()) {
        if ((std::string) elem1->Value() != "BAAN" and (std::string) elem1->Value() != "VERKEERSLICHT" and (std::string) elem1->Value() != "VOERTUIG"){
            std::cerr << "Unknown section : <"<<elem1->Value() <<">"<< std::endl;
        }
        if ((std::string) elem1->Value() == "BAAN") {
            std::string name = "";
            std::string length = "";
            for (TiXmlElement *elem2 = elem1->FirstChildElement(); elem2 != nullptr; elem2 = elem2->NextSiblingElement()) {
                if ((std::string) elem2->Value() == "naam") {
                    name = elem2->GetText();
                } else {
                    if ((std::string) elem2->Value() == "lengte") {
                        length = elem2->GetText();
                    }
                }
            }
            if (name == "" or length == "") {
                std::cerr << "Failed to load file: invalid <BAAN> : 'missing/invalid argument'" << std::endl;
                return false;
            }
            if(!addRoad(name, stoi(length), false)){
                std::cerr << "Failed to add <BAAN>: <BAAN> already exist" << std::endl;
                return false;
            }
        }
    }
    for (TiXmlElement *elem1 = elem->FirstChildElement(); elem1 != NULL; elem1 = elem1->NextSiblingElement()) {
        if ((std::string) elem1->Value() == "VERKEERSLICHT") {
            std::string road = "";
            std::string distance = "";
            std::string cycle = "";
            for (TiXmlElement *elem2 = elem1->FirstChildElement(); elem2 != NULL; elem2 = elem2->NextSiblingElement()) {
                if ((std::string) elem2->Value() == "baan") {
                    road = elem2->GetText();
                } else {
                    if ((std::string) elem2->Value() == "positie") {
                        distance = elem2->GetText();
                    } else {
                        if ((std::string) elem2->Value() == "cyclus") {
                            cycle = elem2->GetText();
                        }
                    }
                }
            }
            if (road == "" or distance == "" or cycle == "") {
                std::cerr << "Failed to load file: invalid <VERKEERSLICHT> : 'missing/invalid argument'" << std::endl;
                return false;
            }
            Road *road1 = nullptr;
            for (Road *roads: getRoads()) {
                if (roads->getName() == road) {
                    road1 = roads;
                    break;
                }
            }
            if (road1 == nullptr) {
                std::cerr << "Failed to load file: invalid <VERKEERSLICHT> : '<baan> does not exist'" << std::endl;
                return false;
            }
            road1->addLights(stoi(distance), stoi(cycle));
        }
        if ((std::string) elem1->Value() == "VOERTUIG") {
            std::string road = "";
            std::string distance = "";
            for (TiXmlElement *elem2 = elem1->FirstChildElement(); elem2 != NULL; elem2 = elem2->NextSiblingElement()) {
                if ((std::string) elem2->Value() == "baan") {
                    road = elem2->GetText();
                } else {
                    if ((std::string) elem2->Value() == "positie") {
                        distance = elem2->GetText();
                    }
                }
            }
            if (road == "" or distance == "") {
                std::cerr << "Failed to load file: invalid <VOERTUIG> : 'missing/invalid argument'" << std::endl;
                return false;
            }
            if (!addCar(road,stoi(distance), false)) {
                std::cerr << "Failed to load file: invalid <VOERTUIG> : '<baan> does not exist'" << std::endl;
                return false;
            }
        }
    }
    return true;
}





