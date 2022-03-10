//
// Created by robbe on 3-3-2022.
//

#ifndef CAR_SIMULATOR_WORLD_H
#define CAR_SIMULATOR_WORLD_H
#include <vector>
#include <iostream>
#include <cmath>
#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"
#include "Road.h"

class World {
private:
    std::vector<Road*> roads;
public:
    World(const char * worldName);

    const std::vector<Road *> &getRoads() const;
    void setRoad(const std::vector<Road *> &banen);
    bool addRoad(std::string name, int length, bool errormessage = true);

    bool addCar(std::string road, int distance, bool errormessage = true);

    bool loadWorld(const char * worldName);

};



#endif //CAR_SIMULATOR_WORLD_H
