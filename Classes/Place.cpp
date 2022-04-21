//
// Created by robbe on 21.04.22.
//

#include <iostream>
#include "../DesignByContract.h"
#include "Place.h"

Place::Place() {
    __initCheck = this;
    ENSURE(properlyInitialized(),"constructor must end in properlyInitialized state");
}

//////////////
bool Place::properlyInitialized() const{
    return __initCheck == this;
}
//////////////