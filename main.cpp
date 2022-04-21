#include <iostream>
#include <fstream>
#include "Classes/World.h"
#include "Basic_Values.h"
#include "Input.h"
#include "Classes/BusStop.h"
#include "Classes/Junction.h"
#include "Classes/CarData.h"

int main() {
    World* w = input::loadWorldXML("../XML/case1.xml");
    std::ofstream myFile;
    std::ofstream myFile2;
    myFile.open("../Car_sim.txt");
    myFile2.open("../Car_sim2.txt");
    for (unsigned int i =0; i < 100; i++) {
        w->simpleSimulateWorld(myFile);
        w->graficImpSimulateWorld(myFile2);
        for (unsigned int _ = 0; _ < 10; _ += 1) {
            w->updateWorld(0.1);
        }
    }
    myFile.close();
    myFile2.close();

    delete w;
    return 0;
}
