//
// Created by robbe on 3-3-2022.
//

#ifndef CAR_SIMULATOR_CAR_H
#define CAR_SIMULATOR_CAR_H
class Road;
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

public:
/**
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    Car (double distance,Road* road);


/**
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling setAcceleration");
*/
    void updateCar(double t);










//////////////
public:
/**
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling getRoad");
*/
    Road *getRoad() const;

protected:
/**
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling setRoad");
*/
    void setRoad(Road *r);

public:
/**
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling getDistance");
*/
    double getDistance();
/**
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling setDistance");
*/
    void setDistance(double distance);
/**
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling getSpeed");
*/
    double getSpeed();
/**
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling setSpeed");
*/
    void setSpeed(double speed);
/**
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling getMaxSpeed");
*/
    double getMaxSpeed();
/**
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling setMaxSpeed");
*/
    void setMaxSpeed(double speed);
/**
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling getAcceleration");
*/
    double getAcceleration();
/**
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling setAcceleration");
*/
    void setAcceleration(double speed);
/**
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling getAction");
*/
    Action getAction();
/**
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling setAction");
*/
    void setAction(Action a);
//////////////



/////////////
protected:
    bool properlyInitialized() const;

/////////////
};


#endif //CAR_SIMULATOR_CAR_H
