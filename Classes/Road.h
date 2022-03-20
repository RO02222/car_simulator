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
 * create a road
 * @param name: name of the road
 * @param length: lengt of the road
 * @return: None
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    Road(const std::string &name, double length);


/**
 * delete a road and everything on the road
 * @return: None
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling ~Road);
*/
    ~Road();


/**
 * remove and delete a car from the road.
 * @param car: the car that needs to be removed
 * @return: None
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling removeCars);
*/
    void removeCars(Car* car);



/**
 * Update the road, update everything on the road: Cars, light, CarGen.
 * @param t: time since last update
 * @return: None
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling setAcceleration");
*/
    void updateRoad(double t);



/////////////
public:
/**
 * add a new traffic light to the road
 * @param position: position of the traffic light on the road
 * @param cycle: cycle time of the trafficlight
 * @return: None
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling addLights);
*/
    void addLight(double position, double cycle);
/**
 * add a new car to the road
 * @param distance: distance of the car on the road
 * @return: None
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling addCars);
*/
    void addCar(double distance);
/**
 * add a new carGen at the beginning of the road
 * @param frequency: frequency of the carGen
 * @return: None
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling setCarGen);
*/
    void addCarGen(double frequency);
/////////////



/////////////
/**
 * Basic Getters/Setters
*/
public:
/**
 * get the name of the road
 * @return: (std::string), the name of the road
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling getName);
*/
    const std::string &getName();
/**
 * change the name of the road
 * @param name: the new name of the road
 * @return: None
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling setName);
*/
    void setName(const std::string &name);
/**
 * get the length of the road
 * @return: (double), the length of the road
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling getLength);
*/
    double getLength();
/**
 * change the length of the road
 * @param length: the new length of the road
 * @return: None
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling setLength);
*/
    void setLength(double length);


/**
 * get all the traffic lights on the the road
 * @return: (std::vector<Light*>), all the traffic lights on the the road
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling getLights);
*/
    const std::vector<Light *> &getLights();
/**
 * change the lights of the road
 * @param lights: the new lights of the road
 * @return: None
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling setLights);
*/
    void setLights(const std::vector<Light *> &lights);
/**
 * get all the Cars on the the road
 * @return: (std::vector<Car*>), all the Cars on the the road
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling getCars);
*/
    const std::vector<Car *> &getCars();
/**
 * change the cars of the road
 * @param cars: the new cars of the road
 * @return: None
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling setCars);
*/
    void setCars(const std::vector<Car *> &cars);
/**
 * get all the CarGens on the the road
 * @return: (std::vector<CarGen*>), all the CarGens on the the road
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling getCarGen);
*/
    const std::vector<CarGen *> &getCarGen();
/**
 * change the carGens of the road
 * @param carGens: the new carGens of the road
 * @return: None
\n REQUIRE(properlyInitialized(), "Road wasn't initialized when calling setCarGen);
*/
    void setCarGen(const std::vector<CarGen *> &carGens);
/////////////



/////////////
protected:
    bool properlyInitialized() const;

/////////////
};

#endif //CAR_SIMULATOR_ROAD_H
