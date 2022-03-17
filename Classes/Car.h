//
// Created by robbe on 3-3-2022.
//

#ifndef CAR_SIMULATOR_CAR_H
#define CAR_SIMULATOR_CAR_H

class Car{
private:
    Car* _initCheck;
    int distance;
    int speed;
public:
    /**
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    Car (int distance);

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
    int getSpeed();
/**
\n REQUIRE(properlyInitialized(), "Car wasn't initialized when calling setSpeed");
*/
    void setSpeed(double speed);



    /////////////
protected:
    bool properlyInitialized();

    /////////////
};


#endif //CAR_SIMULATOR_CAR_H
