//
// Created by robbe on 3-3-2022.
//

#ifndef CAR_SIMULATOR_ROAD_H
#define CAR_SIMULATOR_ROAD_H
#include <vector>
#include <iostream>

class Light;
class Car;
class CarGen;


class Road{
private:
    Road* _initCheck;

    std::string name;
    int length;

    std::vector<Light*> lights;
    std::vector<Car*> cars;
    std::vector<CarGen*> carGen;
public:
/**
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    Road(const std::string &name, int length);



/**
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling removeCars);
*/
    void removeCars(Car* car);







/////////////
public:
/**
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling addLights);
*/
    void addLight(int position, int cycle);
/**
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling addCars);
*/
    void addCar(int distance);
/**
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling setCarGen);
*/
    void addCarGen(int frequency);
/////////////



/////////////
public:
/**
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling getName);
*/
    const std::string &getName();
/**
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling setName);
*/
    void setName(const std::string &name);
/**
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling getLength);
*/
    int getLength();
/**
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling setLength);
*/
    void setLength(int length);


/**
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling getLights);
*/
    const std::vector<Light *> &getLights();
/**
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling setLights);
*/
    void setLights(const std::vector<Light *> &lights);
/**
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling getCars);
*/
    const std::vector<Car *> &getCars();
/**
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling setCars);
*/
    void setCars(const std::vector<Car *> &cars);
/**
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling getCarGen);
*/
    const std::vector<CarGen *> &getCarGen();
/**
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling setCarGen);
*/
    void setCarGen(const std::vector<CarGen *> &carGen);
/////////////



/////////////
protected:
    bool properlyInitialized();

/////////////
};

#endif //CAR_SIMULATOR_ROAD_H
