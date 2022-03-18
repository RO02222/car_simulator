//
// Created by robbe on 10-3-2022.
//

#ifndef CAR_SIMULATOR_CARGEN_H
#define CAR_SIMULATOR_CARGEN_H
class Road;

class CarGen {
private:
    CarGen* _initCheck;
    Road *road;
    double frequency;
    double lastCycle;

public:

/**
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    CarGen(double frequency,Road *road);

/**
\n REQUIRE(properlyInitialized(), "CarGen wasn't initialized when calling updateCarGen");
*/
    void updateCarGen(double t);




/////////////
public:
/**
\n REQUIRE(properlyInitialized(), "CarGen wasn't initialized when calling getRoad);
*/
    Road *getRoad();

protected:
/**
\n REQUIRE(properlyInitialized(), "CarGen wasn't initialized when calling setRoad);
*/
    void setRoad(Road *r);

public:
/**
\n REQUIRE(properlyInitialized(), "CarGen wasn't initialized when calling getFrequency);
*/
    double getFrequency();
/**
\n REQUIRE(properlyInitialized(), "CarGen wasn't initialized when calling setFrequency);
*/
    void setFrequency(double frequency);

/**
\n REQUIRE(properlyInitialized(), "CarGen wasn't initialized when calling getCycle);
*/
    double getCycle();

protected:
/**
\n REQUIRE(properlyInitialized(), "CarGen wasn't initialized when calling setCycle);
*/
    void setCycle(double c);
/////////////



/////////////
protected:
    bool properlyInitialized() const;

/////////////
};


#endif //CAR_SIMULATOR_CARGEN_H
