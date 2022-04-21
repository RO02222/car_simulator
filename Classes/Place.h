//
// Created by robbe on 21.04.22.
//

#ifndef CAR_SIMULATION_PLACE_H
#define CAR_SIMULATION_PLACE_H


class Place {
private:
    Place* __initCheck;

public:
/**
 * create a Place for cars
 * @return: None
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    Place();


/////////////
public:
    bool properlyInitialized() const;

/////////////
};


#endif //CAR_SIMULATION_PLACE_H
