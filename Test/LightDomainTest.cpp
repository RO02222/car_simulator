//
// Created by simon on 17.03.22.
//

//
// Created by simon on 17.03.22.
//
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include "gtest/gtest.h"

using namespace std;

#include "../Classes/World.h"
#include "../Classes/Car.h"
#include "../Classes/CarGen.h"
#include "../Classes/Light.h"
#include "../Classes/Road.h"

class LightDomainTest: public ::testing::Test {
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
TEST_F(LightDomainTest, Initialiser) {
    Road r1 = Road("Middelheimlaan", 100);
    r1.addLight(50,3);

    EXPECT_EQ(r1.getLights()[0]->getPosition(), 50);
    EXPECT_EQ(r1.getLights()[0]->getCycle(), 3);
}


/**
Tests if every object is initialised right.
*/
TEST_F(LightDomainTest, InitialiserEdge) {
    Road r1 = Road("Middelheimlaan", 100);
    r1.addLight(50, 1.0000001);
    r1.addLight(70,0);
    r1.addLight(90,-16);
    r1.addLight(110,2);
    r1.addLight(100000000000000000,2);
    r1.addLight(-300,2);

    EXPECT_EQ(r1.getLights()[0]->getCycle(), 1.0000001);
    EXPECT_EQ(r1.getLights()[1]->getCycle(), 1);
    EXPECT_EQ(r1.getLights()[2]->getCycle(), 1);
    EXPECT_EQ(r1.getLights()[3]->getPosition(), 100);
    EXPECT_EQ(r1.getLights()[4]->getPosition(), 100);
}