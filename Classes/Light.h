//
// Created by robbe on 3-3-2022.
//

#ifndef CAR_SIMULATOR_LIGHT_H
#define CAR_SIMULATOR_LIGHT_H


class Light{
private:
    Light* _initCheck;

    int position;
    int cycle;
public:
    /**
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    Light(int position, int cycle);

/**
\n REQUIRE(properlyInitialized(), "Light wasn't initialized when calling getPosition");
*/
    int getPosition();
/**
\n REQUIRE(properlyInitialized(), "Light wasn't initialized when calling setPosition");
*/
    void setPosition(int position);
/**
\n REQUIRE(properlyInitialized(), "Light wasn't initialized when calling getCycle");
*/
    int getCycle();
/**
\n REQUIRE(properlyInitialized(), "Light wasn't initialized when calling setCycle");
*/
    void setCycle(int cycle);




    /////////////
protected:
    bool properlyInitialized();

    /////////////
};



#endif //CAR_SIMULATOR_LIGHT_H
