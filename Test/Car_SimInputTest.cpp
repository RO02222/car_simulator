//
// Created by simon on 17.03.22.
//

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include "gtest/gtest.h"
#include "../Exception/ParserException.h"



using namespace std;
//source: https://github.com/google/googletest/issues/952
#define EXPECT_THROW_WITH_MESSAGE(stmt, etype, whatstring) EXPECT_THROW( \
        try { \
            stmt; \
        } catch (const etype& ex) { \
            EXPECT_EQ(std::string(ex.what()), whatstring); \
            throw; \
        } \
    , etype)

#include "../Classes/World.h"
#include "../Classes/Car.h"
#include "../Classes/CarGen.h"
#include "../Classes/Light.h"
#include "../Classes/Road.h"
#include "../Car_SimUtils.h"

class Car_SimInputTest: public ::testing::Test {
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
Tests InputHappyDay
*/
TEST_F(Car_SimInputTest, InputHappyDay) {
    World w = World();
    w.loadWorld("../testInput/testCase1.xml");


    EXPECT_EQ(w.getRoads()[0]->getName(), "Middelheimlaan");
    EXPECT_EQ(w.getRoads()[0]->getLength(), 400);

    EXPECT_EQ(w.getRoads()[0]->getLights()[0]->getRoad()->getName(), "Middelheimlaan");
    EXPECT_EQ(w.getRoads()[0]->getLights()[0]->getPosition(), 400);
    EXPECT_EQ(w.getRoads()[0]->getLights()[0]->getCycle(), 20);

    EXPECT_EQ(w.getRoads()[0]->getCars()[0]->getRoad()->getName(), "Middelheimlaan");
    EXPECT_EQ(w.getRoads()[0]->getCars()[0]->getDistance(), 40);
    EXPECT_EQ(w.getRoads()[0]->getCars()[1]->getRoad()->getName(), "Middelheimlaan");
    EXPECT_EQ(w.getRoads()[0]->getCars()[1]->getDistance(), 20);

    EXPECT_EQ(w.getRoads()[0]->getCarGen()[0]->getRoad()->getName(), "Middelheimlaan");
    EXPECT_EQ(w.getRoads()[0]->getCarGen()[0]->getFrequency(), 5);
}

/**
Tests InputMixed test if load in different order also works
*/
TEST_F(Car_SimInputTest, InputMixed) {
    World w = World();
    w.loadWorld("../testInput/testCase2.xml");


    EXPECT_EQ(w.getRoads()[0]->getName(), "Middelheimlaan");
    EXPECT_EQ(w.getRoads()[0]->getLength(), 400);

    EXPECT_EQ(w.getRoads()[0]->getLights()[0]->getRoad()->getName(), "Middelheimlaan");
    EXPECT_EQ(w.getRoads()[0]->getLights()[0]->getPosition(), 400);
    EXPECT_EQ(w.getRoads()[0]->getLights()[0]->getCycle(), 20);

    EXPECT_EQ(w.getRoads()[0]->getCars()[0]->getRoad()->getName(), "Middelheimlaan");
    EXPECT_EQ(w.getRoads()[0]->getCars()[0]->getDistance(), 40);
    EXPECT_EQ(w.getRoads()[0]->getCars()[1]->getRoad()->getName(), "Middelheimlaan");
    EXPECT_EQ(w.getRoads()[0]->getCars()[1]->getDistance(), 20);

    EXPECT_EQ(w.getRoads()[0]->getCarGen()[0]->getRoad()->getName(), "Middelheimlaan");
    EXPECT_EQ(w.getRoads()[0]->getCarGen()[0]->getFrequency(), 5);
}

TEST_F(Car_SimInputTest, InputMixed2) {
    World w = World();
    w.loadWorld("../testInput/testCase3.xml");


    EXPECT_EQ(w.getRoads()[0]->getName(), "Middelheimlaan");
    EXPECT_EQ(w.getRoads()[0]->getLength(), 400);

    EXPECT_EQ(w.getRoads()[0]->getLights()[0]->getRoad()->getName(), "Middelheimlaan");
    EXPECT_EQ(w.getRoads()[0]->getLights()[0]->getPosition(), 400);
    EXPECT_EQ(w.getRoads()[0]->getLights()[0]->getCycle(), 20);

    EXPECT_EQ(w.getRoads()[0]->getCars()[0]->getRoad()->getName(), "Middelheimlaan");
    EXPECT_EQ(w.getRoads()[0]->getCars()[0]->getDistance(), 40);
    EXPECT_EQ(w.getRoads()[0]->getCars()[1]->getRoad()->getName(), "Middelheimlaan");
    EXPECT_EQ(w.getRoads()[0]->getCars()[1]->getDistance(), 20);

    EXPECT_EQ(w.getRoads()[0]->getCarGen()[0]->getRoad()->getName(), "Middelheimlaan");
    EXPECT_EQ(w.getRoads()[0]->getCarGen()[0]->getFrequency(), 5);
}


TEST_F(Car_SimInputTest, InputNoWorld) {
    World w = World();

    EXPECT_THROW_WITH_MESSAGE(w.loadWorld("../testInput/testFail1.xml"),ParserException , "Failed to load file: <World> ... </World>");
}

TEST_F(Car_SimInputTest, InputNoRoot) {
    World w = World();

    EXPECT_THROW_WITH_MESSAGE(w.loadWorld("../testInput/testFail2.xml"),ParserException , "Failed to load file: No root element.");
}

TEST_F(Car_SimInputTest, InputNoLength) {
    World w = World();

    EXPECT_THROW_WITH_MESSAGE(w.loadWorld("../testInput/testFail3.xml"),ParserException , "Failed to load file: invalid <BAAN> : 'missing argument' <lengte>");
}

TEST_F(Car_SimInputTest, InputLightToFar) {
    World w = World();

    EXPECT_THROW_WITH_MESSAGE(w.loadWorld("../testInput/testFail4.xml"),ParserException , "Failed to load file: invalid <VOERTUIG> : '<baan> is not long enough");
}


TEST_F(Car_SimInputTest, InputAlreadyExist) {
    World w = World();

    EXPECT_THROW_WITH_MESSAGE(w.loadWorld("../testInput/testFail5.xml"),ParserException , "Failed to add road: road already exist");
}

TEST_F(Car_SimInputTest, InputNotInitialized) {
    World* w = new World();
    delete w;

    EXPECT_DEATH(w->loadWorld("../testInput/testCase1.xml"), "World wasn't initialized when calling loadWorld");
}

TEST_F(Car_SimInputTest, InputNoPosition) {
    World w = World();

    EXPECT_THROW_WITH_MESSAGE(w.loadWorld("../testInput/testFail6.xml"),ParserException , "Failed to load file: invalid <VERKEERSLICHT> : 'missing argument' <positie>");
}

TEST_F(Car_SimInputTest, InputNoGenerator) {
    World w = World();

    EXPECT_THROW_WITH_MESSAGE(w.loadWorld("../testInput/testFail7.xml"),ParserException , "Failed to load file: invalid <VOERTUIGGENERATOR> : 'missing argument' <baan>");
}

TEST_F(Car_SimInputTest, InputCarToFar) {
    World w = World();

    EXPECT_THROW_WITH_MESSAGE(w.loadWorld("../testInput/testFail8.xml"),ParserException , "Failed to load file: invalid <VOERTUIG> : '<baan> is not long enough");
}


