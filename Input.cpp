#include "Input.h"
#include "Functions.h"
#include "tinyxml/tinyxml.h"
#include "Classes/World.h"
#include "Classes/Road.h"
#include "Classes/Light.h"
#include "Classes/Car.h"
#include "Classes/CarGen.h"
#include "DesignByContract.h"
#include "Exception/ParserException.h"



namespace input {
    World *loadWorldXML(const char *worldName) {
        World *world = new World();
        REQUIRE(world->properlyInitialized(), "World wasn't initialized when calling loadWorldXML");
        TiXmlDocument doc;
        if (!doc.LoadFile(worldName)) {
            std::cerr << doc.ErrorDesc() << std::endl;
            return world;
        }
        TiXmlElement *root = doc.FirstChildElement();
        if (root == NULL) {
            std::cerr << "Failed to load file: No root element." << std::endl;
            return world;
        }
        TiXmlElement *elem = root;
        if ((std::string) elem->Value() != "World") {
            std::cerr << "Failed to load file: <World> ... </World>" << std::endl;
            return world;
        }
        for (TiXmlElement *elem1 = elem->FirstChildElement(); elem1 != 0; elem1 = elem1->NextSiblingElement()) {
            if ((std::string) elem1->Value() == "BAAN") {
                _::loadRoadXML(world, elem1);
            }
        }
        for (TiXmlElement *elem1 = elem->FirstChildElement(); elem1 != NULL; elem1 = elem1->NextSiblingElement()) {
            if ((std::string) elem1->Value() == "BAAN") {
                continue;
            }
            if ((std::string) elem1->Value() == "VERKEERSLICHT") {
                _::loadLightXML(world, elem1);
                continue;
            }
            if ((std::string) elem1->Value() == "VOERTUIG") {
                _::loadCarXML(world, elem1);
                continue;
            }
            if ((std::string) elem1->Value() == "VOERTUIGGENERATOR") {
                _::loadCarGenXML(world, elem1);
                continue;
            }
            if ((std::string) elem1->Value() == "BUSHALTE") {
                _::loadBusstopXML(world, elem1);
                continue;
            }
            if ((std::string) elem1->Value() == "KRUISPUNT") {
                _::loadJunctionXML(world, elem1);
                continue;
            }
            std::cerr << "Failed to load file: <" + (std::string) elem1->Value() + "> is not valid" << std::endl;
        }
        return world;
    }

    namespace _ {

        void loadRoadXML(World *world, TiXmlElement *elem1) {
            REQUIRE(world->properlyInitialized(),
                    "World wasn't initialized when calling private function of loadWorldXML");
            std::string name = "";
            std::string length = "";
            for (TiXmlElement *elem2 = elem1->FirstChildElement(); elem2 != 0; elem2 = elem2->NextSiblingElement()) {
                if (elem2->GetText() == NULL) {
                    std::cerr << "Failed to load file: <" + (std::string) elem2->Value() + "> has no value"
                              << std::endl;
                    continue;
                }
                if ((std::string) elem2->Value() == "naam") {
                    name = elem2->GetText();
                    continue;
                }
                if ((std::string) elem2->Value() == "lengte") {
                    length = elem2->GetText();
                    continue;
                }
                std::cerr << "Failed to load file: <BAAN> : <" + (std::string) elem2->Value()
                             + "> is not valid" << std::endl;
            }
            if (name.empty()) {
                std::cerr << "Failed to load file: invalid <BAAN> : 'missing argument' <naam>" << std::endl;
                return;
            }
            if (length.empty()) {
                std::cerr << "Failed to load file: invalid <BAAN> : 'missing argument' <lengte>" << std::endl;
                return;
            }
            world->addRoad(name, std::stoi(length));
        }


