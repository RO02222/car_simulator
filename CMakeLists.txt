cmake_minimum_required(VERSION 3.6)
project(car_simulator)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Werror")
set(CMAKE_EXE_LINKER_FLAGS -pthread)

# Set include dir
include_directories(gtest/include)

# Set Library dir
link_directories(gtest/lib)

# Set source files for RELEASE target
set(RELEASE_SOURCE_FILES
        main.cpp
        tinyxml/tinystr.h tinyxml/tinystr.cpp tinyxml/tinyxml.h tinyxml/tinyxml.cpp tinyxml/tinyxmlparser.cpp tinyxml/tinyxmlerror.cpp
        World.cpp World.h
        Road.cpp Road.h
        Light.cpp Light.h
        Car.cpp Car.h
        Exception/ParserException.h
        CarGen.cpp CarGen.h DesignByContract.h)

# Set source files for DEBUG target
set(DEBUG_SOURCE_FILES
        TestMain.cpp
        tinyxml/tinystr.h tinyxml/tinystr.cpp tinyxml/tinyxml.h tinyxml/tinyxml.cpp tinyxml/tinyxmlparser.cpp tinyxml/tinyxmlerror.cpp
        World.cpp World.h
        Road.cpp Road.h
        Light.cpp Light.h
        Car.cpp Car.h
        Exception/ParserException.h
        CarGen.cpp CarGen.h DesignByContract.h TestMain.cpp)

# Create RELEASE target
add_executable(Car_simulation ${RELEASE_SOURCE_FILES})

# Create DEBUG target
add_executable(Car_simulation_debug ${DEBUG_SOURCE_FILES})

# Link library
target_link_libraries(Car_simulation_debug gtest)