//============================================================================
// Name        : Car_SimDomainTest.cpp
// Date        : 19/03/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 1
//============================================================================

#include <iostream>
#include "gtest/gtest.h"

using namespace std;

class CarGenDomainTest: public ::testing::Test {
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
void test_CarGen(Type type){
    World* w = new World();
    w->addRoad("Middelheimlaan", 100);
    w->getRoads()[0]->addCarGen(3, w->getCarData(type));
    int time = 0;
    EXPECT_EQ(int (w->getRoads()[0]->getCars().size()), 0);
    w->getRoads()[0]->getCarGen()[0]->updateCarGen(2);
    time = time + 2;
    EXPECT_EQ(w->getRoads()[0]->getCarGen()[0]->getCycle(),time%3);
    EXPECT_EQ(int(w->getRoads()[0]->getCars().size()), 1);
    w->getRoads()[0]->getCarGen()[0]->updateCarGen(2);
    time = time + 2;
    EXPECT_EQ(w->getRoads()[0]->getCarGen()[0]->getCycle(),time%3);
    EXPECT_EQ(int(w->getRoads()[0]->getCars().size()), 1);
    EXPECT_EQ(w->getRoads()[0]->getCars()[0]->getData(), w->getRoads()[0]->getCarGen()[0]->getData());
    EXPECT_EQ(w->getRoads()[0]->getCarGen()[0]->getFrequency(), 3);

    delete w;
}

/**
Tests Initialiser: test if every object is initialised right.
*/
TEST_F(CarGenDomainTest, Initialiser) {
//CargenCar: test if CarGen works for cars.
    test_CarGen(car);
//CargenCar: test if CarGen works for ambulances.
    test_CarGen(ambulance);
//CargenCar: test if CarGen works for firetrucks.
    test_CarGen(fire);
//CargenCar: test if CarGen works for busses.
    test_CarGen(bus);
}

TEST_F(CarGenDomainTest, Initialiser2) {
    World *w = new World();
    w->addRoad("Middelheimlaan", 100);
    w->getRoads()[0]->addCarGen(3, w->getAllData());
    int time = 0;
    EXPECT_EQ(int(w->getRoads()[0]->getCars().size()), 0);
    w->getRoads()[0]->getCarGen()[0]->updateCarGen(2);
    time = time + 2;
    EXPECT_EQ(w->getRoads()[0]->getCarGen()[0]->getCycle(), time%3);
    EXPECT_EQ(int(w->getRoads()[0]->getCars().size()), 1);
    w->getRoads()[0]->getCarGen()[0]->updateCarGen(2);
    time = time + 2;
    EXPECT_EQ(w->getRoads()[0]->getCarGen()[0]->getCycle(), time%3);
    EXPECT_EQ(int(w->getRoads()[0]->getCars().size()), 1);
    EXPECT_EQ(w->getRoads()[0]->getCarGen()[0]->getFrequency(), 3);

    delete w;
}