        void loadLightXML(World *world, TiXmlElement *elem1) {
            REQUIRE(world->properlyInitialized(),
                    "World wasn't initialized when calling private function of loadWorldXML");
            std::string roadName = "";
            std::string position = "";
            std::string cycle = "";
            for (TiXmlElement *elem2 = elem1->FirstChildElement(); elem2 != 0; elem2 = elem2->NextSiblingElement()) {
                if (elem2->GetText() == NULL) {
                    std::cerr << "Failed to load file: <" + (std::string) elem2->Value() + "> has no value"
                              << std::endl;
                    continue;
                }
                if ((std::string) elem2->Value() == "baan") {
                    roadName = elem2->GetText();
                    continue;
                }
                if ((std::string) elem2->Value() == "positie") {
                    position = elem2->GetText();
                    continue;
                }
                if ((std::string) elem2->Value() == "cyclus") {
                    cycle = elem2->GetText();
                    continue;
                }
                std::cerr << "Failed to load file: <VERKEERSLICHT> : <"
                             + (std::string) elem2->Value() + "> is not valid" << std::endl;
            }
            if (roadName.empty()) {
                std::cerr << "Failed to load file: invalid <VERKEERSLICHT> : 'missing argument' <baan>" << std::endl;
                return;
            }
            if (position.empty()) {
                std::cerr << "Failed to load file: invalid <VERKEERSLICHT> : 'missing argument' <positie>" << std::endl;
                return;
            }
            if (cycle.empty()) {
                std::cerr << "Failed to load file: invalid <VERKEERSLICHT> : 'missing argument' <cyclus>" << std::endl;
                return;
            }
            Road *road = NULL;
            std::vector<Road *> roadIt = world->getRoads();
            for (std::vector<Road *>::iterator it = roadIt.begin(); it != roadIt.end(); it++) {
                if ((*it)->getName() == roadName) {
                    road = (*it);
                    break;
                }
            }
            if (road == NULL) {
                std::cerr << "Failed to load file: invalid <VERKEERSLICHT> : '<baan>' does not exist" << std::endl;
                return;
            }
            road->addLight(std::stoi(position), std::stoi(cycle));
        }


        void loadCarXML(World *world, TiXmlElement *elem1) {
            REQUIRE(world->properlyInitialized(),
                    "World wasn't initialized when calling private function of loadWorldXML");
            std::string roadName = "";
            std::string position = "";
            std::string type = "";
            Type Type;
            for (TiXmlElement *elem2 = elem1->FirstChildElement(); elem2 != 0; elem2 = elem2->NextSiblingElement()) {
                if (elem2->GetText() == NULL) {
                    std::cerr << "Failed to load file: <" + (std::string) elem2->Value() + "> has no value"
                              << std::endl;
                    return;
                }
                if ((std::string) elem2->Value() == "baan") {
                    roadName = elem2->GetText();
                    continue;
                }
                if ((std::string) elem2->Value() == "positie") {
                    position = elem2->GetText();
                    continue;
                }
                if ((std::string) elem2->Value() == "type") {
                    type = elem2->GetText();
                    continue;
                }
                std::cerr << "Failed to load file: <VOERTUIG> : <" + (std::string) elem2->Value()
                             + "> is not valid" << std::endl;
            }
            if (roadName.empty()) {
                std::cerr << "Failed to load file: invalid <VOERTUIG> : 'missing argument' <baan>" << std::endl;
                return;
            }
            if (position.empty()) {
                std::cerr << "Failed to load file: invalid <VOERTUIG> : 'missing argument' <positie>" << std::endl;
                return;
            }
            if (type.empty()) {
                std::cerr << "Failed to load file: invalid <VOERTUIG> : 'missing argument' <type>" << std::endl;
                return;
            }
            if (type == "auto") {
                Type = car;
            }else if (type == "bus") {
                Type = bus;
            }else if (type == "brandweerwagen") {
                Type = fire;
            }else if (type == "ziekenwagen") {
                Type = police;
            }else if (type == "politiecombi") {
                Type = ambulance;
            }else{
                std::cerr << "Failed to load file: invalid <VOERTUIG> : 'invalid argument' <type>" << std::endl;
                return;
            }

            Road *road = NULL;
            std::vector<Road *> roadIt = world->getRoads();
            for (std::vector<Road *>::iterator it = roadIt.begin(); it != roadIt.end(); it++) {
                if ((*it)->getName() == roadName) {
                    road = (*it);
                    break;
                }
            }
            if (road == NULL) {
                std::cerr << "Failed to load file: invalid <VOERTUIG> : '<baan> does not exist" << std::endl;
                return;
            }
            road->addCar(std::stoi(position),world->getCarData(Type));
        }


