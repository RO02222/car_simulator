#include <iostream>
#include "World.h"

int main() {
    World* w = new World("../XML/case1.xml");
    delete w;
    return 0;
}
