#include "vex.h"
#include "config.h"

vex::brain       Brain;
vex::competition Competition;
vex::controller  Controller1;

// DRIVE
vex::motor MotorLF( vex::PORT1 );
vex::motor MotorLB( vex::PORT9 );
vex::motor MotorRF( vex::PORT7 );
vex::motor MotorRB( vex::PORT10 );

vex::motor LF = vex::motor(vex::PORT1);
vex::motor LB = vex::motor(vex::PORT9);
vex::motor RF = vex::motor(vex::PORT7);
vex::motor RB = vex::motor(vex::PORT10);

//BALL SUBSYSTEM
vex::motor flywheel = vex::motor(vex::PORT3, vex::gearSetting::ratio6_1);
vex::motor decsorer = vex::motor(vex::PORT11, vex::gearSetting::ratio18_1);
vex::motor intake = vex::motor(vex::PORT2, vex::gearSetting::ratio18_1);
vex::motor indexer = vex::motor(vex::PORT4, vex::gearSetting::ratio18_1);

//SENSORS
vex::gyro Gyro = vex::gyro(Brain.ThreeWirePort.C);
vex::accelerometer AccelerometerX = vex::accelerometer(Brain.ThreeWirePort.D);
vex::accelerometer AccelerometerZ = vex::accelerometer(Brain.ThreeWirePort.E);
vex::light Light = vex::light(Brain.ThreeWirePort.B);
vex::pot Pot = vex::pot(Brain.ThreeWirePort.A);
vex::digital_out LED = vex::digital_out(Brain.ThreeWirePort.F);


//GLOBALS
double potVal = 0;
int autonState = 0;
bool blinkLED = false;
bool activeBrakeOn = false;