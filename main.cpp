#include <iostream>
#include <fstream>
#include "Classes/World.h"
#include "Basic_Values.h"
#include "Input.h"
#include "Classes/BusStop.h"
#include "Classes/Junction.h"
#include "Classes/CarData.h"

#if VERSION == 14
#include <chrono>
#include <thread>
#endif


int main() {
    //World* w = input::loadWorldXML("../XML/bugattiVScar.xml");
    //World* w = input::loadWorldXML("../XML/case1.xml");

    //World* w = input::loadWorldXML("../XML/case1.xml");
    srand(974120);
    World* w = input::loadWorldXML("../testInput/testCase5.xml");
    w->isvalid();
    //World* w = input::loadWorldXML("../testInput/testFail2.xml");
    //World* w = input::loadWorldXML("../testInput/test1.xml");
    std::ofstream myFile;
    std::ofstream myFile2;
    myFile.open("../outputFile/Car_sim.txt");
    myFile2.open("../outputFile/Car_sim2.txt");
#if VERSION == 14
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
#endif
    for (unsigned int i =0; i < 10; i++) {
        w->simpleSimulateWorld(myFile);
        w->graficImpSimulateWorld(myFile2);
#if VERSION == 14
        //std::this_thread::sleep_for(std::chrono::milliseconds(20));
#endif
        for (unsigned int _ = 0; _ < 10; _ += 1) {
            w->updateWorld(0.01);
        }
    }
    myFile.close();
    myFile2.close();

    delete w;
    return 0;
}
