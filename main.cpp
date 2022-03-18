#include <iostream>
#include <fstream>
#include "Classes/World.h"
#include "Basic_Values.h"

int main() {
    //load world
    World* w = new World();
    try {
        w->loadWorld("../XML/case1.xml");
    }
    catch(std::exception* e) {
        std::cerr<<e->what()<<std::endl;
    }
    std::ofstream myFile;
    myFile.open("../Car_sim.txt");
    w->simulateWorld(myFile);
    for (unsigned int i =0; i < 10; i++) {
        w->updateWorld(5);
        w->simulateWorld(myFile);
    }
    myFile.close();


    /*
    std::ostream onStream();

    onStream << "hallo";
    w->simulateWorld()
    std::ofstream File;
    File.open("output");
    File << o
    */
    delete w;
    return 0;
}
