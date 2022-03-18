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

public:

/**
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    CarGen(double frequency,Road *road);






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
/////////////



/////////////
protected:
    bool properlyInitialized() const;

/////////////
};


#endif //CAR_SIMULATOR_CARGEN_H
