#include <iostream>
#include "World.h"

int main() {

    World* w = new World();
    try {
        w->loadWorld("../XML/case1.xml");
    }
    catch(std::exception* e) {
        std::cerr<<e->what()<<std::endl;
    }
    delete w;
    return 0;
}
