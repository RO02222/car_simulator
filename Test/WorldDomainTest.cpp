//
// Created by simon on 17.03.22.
//

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

class WorldDomainTest: public ::testing::Test {
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
TEST_F(WorldDomainTest, Initialiser) {
    World w = World();
    r1.addLight(50,3);

    EXPECT_EQ(r1.getLights()[0]->getPosition(), 50);
    EXPECT_EQ(r1.getLights()[0]->getCycle(), 3);
}