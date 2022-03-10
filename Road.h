//
// Created by robbe on 3-3-2022.
//

#ifndef CAR_SIMULATOR_ROAD_H
#define CAR_SIMULATOR_ROAD_H
#include <vector>
#include <iostream>

class Road;
class Light;
class Car;

class Road{
private:
    Road* _initCheck;

    std::string name;
    int length;
    std::vector<Light*> lights;
    std::vector<Car*> cars;
public:
    /**
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    Road(const std::string &name, int length);

/**
\n REQUIRE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    const std::string &getName();
    /**
\n REQUIRE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    void setName(const std::string &name);
/**
\n REQUIRE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    int getLength();
/**
\n REQUIRE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    void setLength(int length);
/**
\n REQUIRE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    const std::vector<Light *> &getLights();
/**
\n REQUIRE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    void setLights(const std::vector<Light *> &lights);
/**
\n REQUIRE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    void addLights(int position, int cycle);
/**
\n REQUIRE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    const std::vector<Car *> &getCars();
/**
\n REQUIRE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    void setCars(const std::vector<Car *> &cars);
/**
\n REQUIRE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    void addCars(int distance);



    /////////////
protected:
    bool properlyInitialized();

    /////////////
};

#endif //CAR_SIMULATOR_ROAD_H
