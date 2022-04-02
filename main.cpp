#include <iostream>
#include <fstream>
#include "Classes/World.h"
#include "Basic_Values.h"
#include "Input.h"
#include "Classes/BusStop.h"
#include "Classes/Junction.h"

int main() {
    World* w = input::loadWorldXML("../XML/case1.xml");
    std::ofstream myFile;
    myFile.open("../Car_sim.txt");
    w->simulateWorld(myFile);
    for (unsigned int i =0; i < 400; i++) {
        w->updateWorld(0.0166);
        w->simulateWorld(myFile);
    }
    myFile.close();
    delete w;
    return 0;
}
