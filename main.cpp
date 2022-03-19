#include <iostream>
#include <fstream>
#include "Classes/World.h"
#include "Basic_Values.h"

int main() {

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
    return 0;
}
