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

class Car_SimDomainTest: public ::testing::Test {
protected:
    // You should make the members protected s.t. they can be
    // accessed from sub-classes.

    // virtual void SetUp() will be called before each test is run.  You
    // should define it if you need to initialize the variables.
    // Otherwise, this can be skipped.
    virtual void SetUp() {
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
TEST_F(Car_SimDomainTest, Initialiser) {
    World w = World();
    Road r1 = Road("Middelheimlaan", 100);
    Road r2 = Road("Groenenborgerlaan", 100);
    r1.addCar(25);
    r1.addCar(60);
    r2.addCar(90);
    r1.addLight(80, 5);
    r1.addLight( 20, 5);
    r1.addLight(50, 5);
    r2.addLight(60,5);
    r1.addCarGen(5);
    r2.addCarGen(5);

    EXPECT_EQ(r1.getName(), "Middelheimlaan");
    EXPECT_EQ(r1.getLength(), 100);
    EXPECT_EQ(r2.getName(), "Groenenborgerlaan");
    EXPECT_EQ(r2.getLength(), 100);

    EXPECT_EQ(r1.getCars()[0]->getDistance(),25);
    EXPECT_EQ(r1.getCars()[1]->getDistance(),60);
    EXPECT_EQ(r2.getCars()[0]->getDistance(),90);

    EXPECT_EQ(r1.getLights()[0]->getPosition(), 80);
    EXPECT_EQ(r1.getLights()[1]->getPosition(), 20);
    EXPECT_EQ(r1.getLights()[2]->getPosition(), 50);
    EXPECT_EQ(r2.getLights()[0]->getPosition(), 60);
    EXPECT_EQ(r1.getLights()[0]->getState(), red);
    EXPECT_EQ(r1.getLights()[1]->getState(), red);
    EXPECT_EQ(r1.getLights()[2]->getState(), red);
    EXPECT_EQ(r2.getLights()[0]->getState(), red);
    EXPECT_EQ(r1.getLights()[0]->getCycle(), 5);
    EXPECT_EQ(r1.getLights()[1]->getCycle(), 5);
    EXPECT_EQ(r1.getLights()[2]->getCycle(), 5);
    EXPECT_EQ(r2.getLights()[0]->getCycle(), 5);

    EXPECT_EQ(r1.getCarGen()[0]->getFrequency(), 5);
    EXPECT_EQ(r2.getCarGen()[0]->getFrequency(), 5);
}

/**
Tests update simulated world and see if the new situation is right (here just the lights).
*/
TEST_F(Car_SimDomainTest, UpdateWorld) {
    World* w = new World();
    Road* r1 = new Road("Middelheimlaan", 100);
    r1->addCar(25);
    r1->addCar(60);
    r1->addCar(90);
    r1->addLight(80, 2);
    r1->addLight( 20, 3);
    r1->addLight(50, 4);
    r1->addLight(60,5);
    r1->addCarGen(5);
    vector<Road*> roads;
    roads.push_back(r1);
    w->setRoad(roads);

    w->updateWorld(1);
    EXPECT_EQ(r1->getName(), "Middelheimlaan");
    EXPECT_EQ(r1->getLength(), 100);

    EXPECT_EQ(r1->getLights()[0]->getPosition(), 80);
    EXPECT_EQ(r1->getLights()[1]->getPosition(), 20);
    EXPECT_EQ(r1->getLights()[2]->getPosition(), 50);
    EXPECT_EQ(r1->getLights()[3]->getPosition(), 60);

    EXPECT_EQ(r1->getLights()[0]->getCycle(), 2);
    EXPECT_EQ(r1->getLights()[1]->getCycle(), 3);
    EXPECT_EQ(r1->getLights()[2]->getCycle(), 4);
    EXPECT_EQ(r1->getLights()[3]->getCycle(), 5);

    EXPECT_EQ(r1->getLights()[0]->getState(), red);
    EXPECT_EQ(r1->getLights()[1]->getState(), red);
    EXPECT_EQ(r1->getLights()[2]->getState(), red);
    EXPECT_EQ(r1->getLights()[3]->getState(), red);

    w->updateWorld(5);

    EXPECT_EQ(r1->getLights()[0]->getState(), green);
    EXPECT_EQ(r1->getLights()[1]->getState(), green);
    EXPECT_EQ(r1->getLights()[2]->getState(), green);
    EXPECT_EQ(r1->getLights()[3]->getState(), green);

    w->updateWorld(2);
    EXPECT_EQ(r1->getLights()[0]->getState(), red);
    EXPECT_EQ(r1->getLights()[1]->getState(), red);
    EXPECT_EQ(r1->getLights()[2]->getState(), green);
    EXPECT_EQ(r1->getLights()[3]->getState(), green);

    delete r1;
    delete w;
}

