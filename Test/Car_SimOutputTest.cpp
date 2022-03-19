//============================================================================
// Name        : Car_SimDomainTest.cpp
// Date        : 19/03/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 1
//============================================================================


#include <iostream>
#include <fstream>
#include "gtest/gtest.h"
#include "../Car_SimUtils.h"


using namespace std;

class Car_SimOutputTest: public ::testing::Test {
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
    // You should make the members protected s.t. they can be
    // accessed from sub-classes.
};

// Tests the compare files
TEST_F(Car_SimOutputTest, FileCompare) {
    ASSERT_TRUE(DirectoryExists("../testOutput"));

    ofstream myfile;
    myfile.open("../testOutput/file1.txt");
    myfile.close();
    myfile.open("../testOutput/file2.txt");
    myfile.close();

    EXPECT_TRUE(FileExists("../testOutput/file1.txt"));
    EXPECT_TRUE(FileExists("../testOutput/file2.txt"));
    EXPECT_TRUE(FileIsEmpty("../testOutput/file1.txt"));
    EXPECT_TRUE(FileIsEmpty("../testOutput/file2.txt"));


    //compare 2 empty files
// *** Beware: the following does not work with older versions of libstdc++
// *** It doesn't work with gcc version 4.0.1 (Apple Inc. build 5465)
// *** It does work with gcc version 4.2.1
//    EXPECT_TRUE(FileCompare("../testOutput/file1.txt", "../testOutput/file2.txt"));
//    EXPECT_TRUE(FileCompare("../testOutput/file2.txt", "../testOutput/file1.txt"));

    //compare an empty and a non-empty files
    myfile.open("../testOutput/file1.txt");
    myfile << "xxx" << endl << "yyy";
    myfile.close();
    EXPECT_TRUE(FileExists("../testOutput/file1.txt"));
    EXPECT_FALSE(FileIsEmpty("../testOutput/file1.txt"));
    EXPECT_FALSE(FileCompare("../testOutput/file1.txt", "../testOutput/file2.txt"));
    EXPECT_FALSE(FileCompare("../testOutput/file2.txt", "../testOutput/file1.txt"));

    //compare two equal files
    myfile.open("../testOutput/file2.txt");
    myfile << "xxx" << endl << "yyy";
    myfile.close();
    EXPECT_TRUE(FileExists("../testOutput/file2.txt"));
    EXPECT_FALSE(FileIsEmpty("../testOutput/file2.txt"));
    EXPECT_TRUE(FileCompare("../testOutput/file1.txt", "../testOutput/file2.txt"));
    EXPECT_TRUE(FileCompare("../testOutput/file2.txt", "../testOutput/file1.txt"));

    //compare 2 non-empty files which are off by a character in the middle
    myfile.open("../testOutput/file2.txt");
    myfile << "xxx" << endl << "xyy";
    myfile.close();
    EXPECT_FALSE(FileCompare("../testOutput/file1.txt", "../testOutput/file2.txt"));
    EXPECT_FALSE(FileCompare("../testOutput/file2.txt", "../testOutput/file1.txt"));

    //compare 2 non-empty files where one is one character shorter than the other
    myfile.open("../testOutput/file2.txt");
    myfile << "xxx" << endl << "yy";
    myfile.close();
    EXPECT_FALSE(FileCompare("../testOutput/file1.txt", "../testOutput/file2.txt"));
    EXPECT_FALSE(FileCompare("../testOutput/file2.txt", "../testOutput/file1.txt"));

    //compare existing against non existing file
    EXPECT_FALSE(
            FileCompare("../testOutput/file1.txt", "../testOutput/nonexisting.txt"));
    EXPECT_FALSE(
            FileCompare("../testOutput/nonexisting.txt", "../testOutput/file1.txt"));
}

/**
Tests FileOutputHappyDay: test if the output is right in a simple case.
*/
TEST_F(Car_SimOutputTest, FileOutputHappyDay) {
    World* w = new World();
    try {
        w->loadWorld("../XML/case2.xml");
    }
    catch(std::exception* e) {
        std::cerr<<e->what()<<std::endl;
    }
    std::ofstream myFile;
    myFile.open("../Car_sim.txt");
    w->simulateWorld(myFile);
    for (unsigned int i =0; i < 1; i++) {
        w->updateWorld(1);
        w->simulateWorld(myFile);
    }
    myFile.close();
    delete w;

    EXPECT_TRUE(FileCompare("../Car_sim.txt", "../testOutput/testOutput1.txt"));
}


/**
Tests FileExtreme: test if the output is right for many updates of the world.
*/
TEST_F(Car_SimOutputTest, FileExtreme) {
    World* w = new World();
    try {
        w->loadWorld("../XML/case2.xml");
    }
    catch(std::exception* e) {
        std::cerr<<e->what()<<std::endl;
    }
    std::ofstream myFile;
    myFile.open("../Car_sim.txt");
    w->simulateWorld(myFile);
    for (unsigned int i =0; i < 400; i++) {
        w->updateWorld(1);
        w->simulateWorld(myFile);
    }
    myFile.close();
    delete w;

    EXPECT_TRUE(FileCompare("../Car_sim.txt", "../testOutput/testOutput2.txt"));
}

/**
Tests FileSimulation: test if the output is right for many updates of the world, with the given simulation update time.
*/
TEST_F(Car_SimOutputTest, FileSimulation) {
    World* w = new World();
    try {
        w->loadWorld("../XML/case2.xml");
    }
    catch(std::exception* e) {
        std::cerr<<e->what()<<std::endl;
    }
    std::ofstream myFile;
    myFile.open("../Car_sim.txt");
    w->simulateWorld(myFile);
    for (unsigned int i =0; i < 400; i++) {
        w->updateWorld(0.0166);
        w->simulateWorld(myFile);
    }
    myFile.close();
    delete w;

    EXPECT_TRUE(FileCompare("../Car_sim.txt", "../testOutput/testOutput3.txt"));
}