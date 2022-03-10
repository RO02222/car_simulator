//
// Created by robbe on 3-3-2022.
//

#ifndef CAR_SIMULATOR_CAR_H
#define CAR_SIMULATOR_CAR_H

class Car{
private:
    Car* _initCheck;
    int distance;
public:
    /**
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    Car (int distance);

/**
\n REQUIRE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    int getDistance();
/**
\n REQUIRE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    void setDistance(int distance);




    /////////////
protected:
    bool properlyInitialized();

    /////////////
};


#endif //CAR_SIMULATOR_CAR_H
