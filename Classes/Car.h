//
// Created by robbe on 3-3-2022.
//

#ifndef CAR_SIMULATOR_CAR_H
#define CAR_SIMULATOR_CAR_H
class Road;
class Car{
private:
    Car* _initCheck;
    Road* road;
    int distance;
    double speed;
    double acceleration;

public:
    /**
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    Car (int distance,Road* road);


/**
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling setAcceleration");
*/
    void updateCar(double t);

/**
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling getDistance");
*/
    int getDistance();
/**
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling setDistance");
*/
    void setDistance(int distance);

/**
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling getSpeed");
*/
    double getSpeed();
/**
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling setSpeed");
*/
    void setSpeed(double speed);

/**
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling getAcceleration");
*/
    double getAcceleration();
/**
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling setAcceleration");
*/
    void setAcceleration(double speed);


    /////////////
protected:
    bool properlyInitialized();

    /////////////
};


#endif //CAR_SIMULATOR_CAR_H
