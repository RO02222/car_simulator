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
    int frequency;

public:
/**
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    CarGen(int frequency,Road *road);

/**
\n REQUIRE(properlyInitialized(), "CarGen wasn't initialized when calling getFrequency);
*/
    int getFrequency();
/**
\n REQUIRE(properlyInitialized(), "CarGen wasn't initialized when calling setFrequency);
*/
    void setFrequency(int frequency);
/**
\n REQUIRE(properlyInitialized(), "CarGen wasn't initialized when calling getRoad);
*/
    Road *getRoad();
/**
\n REQUIRE(properlyInitialized(), "CarGen wasn't initialized when calling setRoad);
*/
    void setRoad(Road *r);


    /////////////
protected:
    bool properlyInitialized();

    /////////////
};


#endif //CAR_SIMULATOR_CARGEN_H
