//============================================================================
// Name        : TicTacToeDomainTests.cpp
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <gtest/gtest.h>

using namespace std;

#include "Classes/World.h"
#include "Classes/Car.h"
#include "Classes/CarGen.h"
#include "Classes/Light.h"
#include "Classes/Road.h"

class TicTactToeDomainTest: public ::testing::Test {
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
Tests the default constructor.
*/
TEST_F(TicTactToeDomainTest, HappyDay) {
    World w = World();
    Road R1 = Road("Middelheimlaan", 800);
    Road R2 = Road("Groenenborgerlaan", 80);
    Car C1 = Car(25);
    Car C2 = Car(60);
    Car C3 = Car(90);
    Light L1 = Light(100, 5);
    Light L2 = Light(600, 5);
    Light L3 = Light(40,5);
    R1.
    EXPECT_EQ(0, ttt_.nrOfMoves());
    EXPECT_TRUE(ttt_.notDone());
    char col, row;
    for (col = minCol; col <= maxCol; col++)
        for (row = minRow; row <= maxRow; row++) {
            EXPECT_EQ(' ', ttt_.getMark(col, row));
        };
    EXPECT_TRUE(tttPlayer_.properlyInitialized());
    EXPECT_EQ('X', tttPlayer_.getMarker());
}


/**
Tests the "happy day" scenario
*/
TEST_F(TicTactToeDomainTest, HappyDay) {
    EXPECT_EQ(0, ttt_.nrOfMoves());
    EXPECT_TRUE(ttt_.notDone());
    ttt_.setMoves("a1c1b2a3c3", "b1a2c2b3");
    while (ttt_.notDone()) {
        ttt_.doMove();
    };
    char col, row;
    bool markIsX = false; // start with 'O'
    // The diagonal is recognised as a winner. Sow we stop after verifying first two rows
    for (row = minRow; row < maxRow; row++)
        for (col = minCol; col <= maxCol; col++) {
            if (markIsX)
                EXPECT_EQ('X', ttt_.getMark(col, row));
            else
                EXPECT_EQ('O', ttt_.getMark(col, row));
            markIsX = not markIsX;
        };
    EXPECT_FALSE(ttt_.notDone());
    EXPECT_EQ(7, ttt_.nrOfMoves());
}
