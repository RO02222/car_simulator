cmake_minimum_required(VERSION 3.20)
project(car_simulator)

set(CMAKE_CXX_STANDARD 14)

add_executable(car_simulator
        main.cpp
        tinyxml/tinystr.h tinyxml/tinystr.cpp tinyxml/tinyxml.h tinyxml/tinyxml.cpp tinyxml/tinyxmlparser.cpp tinyxml/tinyxmlerror.cpp
        World.cpp World.h
        Road.cpp Road.h
        Light.cpp Light.h
        Car.cpp Car.h
        Exception/ParserException.h
        CarGen.cpp CarGen.h)
