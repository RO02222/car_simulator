//============================================================================
// Name        : Car_SimDomainTest.cpp
// Date        : 19/03/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 1
//============================================================================

#include <iostream>
#include "gtest/gtest.h"
#include "../Car_SimUtils.h"
#include "../Basic_Values.h"
#include "../Classes/Light.h"

using namespace std;


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
    friend class World;
    friend class Road;
    friend class Car;
    friend class CarGen;
    friend class Light;
    friend class BusStop;
    friend class Junction;
    friend class CarData;
    // You should make the members protected s.t. they can be
    // accessed from sub-classes.


};

/**
Tests Initialiser: test if every object is initialised right.
*/
TEST_F(LightDomainTest, Initialiser) {
    std::ofstream error;
    Road r1 = Road("Middelheimlaan", 100, &error);
    r1.addLight(50,3);

    EXPECT_EQ(r1.getLights()[0]->getPosition(), 50);
    EXPECT_EQ(r1.getLights()[0]->getCycle(), 3);
}


/**
Tests InitialiserEdge: test if every object is initialised right when edge case.
*/
TEST_F(LightDomainTest, InitialiserEdge) {
    std::ofstream error;
    error.open("../outputFile/error.txt");

    Road r1 = Road("Middelheimlaan", 100, &error);
    r1.addLight(50, 1.0000001);
    r1.addLight(70,0);
    r1.addLight(90,-16);
    r1.addLight(110,2);
    r1.addLight(-23, 4);

    EXPECT_EQ(r1.getLights()[0]->getCycle(), 1.0000001);
    EXPECT_EQ(r1.getLights()[1]->getCycle(), (unsigned int) 1);
    EXPECT_EQ(r1.getLights()[2]->getCycle(), (unsigned int)1);
    EXPECT_EQ(r1.getLights().size(), (unsigned int) 3);
    error.close();

    EXPECT_TRUE(FileCompare( "../testOutput/LightFail.txt", "../outputFile/error.txt"));
}

TEST_F(LightDomainTest, LightChange) {
    srand(123);
    World* w = new World();
    w->addRoad("Middelheimlaan", 10000);
    w->getRoads()[0]->addLight(50, 20);
    w->getRoads()[0]->addCar(0, w->getCarData(car));
    w->getRoads()[0]->getLights()[0]->setLastCycle(0);
    w->getRoads()[0]->getLights()[0]->setState(red);
    EXPECT_EQ(w->getRoads()[0]->getCars()[0]->getAction(), fast);
    int lastcycle = w->getRoads()[0]->getLights()[0]->getLastCycle();
    for (unsigned int _ = 0; _<4;_++) {
        w->updateWorld(1);
    }//na 1 keer update vertraagt de auto
    lastcycle = (lastcycle+4)%20;
    EXPECT_EQ(w->getRoads()[0]->getLights()[0]->getLastCycle(), lastcycle);
    EXPECT_EQ(w->getRoads()[0]->getCars()[0]->getAction(), slow);

    for (unsigned int _ = 0; _<10;_++) {
        w->updateWorld(1);
    } //kleiner interval, meerdere keren werkt wel!!!
    lastcycle = (lastcycle+10)%20;
    EXPECT_EQ(w->getRoads()[0]->getLights()[0]->getLastCycle(), lastcycle);
    EXPECT_EQ(w->getRoads()[0]->getCars()[0]->getAction(), stop);

    for (unsigned int _ = 0; _<10;_++) {
        w->updateWorld(1);
    }
    lastcycle = (lastcycle+10)%20;
    EXPECT_EQ(w->getRoads()[0]->getLights()[0]->getLastCycle(), lastcycle);
    EXPECT_EQ(w->getRoads()[0]->getCars()[0]->getAction(), fast);
    delete w;
}
