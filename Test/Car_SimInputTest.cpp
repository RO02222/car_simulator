//============================================================================
// Name        : Car_SimDomainTest.cpp
// Date        : 19/03/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 1
//============================================================================

#include <iostream>
#include <fstream>
#include "../Input.h"
#include "gtest/gtest.h"
#include "../Classes/World.h"
#include "../Car_SimUtils.h"



using namespace std;


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
    friend class World;
    friend class Road;
    friend class Car;
    friend class CarGen;
    friend class Light;
    friend class BusStop;
    friend class Junction;
    // You should make the members protected s.t. they can be
    // accessed from sub-classes.
};

void Test_error(const char* inputfile, std::string compareFile){
    World* w = input::loadWorldXML(inputfile);
    delete w;
    EXPECT_TRUE(FileCompare("../outputFile/error.txt", compareFile));
}

/**
Tests InputHappyDay
*/
TEST_F(Car_SimInputTest, InputHappyDay) {
    World w = World();
    w.loadWorld("../testInput/testCase1.xml");


    EXPECT_EQ(w->getRoads()[0]->getName(), "Middelheimlaan");
    EXPECT_EQ(w->getRoads()[0]->getLength(), 400);

    EXPECT_EQ(w->getRoads()[0]->getLights()[0]->getRoad()->getName(), "Middelheimlaan");
    EXPECT_EQ(w->getRoads()[0]->getLights()[0]->getPosition(), 400);
    EXPECT_EQ(w->getRoads()[0]->getLights()[0]->getCycle(), 20);

    EXPECT_EQ(w->getRoads()[0]->getCars()[0]->getRoad()->getName(), "Middelheimlaan");
    EXPECT_EQ(w->getRoads()[0]->getCars()[0]->getDistance(), 40);
    EXPECT_EQ(w->getRoads()[0]->getCars()[1]->getRoad()->getName(), "Middelheimlaan");
    EXPECT_EQ(w->getRoads()[0]->getCars()[1]->getDistance(), 20);

    EXPECT_EQ(w->getRoads()[0]->getCarGen()[0]->getRoad()->getName(), "Middelheimlaan");
    EXPECT_EQ(w->getRoads()[0]->getCarGen()[0]->getFrequency(), 5);
    delete w;
}

/**
Tests InputMixed: test if xml read in different order of Classes also works.
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

/**
Tests InputMixed2: test if xml read in different order of variables also works.
*/
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

/**
Tests InputNoWorld: test if xml read without a world part works.
*/
TEST_F(Car_SimInputTest, InputFail) {
    //InputNoWorld: test if xml read without a world part works.
    Test_error("../testInput/testFail1.xml","../testOutput/testFail1.txt");
    //InputNoRootTest if xml read without a root works.
    Test_error("../testInput/testFail2.xml","../testOutput/testFail2.txt");
    //InputNoLength: test if xml read without a length in baan works.
    Test_error("../testInput/testFail3.xml","../testOutput/testFail3.txt");
    //InputLightToFar: test if xml read works when the position of the light is not on the road.
    Test_error("../testInput/testFail4.xml","../testOutput/testFail4.txt");
    //InputAlreadyExist: test if xml read works when the name of the road already exists.
    Test_error("../testInput/testFail5.xml","../testOutput/testFail5.txt");
    //InputNoPosition: test if xml read works when there is no position given for the light.
    Test_error("../testInput/testFail6.xml","../testOutput/testFail6.txt");
    //InputNoBaan: test if xml read works when there is no baan given for the CarGenerator.
    Test_error("../testInput/testFail7.xml","../testOutput/testFail7.txt");
    //InputCarToFar: test if xml read works when the position of the car is not on the road.
    Test_error("../testInput/testFail8.xml","../testOutput/testFail8.txt");
}
