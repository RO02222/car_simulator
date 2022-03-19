//============================================================================
// Name        : Car_SimDomainTest.cpp
// Date        : 19/03/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 1
//============================================================================

#include <iostream>
#include "gtest/gtest.h"
#include "../Classes/World.h"
#include "../Classes/Car.h"
#include "../Classes/Light.h"

using namespace std;



class CarDomainTest: public ::testing::Test {
protected:
    // You should make the members protected s.t. they can be
    // accessed from sub-classes.

    // virtual void SetUp() will be called before each test is run.  You
    // should define it if you need to initialize the variables.
    // Otherwise, this can be skipped.
    virtual void SetUp() {
        World();
    }

    // virtual void TearDown() will be called after each test is run.
    // You should define it if there is cleanup work to do.  Otherwise,
    // you don't have to provide it.
    virtual void TearDown() {
    }

    // Declares the variables your tests want to use.
    friend class Car;
    friend class World;
    friend class CarGen;
    friend class Light;
    friend class Road;
    // You should make the members protected s.t. they can be
    // accessed from sub-classes.


};

/**
Tests if every object is initialised right.
*/
TEST_F(CarDomainTest, Initialiser) {
    Road r1 = Road("Middelheimlaan", 100);
    r1.addCar(3);

    EXPECT_EQ(r1.getCars()[0]->getDistance(), 3);

    r1.addCar(29);
    EXPECT_EQ(r1.getCars()[1]->getDistance(), 29);
}


/**
Tests if every object is initialised right.
*/
TEST_F(CarDomainTest, InitialiserEdge) {
    Road r1 = Road("Middelheimlaan", 100);
    r1.addCar(0);

    EXPECT_EQ(r1.getCars()[0]->getDistance(), 0);

    r1.addCar(100);
    EXPECT_EQ(r1.getCars()[1]->getDistance(), 100);

    r1.addCar(-1);
    EXPECT_EQ(r1.getCars()[2]->getDistance(), 0);

    r1.addCar(101);
    EXPECT_EQ(r1.getCars()[3]->getDistance(), 100);
}
