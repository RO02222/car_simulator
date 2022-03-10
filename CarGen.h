//
// Created by robbe on 10-3-2022.
//

#ifndef CAR_SIMULATOR_CARGEN_H
#define CAR_SIMULATOR_CARGEN_H
class Road;

class CarGen {
private:
    CarGen* _initCheck;

    int frequency;
    Road *road;
public:
/**
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    CarGen(Road *road, int frequency);

/**
\n REQUIRE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    int getFrequency();
/**
\n REQUIRE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    void setFrequency(int frequency);
/**
\n REQUIRE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    Road *getRoad();
/**
\n REQUIRE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    void setRoad(Road *road);


    /////////////
protected:
    bool properlyInitialized();

    /////////////
};


#endif //CAR_SIMULATOR_CARGEN_H
