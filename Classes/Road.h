//============================================================================
// Name        : Car_SimDomainTest.cpp
// Date        : 19/03/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 1
//============================================================================


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
    double length;

    std::vector<Light*> lights;
    std::vector<Car*> cars;
    std::vector<CarGen*> carGen;
public:
/**
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    Road(const std::string &name, double length);



/**
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling removeCars);
*/
    void removeCars(Car* car);



/**
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling setAcceleration");
*/
    void updateRoad(double t);



/////////////
public:
/**
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling addLights);
*/
    void addLight(double position, double cycle);
/**
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling addCars);
*/
    void addCar(double distance);
/**
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling setCarGen);
*/
    void addCarGen(double frequency);
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
    double getLength();
/**
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling setLength);
*/
    void setLength(double length);


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
    bool properlyInitialized() const;

/////////////
};

#endif //CAR_SIMULATOR_ROAD_H
