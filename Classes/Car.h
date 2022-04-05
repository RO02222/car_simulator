//============================================================================
// Name        : Car_SimDomainTest.cpp
// Date        : 19/03/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 1
//============================================================================


#ifndef CAR_SIMULATOR_CAR_H
#define CAR_SIMULATOR_CAR_H
class Road;
class CarData;
enum Type{car,bus,fire,police,ambulance,none};
enum Action{fast,slow,stop};
class Car{
private:
    Car* _initCheck;
    Road* road;
    double distance;
    double speed;
    double maxSpeed;
    double acceleration;
    Action action;
    CarData* data;

public:
/**
 * create a Car
 * @param distance: position on the road
 * @param data: the data of the car
 * @param road: road where the Car is positioned.
 * @return: None
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    Car (double distance, CarData* data, Road* road);


/**
 * Update the Car his position, speed and acceleration
 * @param t: time since last update
 * @return: None
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling setAcceleration");
*/
    void updateCar(double t);










//////////////
public:
/**
 * get the road where the Car is positioned
 * @return: (Road*), the road where the Car is positioned
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling getRoad");
*/
    Road *getRoad() const;

protected:
/**
 * change the road of the CarGen
 * @param road: the new road of the CarGen
 * @return: None
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling setRoad");
*/
    void setRoad(Road *road);

public:
/**
 * get the distance of the car
 * @return: (double), the distance of the car
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling getDistance");
*/
    double getDistance();
/**
 * change the distance of the car
 * @param distance: the new distance of the car
 * @return: None
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling setDistance");
*/
    void setDistance(double distance);
/**
 * get the speed of the car
 * @return: (double), the speed of the car
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling getSpeed");
*/
    double getSpeed();
/**
 * change the speed of the car
 * @param speed: the new speed of the car
 * @return: None
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling setSpeed");
*/
    void setSpeed(double speed);
/**
 * get the maxSpeed of the car
 * @return: (double), the maxSpeed of the car
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling getMaxSpeed");
*/
    double getMaxSpeed();
/**
 * change the maxSpeed of the car
 * @param maxSpeed: the new maxSpeed of the car
 * @return: None
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling setMaxSpeed");
*/
    void setMaxSpeed(double maxSpeed);
/**
 * get the acceleration of the car
 * @return: (double), the acceleration of the car
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling getAcceleration");
*/
    double getAcceleration();
/**
 * change the acceleration of the car
 * @param acceleration: the new acceleration of the car
 * @return: None
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling setAcceleration");
*/
    void setAcceleration(double acceleration);
/**
 * get the Acton that the car is doing
 * @return: (action), the Acton that the car is doing
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling getAction");
*/
    Action getAction();
/**
 * change the Action of the car
 * @param action: the new Action of the car
 * @return: None
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling setAction");
*/
    void setAction(Action action);
//////////////



/////////////
protected:
    bool properlyInitialized() const;

/////////////
};


#endif //CAR_SIMULATOR_CAR_H
