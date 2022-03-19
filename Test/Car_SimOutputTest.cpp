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
    ASSERT_TRUE(DirectoryExists("testOutput"));

    ofstream myfile;
    myfile.open("testOutput/file1.txt");
    myfile.close();
    myfile.open("testOutput/file2.txt");
    myfile.close();

    EXPECT_TRUE(FileExists("testOutput/file1.txt"));
    EXPECT_TRUE(FileExists("testOutput/file2.txt"));
    EXPECT_TRUE(FileIsEmpty("testOutput/file1.txt"));
    EXPECT_TRUE(FileIsEmpty("testOutput/file2.txt"));


    //compare 2 empty files
// *** Beware: the following does not work with older versions of libstdc++
// *** It doesn't work with gcc version 4.0.1 (Apple Inc. build 5465)
// *** It does work with gcc version 4.2.1
    EXPECT_TRUE(FileCompare("testOutput/file1.txt", "testOutput/file2.txt"));
    EXPECT_TRUE(FileCompare("testOutput/file2.txt", "testOutput/file1.txt"));

    //compare an empty and a non-empty files
    myfile.open("testOutput/file1.txt");
    myfile << "xxx" << endl << "yyy";
    myfile.close();
    EXPECT_TRUE(FileExists("testOutput/file1.txt"));
    EXPECT_FALSE(FileIsEmpty("testOutput/file1.txt"));
    EXPECT_FALSE(FileCompare("testOutput/file1.txt", "testOutput/file2.txt"));
    EXPECT_FALSE(FileCompare("testOutput/file2.txt", "testOutput/file1.txt"));

    //compare two equal files
    myfile.open("testOutput/file2.txt");
    myfile << "xxx" << endl << "yyy";
    myfile.close();
    EXPECT_TRUE(FileExists("testOutput/file2.txt"));
    EXPECT_FALSE(FileIsEmpty("testOutput/file2.txt"));
    EXPECT_TRUE(FileCompare("testOutput/file1.txt", "testOutput/file2.txt"));
    EXPECT_TRUE(FileCompare("testOutput/file2.txt", "testOutput/file1.txt"));

    //compare 2 non-empty files which are off by a character in the middle
    myfile.open("testOutput/file2.txt");
    myfile << "xxx" << endl << "xyy";
    myfile.close();
    EXPECT_FALSE(FileCompare("testOutput/file1.txt", "testOutput/file2.txt"));
    EXPECT_FALSE(FileCompare("testOutput/file2.txt", "testOutput/file1.txt"));

    //compare 2 non-empty files where one is one character shorter than the other
    myfile.open("testOutput/file2.txt");
    myfile << "xxx" << endl << "yy";
    myfile.close();
    EXPECT_FALSE(FileCompare("testOutput/file1.txt", "testOutput/file2.txt"));
    EXPECT_FALSE(FileCompare("testOutput/file2.txt", "testOutput/file1.txt"));

    //compare existing against non existing file
    EXPECT_FALSE(
            FileCompare("testOutput/file1.txt", "testOutput/nonexisting.txt"));
    EXPECT_FALSE(
            FileCompare("testOutput/nonexisting.txt", "testOutput/file1.txt"));
}