//============================================================================
// Name        : Car_SimDomainTest.cpp
// Date        : 19/03/2022
// Authors     : Simon Olivier & Robbe Teughels
// Version     : 1
//============================================================================


#ifndef CAR_SIMULATOR_BASIC_VALUES_H
#define CAR_SIMULATOR_BASIC_VALUES_H
#include <fstream>

std::ofstream error;

const double gSimTime = 0.0166;
const int gBreakDistance = 50;
const int gStopDistance = 15;
const double gSlowFactor = 0.4;

const double gl_auto = 4;            //lengte
const double gvMax_auto = 16.6;      //maximale snelheid
const double gaMax_auto = 1.44;      //maximale versnelling
const double gbMax_auto = 4.61;      //maximale remfactor
const double gfMin_auto = 4;         //minimale volgafstand

const double gl_bus = 12;             //lengte
const double gvMax_bus = 11.4;       //maximale snelheid
const double gaMax_bus = 1.22;       //maximale versnelling
const double gbMax_bus = 4.29;       //maximale remfactor
const double gfMin_bus = 12;          //minimale volgafstand

const double gl_brandweerwagen = 10;         //lengte
const double gvMax_brandweerwagen = 14.6;   //maximale snelheid
const double gaMax_brandweerwagen = 1.33;   //maximale versnelling
const double gbMax_brandweerwagen = 4.56;   //maximale remfactor
const double gfMin_brandweerwagen = 10;      //minimale volgafstand

const double gl_ziekenwagen = 8;            //lengte
const double gvMax_ziekenwagen = 15.5;      //maximale snelheid
const double gaMax_ziekenwagen = 1.44;      //maximale versnelling
const double gbMax_ziekenwagen = 4.47;      //maximale remfactor
const double gfMin_ziekenwagen = 8;         //minimale volgafstand

const double gl_politiecombi = 6;            //lengte
const double gvMax_politiecombi = 17.2;      //maximale snelheid
const double gaMax_politiecombi = 1.55;      //maximale versnelling
const double gbMax_politiecombi = 4.92;      //maximale remfactor
const double gfMin_politiecombi = 6;         //minimale volgafstand

#endif //CAR_SIMULATOR_BASIC_VALUES_H