        void loadCarGenXML(World *world, TiXmlElement *elem1) {
            REQUIRE(world->properlyInitialized(),
                    "World wasn't initialized when calling private function of loadWorldXML");
            std::string roadName = "";
            std::string frequency = "";
            std::string type = "";
            Type Type;
            for (TiXmlElement *elem2 = elem1->FirstChildElement(); elem2 != 0; elem2 = elem2->NextSiblingElement()) {
                if (elem2->GetText() == NULL) {
                    std::cerr << "Failed to load file: <" + (std::string) elem2->Value()
                                 + "> has no value" << std::endl;
                    continue;
                }
                if ((std::string) elem2->Value() == "baan") {
                    roadName = elem2->GetText();
                    continue;
                }
                if ((std::string) elem2->Value() == "frequentie") {
                    frequency = elem2->GetText();
                    continue;
                }
                if ((std::string) elem2->Value() == "type") {
                    type = elem2->GetText();
                    continue;
                }
                std::cerr << "Failed to load file: <VOERTUIGGENERATOR> : <" + (std::string) elem2->Value()
                             + "> is not valid" << std::endl;
            }
            if (roadName.empty()) {
                std::cerr << "Failed to load file: invalid <VOERTUIGGENERATOR> : 'missing argument' <baan>"
                          << std::endl;
                return;
            }
            if (frequency.empty()) {
                std::cerr << "Failed to load file: invalid <VOERTUIGGENERATOR> : 'missing argument' <frequentie>"
                          << std::endl;
                return;
            }
            if (type.empty() or type == "none" or type == "None") {
                Type = none;
            } else if (type == "auto") {
                Type = car;
            }else if (type == "bus") {
                Type = bus;
            }else if (type == "brandweerwagen") {
                Type = fire;
            }else if (type == "ziekenwagen") {
                Type = police;
            }else if (type == "politiecombi") {
                Type = ambulance;
            }else{
                std::cerr << "Failed to load file: invalid <VOERTUIGGENERATOR> : 'invalid argument' <type>" << std::endl;
                return;
            }
            Road *road = NULL;
            std::vector<Road *> roadIt = world->getRoads();
            for (std::vector<Road *>::iterator it = roadIt.begin(); it != roadIt.end(); it++) {
                if ((*it)->getName() == roadName) {
                    road = (*it);
                    break;
                }
            }
            if (road == NULL) {
                std::cerr << "Failed to load file: invalid <VOERTUIGGENERATOR> : '<baan> does not exist" << std::endl;
                return;
            }
            if (Type == none){
                road->addCarGen(std::stoi(frequency),world->getAllData());
            } else {
                road->addCarGen(std::stoi(frequency), world->getCarData(Type));
            }
        }

