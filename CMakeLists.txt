cmake_minimum_required(VERSION 3.20)
project(car_simulator)

set(CMAKE_CXX_STANDARD 98)

add_executable(car_simulator
        main.cpp
        tinyxml/tinystr.h tinyxml/tinystr.cpp tinyxml/tinyxml.h tinyxml/tinyxml.cpp tinyxml/tinyxmlparser.cpp tinyxml/tinyxmlerror.cpp
        Classes/World.cpp Classes/World.h
        Classes/Road.cpp Classes/Road.h
        Classes/Light.cpp Classes/Light.h
        Classes/Car.cpp Classes/Car.h
        Exception/ParserException.h
        Classes/CarGen.cpp Classes/CarGen.h DesignByContract.h Basic_Values.h Functions.cpp Functions.h)
