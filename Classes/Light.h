//
// Created by robbe on 3-3-2022.
//

#ifndef CAR_SIMULATOR_LIGHT_H
#define CAR_SIMULATOR_LIGHT_H


class Light{
private:
    Light* _initCheck;

    double position;
    double cycle;
public:
    /**
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    Light(double position, double cycle);

















/////////////
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
/////////////



/////////////
protected:
    bool properlyInitialized() const;

/////////////
};



#endif //CAR_SIMULATOR_LIGHT_H
