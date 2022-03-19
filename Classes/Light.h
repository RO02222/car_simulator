//============================================================================
// Name        : Car_SimDomainTest.cpp
// Date        : 19/03/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 1
//============================================================================


#ifndef CAR_SIMULATOR_LIGHT_H
#define CAR_SIMULATOR_LIGHT_H

enum color {green,red};
class Road;

class Light{
private:
    Light* _initCheck;
    Road* road;

    double position;
    double cycle;
    double lastCycle;
    color state;
public:
    /**
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    Light(double position, double cycle, Road* r);


/**
\n REQUIRE(properlyInitialized(), "Light wasn't initialized when calling updateLight");
*/
    void updateLight(double t);














/////////////
/**
\n REQUIRE(properlyInitialized(), "Light wasn't initialized when calling getPosition");
*/
    Road* getRoad();

protected:
/**
\n REQUIRE(properlyInitialized(), "Light wasn't initialized when calling setPosition");
*/
    void setRoad(Road* r);

public:
/**
\n REQUIRE(properlyInitialized(), "Light wasn't initialized when calling getPosition");
*/
    double getPosition();
/**
\n REQUIRE(properlyInitialized(), "Light wasn't initialized when calling setPosition");
*/
    void setPosition(double position);
/**
\n REQUIRE(properlyInitialized(), "Light wasn't initialized when calling getCycle");
*/
    double getCycle();
/**
\n REQUIRE(properlyInitialized(), "Light wasn't initialized when calling setCycle");
*/
    void setCycle(double cycle);
/**
\n REQUIRE(properlyInitialized(), "Light wasn't initialized when calling getState");
*/
    color getState();
/**
\n REQUIRE(properlyInitialized(), "Light wasn't initialized when calling setState");
*/
    void setState(color state);
/////////////



/////////////
protected:
    bool properlyInitialized() const;

/////////////
};



#endif //CAR_SIMULATOR_LIGHT_H
