cmake_minimum_required(VERSION 3.6)
project(Car_Simulation)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Werror")
set(CMAKE_EXE_LINKER_FLAGS -pthread)

# Set include dir
include_directories(gtest/include)

# Set Library dir
link_directories(gtest/lib)

# Set source files for RELEASE target
set(RELEASE_SOURCE_FILES
        Car_SimDomainTest.cpp
        tinyxml/tinystr.h tinyxml/tinystr.cpp tinyxml/tinyxml.h tinyxml/tinyxml.cpp tinyxml/tinyxmlparser.cpp tinyxml/tinyxmlerror.cpp
        Classes/World.cpp Classes/World.h
        Classes/Road.cpp Classes/Road.h
        Classes/Light.cpp Classes/Light.h
        Classes/Car.cpp Classes/Car.h
        Exception/ParserException.h
        Classes/CarGen.cpp Classes/CarGen.h DesignByContract.h Basic_Values.h Functions.cpp Functions.h CarTest.cpp LightTest.cpp RoadTest.cpp CarGenTest.cpp WorldTest.cpp Car_SimDomainTest.cpp LightDomainTest.cpp RoadDomainTest.cpp WorldDomainTest.cpp WorldInputTest.cpp WorldOutputTest.cpp RoadInputTest.cpp RoadOutputTest.cpp LightInputTest.cpp LightOutputTest.cpp CarInputTest.cpp CarOutputTest.cpp CarGenInputTest.cpp CarGenOutputTest.cpp CarGenDomainTest.cpp)

# Set source files for DEBUG target
set(DEBUG_SOURCE_FILES
        TestMain.cpp
        tinyxml/tinystr.h tinyxml/tinystr.cpp tinyxml/tinyxml.h tinyxml/tinyxml.cpp tinyxml/tinyxmlparser.cpp tinyxml/tinyxmlerror.cpp
        Classes/World.cpp Classes/World.h
        Classes/Road.cpp Classes/Road.h
        Classes/Light.cpp Classes/Light.h
        Classes/Car.cpp Classes/Car.h
        Exception/ParserException.h
        Classes/CarGen.cpp Classes/CarGen.h DesignByContract.h Basic_Values.h Functions.cpp Functions.h)

# Create RELEASE target
add_executable(Car_Simulation ${RELEASE_SOURCE_FILES})

# Create DEBUG target
add_executable(Car_Simulation_debug ${DEBUG_SOURCE_FILES})

# Link library
target_link_libraries(Car_Simulation_debug gtest)