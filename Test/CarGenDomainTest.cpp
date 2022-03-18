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

/**
Tests if every object is initialised right.
*/
TEST_F(CarGenDomainTest, Initialiser) {
    Road r1 = Road("Middelheimlaan", 100);
    r1.addCarGen(3);


    EXPECT_EQ(r1.getCarGen()[0]->getFrequency(), 3);
    EXPECT_EQ(r1.getCarGen()[0]->getRoad()->getName(), "Middelheimlaan");
}


/**
Tests if every object is initialised right.
*/
TEST_F(CarGenDomainTest, InitialiserEdge) {
    Road r1 = Road("Middelheimlaan", 100);
    r1.addCarGen(1.00001);

    EXPECT_EQ(r1.getCarGen()[0]->getFrequency(), 1.00001);
    EXPECT_EQ(r1.getCarGen()[0]->getRoad()->getName(), "Middelheimlaan");

}