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
    World* w = input::loadWorldXML("../XML/case1.xml");

    //World* w = input::loadWorldXML("../XML/case1.xml");
    //World* w = input::loadWorldXML("../testInput/testFail1.xml");
    //World* w = input::loadWorldXML("../testInput/testFail2.xml");
    //World* w = input::loadWorldXML("../testInput/test1.xml");
    std::ofstream myFile;
    std::ofstream myFile2;
    myFile.open("../outputFile/Car_sim.txt");
    myFile2.open("../outputFile/Car_sim2.txt");
    for (unsigned int i =0; i < 1000; i++) {
        w->simpleSimulateWorld(myFile);
        w->graficImpSimulateWorld(myFile2);
#if VERSION == 14
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
#endif
        for (unsigned int _ = 0; _ < 10; _ += 1) {
            w->updateWorld(0.1);
        }
    }
    myFile.close();
    myFile2.close();

    delete w;
    return 0;
}
