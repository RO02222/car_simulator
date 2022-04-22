//============================================================================
// Name        : Car_SimDomainTest.cpp
// Date        : 19/03/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 1
//============================================================================

#include <iostream>
#include "gtest/gtest.h"

using namespace std;

class RoadDomainTest: public ::testing::Test {
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
Tests Initialiser: test if every object is initialised right.
*/
TEST_F(RoadDomainTest, Initialiser) {
    Road r1 = Road("Middelheimlaan", 100);

    EXPECT_EQ(r1.getName(), "Middelheimlaan");
    EXPECT_EQ(r1.getLength(), 100);
}


/**
Tests InitialiserEdge: test if every object is initialised right with some edge cases or extreme numbers.
*/
TEST_F(RoadDomainTest, InitialiserEdge) {
    Road r1 = Road("Middelheimlaan", 1000000000000);
    Road r2 = Road("Groenenborgerlaan", 1);
    Road r3 = Road("Keyserlei", -1);


    EXPECT_EQ(r1.getLength(), 1000000000000);
    EXPECT_EQ(r2.getLength(), 1);
    EXPECT_EQ(r3.getLength(), 1);
}

/**
Tests addLight: test if function addLight works properly.
*/
TEST_F(RoadDomainTest, addLight){
    Road r1 = Road("Middelheimlaan", 100);

    r1.addLight(10,3);
    EXPECT_EQ(r1.getLights()[0]->getPosition(), 10);
    EXPECT_EQ(r1.getLights()[0]->getCycle(), 3);

    r1.addLight(50,2);
    EXPECT_EQ(r1.getLights()[1]->getPosition(), 50);
    EXPECT_EQ(r1.getLights()[1]->getCycle(), 2);
}

/**
Tests addCar: test if function addCar works properly.
*/
TEST_F(RoadDomainTest, addCar){
    Road r1 = Road("Middelheimlaan", 100);
    World* w = new World();
    r1.addCar(10,w->getCarData(car));
    EXPECT_EQ(r1.getCars()[0]->getDistance(), 10);

    r1.addCar(50);
    EXPECT_EQ(r1.getCars()[1]->getDistance(), 50);
}

/**
Tests addCarGen: test if function addCarGen works properly.
*/
TEST_F(RoadDomainTest, addCarGen){
    Road r1 = Road("Middelheimlaan", 100);

    r1.addCarGen(5);
    EXPECT_EQ(r1.getCarGen()[0]->getFrequency(), 5);
}

