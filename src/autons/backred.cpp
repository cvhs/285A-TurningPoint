#include "autons.h"
#include "../config/config.h"
#include "../assistants/assistants.h"
#include "../PID/movePID.h"
#include "../PID/turnPID.h"
using namespace vex;

void backRed() {
    intake.spin(directionType::rev,100,velocityUnits::pct);
    //FORWARD: 1020 degrees
    moveForwardFor(1020, 1020, 127, 127);

    //moveForwardFor(-1020, -1020, 127, 127);
    //TURN: 110 degrees clockwise
    
    turnClockwiseFor(-1150);

    //BACKWARDS: 270 degrees
    moveForwardFor(-500, -500, 127, 127);

    decsorer.rotateTo(150, rotationUnits::deg, 100, velocityUnits::pct);
    vex::task::sleep(500);
    decsorer.rotateTo(0, rotationUnits::deg, 100, velocityUnits::pct);
    //TURN: 37 degrees clockwise
    turnClockwiseFor(-360);

    //FORWARD: 1300 degrees
    moveForwardFor(1120, 1120, 127, 127);
    intake.spin(directionType::rev,0,velocityUnits::pct);
    
    

    
    
    //TURN
    turnClockwiseFor(610);
    
    //FORWARD
    moveForwardFor(480, 480, 127, 127);
    
    //TURN
    turnClockwiseFor(900);
    
    
    
    //FORWARD
    leftDrive(100);
    rightDrive(100);
    vex::task::sleep(1500);
    leftDrive(0);
    rightDrive(0);
    vex::task::sleep(100);
}