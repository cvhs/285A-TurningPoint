#ifndef CONFIG_H_
#define CONFIG_H_

#include "vex.h"

extern vex::brain       Brain;
extern vex::competition Competition;
extern vex::controller  Controller1;

// DRIVE
extern vex::motor MotorLF;
extern vex::motor MotorLB;
extern vex::motor MotorRF;
extern vex::motor MotorRB;

extern vex::motor LF;
extern vex::motor LB;
extern vex::motor RF;
extern vex::motor RB;

//BALL SUBSYSTEM
extern vex::motor flywheel;
extern vex::motor decsorer;
extern vex::motor intake;
extern vex::motor indexer;

//SENSORS
extern vex::gyro Gyro;
extern vex::accelerometer AccelerometerX;
extern vex::accelerometer AccelerometerZ;
extern vex::light Light;
extern vex::pot Pot;
extern vex::digital_out LED;

extern double potVal;
extern int autonState;
extern bool blinkLED;
extern bool activeBrakeOn;

#endif