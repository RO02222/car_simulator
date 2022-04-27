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
Tests Initialiser: test if every object is initialised right.
*/
TEST_F(CarDomainTest, Initialiser) {
    World* w = new World();
    Road r1 = Road("Middelheimlaan", 100, &w->error);

    r1.addCar(3, w->getCarData(car));
    EXPECT_EQ(r1.getCars()[0]->getDistance(), 3);
    EXPECT_EQ(r1.getCars()[0]->getData(), w->getCarData(car));

    r1.addCar(29, w->getCarData(ambulance));
    EXPECT_EQ(r1.getCars()[1]->getDistance(), 29);
    EXPECT_EQ(r1.getCars()[1]->getData(), w->getCarData(ambulance));

    r1.addCar(35, w->getCarData(fire));
    EXPECT_EQ(r1.getCars()[2]->getDistance(), 35);
    EXPECT_EQ(r1.getCars()[3]->getData(), w->getCarData(fire));

    r1.addCar(60, w->getCarData(bus));
    EXPECT_EQ(r1.getCars()[3]->getDistance(), 60);
    EXPECT_EQ(r1.getCars()[3]->getData(), w->getCarData(bus));
}


/**
Tests InitialiserEdge: test if every object is initialised right with some edge cases.
*/
TEST_F(CarDomainTest, InitialiserEdge) {
    World* w = new World();
    Road r1 = Road("Middelheimlaan", 100, &w->error);

    r1.addCar(0, w->getCarData(car));
    EXPECT_EQ(r1.getCars()[0]->getDistance(), 0);
    EXPECT_EQ(r1.getCars()[0]->getData(), w->getCarData(car));

    r1.addCar(100, w->getCarData(ambulance));
    EXPECT_EQ(r1.getCars()[1]->getDistance(), 100);
    EXPECT_EQ(r1.getCars()[1]->getData(), w->getCarData(ambulance));

    r1.addCar(-1, w->getCarData(fire));
    EXPECT_EQ(r1.getCars()[2]->getDistance(), 0);
    EXPECT_EQ(r1.getCars()[3]->getData(), w->getCarData(fire));

    r1.addCar(101, w->getCarData(bus));
    EXPECT_EQ(r1.getCars()[3]->getDistance(), 100);
    EXPECT_EQ(r1.getCars()[3]->getData(), w->getCarData(bus));
}

TEST_F(CarDomainTest, updatetest) {
    World* w = new World();
    Road r1 = Road("Middelheimlaan", 100, &w->error);
    vector<double> speed;
    vector<double> accelaration;
    vector<double> distance;

    r1.addCar(3, w->getCarData(car));
    EXPECT_EQ(r1.getCars()[0]->getDistance(), 3);
    EXPECT_EQ(r1.getCars()[0]->getData(), w->getCarData(car));
    speed.push_back(r1.getCars()[0]->getSpeed());
    accelaration.push_back(r1.getCars()[0]->getAcceleration());
    distance.push_back(r1.getCars()[0]->getDistance());

    r1.addCar(29, w->getCarData(ambulance));
    EXPECT_EQ(r1.getCars()[1]->getDistance(), 29);
    EXPECT_EQ(r1.getCars()[1]->getData(), w->getCarData(ambulance));
    speed.push_back(r1.getCars()[1]->getSpeed());
    accelaration.push_back(r1.getCars()[1]->getAcceleration());
    distance.push_back(r1.getCars()[1]->getDistance());

    r1.addCar(35, w->getCarData(fire));
    EXPECT_EQ(r1.getCars()[2]->getDistance(), 35);
    EXPECT_EQ(r1.getCars()[3]->getData(), w->getCarData(fire));
    speed.push_back(r1.getCars()[2]->getSpeed());
    accelaration.push_back(r1.getCars()[2]->getAcceleration());
    distance.push_back(r1.getCars()[2]->getDistance());

    r1.addCar(60, w->getCarData(bus));
    EXPECT_EQ(r1.getCars()[3]->getDistance(), 60);
    EXPECT_EQ(r1.getCars()[3]->getData(), w->getCarData(bus));
    speed.push_back(r1.getCars()[3]->getSpeed());
    accelaration.push_back(r1.getCars()[3]->getAcceleration());
    distance.push_back(r1.getCars()[3]->getDistance());

    r1.updateRoad(2);
    if(r1.getCars()[0]->getSpeed()!= 0){
        EXPECT_NE(r1.getCars()[0]->getAcceleration(), accelaration[0]);
        EXPECT_NE(r1.getCars()[0]->getDistance(), distance[0]);
        EXPECT_NE(r1.getCars()[0]->getSpeed(), speed[0]);
    }
    if(r1.getCars()[1]->getSpeed()!= 0){
        EXPECT_NE(r1.getCars()[1]->getAcceleration(), accelaration[1]);
        EXPECT_NE(r1.getCars()[1]->getDistance(), distance[1]);
        EXPECT_NE(r1.getCars()[1]->getSpeed(), speed[1]);
    }
    if(r1.getCars()[2]->getSpeed()!= 0){
        EXPECT_NE(r1.getCars()[2]->getAcceleration(), accelaration[2]);
        EXPECT_NE(r1.getCars()[2]->getDistance(), distance[2]);
        EXPECT_NE(r1.getCars()[2]->getSpeed(), speed[2]);
    }
    if(r1.getCars()[3]->getSpeed()!= 0){
        EXPECT_NE(r1.getCars()[3]->getAcceleration(), accelaration[3]);
        EXPECT_NE(r1.getCars()[3]->getDistance(), distance[3]);
        EXPECT_NE(r1.getCars()[3]->getSpeed(), speed[3]);
    }

    speed = {r1.getCars()[0]->getSpeed(), r1.getCars()[1]->getSpeed(), r1.getCars()[2]->getSpeed(), r1.getCars()[3]->getSpeed()};
    distance = {r1.getCars()[0]->getDistance(), r1.getCars()[1]->getDistance(), r1.getCars()[2]->getDistance(), r1.getCars()[3]->getDistance()};
    accelaration = {r1.getCars()[0]->getAcceleration(), r1.getCars()[1]->getAcceleration(), r1.getCars()[2]->getAcceleration(), r1.getCars()[3]->getAcceleration()};
}

