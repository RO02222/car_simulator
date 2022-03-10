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
\n REQUIRE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    int getPosition();
/**
\n REQUIRE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    void setPosition(int position);
/**
\n REQUIRE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    int getCycle();
/**
\n REQUIRE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    void setCycle(int cycle);




    /////////////
protected:
    bool properlyInitialized();

    /////////////
};



#endif //CAR_SIMULATOR_LIGHT_H