        void loadBusstopXML(World *world, TiXmlElement *elem1) {
            REQUIRE(world->properlyInitialized(),
                    "World wasn't initialized when calling private function of loadWorldXML");
            std::string roadName = "";
            std::string position = "";
            std::string stoptime = "";
            for (TiXmlElement *elem2 = elem1->FirstChildElement(); elem2 != 0; elem2 = elem2->NextSiblingElement()) {
                if (elem2->GetText() == NULL) {
                    std::cerr << "Failed to load file: <" + (std::string) elem2->Value() + "> has no value"
                              << std::endl;
                    continue;
                }
                if ((std::string) elem2->Value() == "baan") {
                    roadName = elem2->GetText();
                    continue;
                }
                if ((std::string) elem2->Value() == "positie") {
                    position = elem2->GetText();
                    continue;
                }
                if ((std::string) elem2->Value() == "wachttijd") {
                    stoptime = elem2->GetText();
                    continue;
                }
                std::cerr << "Failed to load file: <BUSHALTE> : <"
                             + (std::string) elem2->Value() + "> is not valid" << std::endl;
            }
            if (roadName.empty()) {
                std::cerr << "Failed to load file: invalid <BUSHALTE> : 'missing argument' <baan>" << std::endl;
                return;
            }
            if (position.empty()) {
                std::cerr << "Failed to load file: invalid <BUSHALTE> : 'missing argument' <positie>" << std::endl;
                return;
            }
            if (stoptime.empty()) {
                std::cerr << "Failed to load file: invalid <BUSHALTE> : 'missing argument' <wachttijd>" << std::endl;
                return;
            }
            Road *road = NULL;
            std::vector<Road *> roadIt = world->getRoads();
            for (std::vector<Road *>::iterator it = roadIt.begin(); it != roadIt.end(); it++) {
                if ((*it)->getName() == roadName) {
                    road = (*it);
                    break;
                }
            }
            if (road == NULL) {
                std::cerr << "Failed to load file: invalid <BUSHALTE> : '<baan>' does not exist" << std::endl;
                return;
            }
            road->addBusStop(std::stoi(position), std::stoi(stoptime));
        }


        void loadJunctionXML(World *world, TiXmlElement *elem1) {
            REQUIRE(world->properlyInitialized(),
                    "World wasn't initialized when calling private function of loadWorldXML");
            std::string roadName1 = "";
            std::string roadName2 = "";
            std::string position1 = "";
            std::string position2 = "";
            for (TiXmlElement *elem2 = elem1->FirstChildElement(); elem2 != 0; elem2 = elem2->NextSiblingElement()) {
                if (elem2->GetText() == NULL) {
                    std::cerr << "Failed to load file: <" + (std::string) elem2->Value() + "> has no value"
                              << std::endl;
                    continue;
                }
                if ((std::string) elem2->Value() == "baan") { ;
                    if (elem2->LastAttribute() != 0) {
                        if (roadName1.empty()) {
                            roadName1 = elem2->GetText();
                            position1 = elem2->LastAttribute()->Value();
                            continue;
                        }
                        roadName2 = elem2->GetText();
                        position2 = elem2->LastAttribute()->Value();
                        continue;
                    }
                }
                std::cerr << "Failed to load file: <KRUISPUNT> : <"
                             + (std::string) elem2->Value() + "> is not valid" << std::endl;
            }
            if (roadName1.empty()) {
                std::cerr << "Failed to load file: invalid <KRUISPUNT> : 'missing argument' <baan>" << std::endl;
                return;
            }
            if (roadName2.empty()) {
                std::cerr << "Failed to load file: invalid <KRUISPUNT> : 'missing argument' <baan>" << std::endl;
                return;
            }
            Road *road1 = NULL;
            Road *road2 = NULL;
            std::vector<Road *> roadIt = world->getRoads();
            for (std::vector<Road *>::iterator it = roadIt.begin(); it != roadIt.end(); it++) {
                if ((*it)->getName() == roadName1) {
                    road1 = (*it);
                    continue;
                }
                if ((*it)->getName() == roadName2) {
                    road2 = (*it);
                    continue;
                }
            }
            if (road1 == NULL or road2 == NULL) {
                std::cerr << "Failed to load file: invalid <KRUISPUNT> : '<baan>' does not exist" << std::endl;
                return;
            }
            world->addJunction(std::pair<Road *, double>(road1, std::stoi(position1)),
                               std::pair<Road *, double>(road2, std::stoi(position2)));
        }
    }
}
///////////////////////