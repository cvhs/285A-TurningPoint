#include "autons.h"
#include "../config/config.h"
#include "../assistants/assistants.h"
#include "../PID/movePID.h"
#include "../PID/turnPID.h"
using namespace vex;

void frontBlue() {
    
  flywheel.spin(directionType::rev, 540, velocityUnits::rpm);
  intake.spin(directionType::rev,100,velocityUnits::pct);
  //FORWARD: 1020 degrees
  moveForwardFor(300, 300, 127, 127); // CHANGE TO NORMAL AT COMP
  leftDrive(0);
  rightDrive(0);
  vex::task::sleep(500);
  moveForwardFor(-480, -480, 127, 127); // CHANGE TO NORMAL AT COMP
  turnClockwiseFor(825);
  indexer.rotateFor(360, rotationUnits::deg);
  moveForwardFor(740, 710, 127, 127);
  indexer.rotateFor(360, rotationUnits::deg);
  moveForwardFor(700, 700, 127, 127);
  moveForwardFor(-2200, -2200, 127, 127);
  turnClockwiseFor(-900);
  leftDrive(100);
  rightDrive(100);
  vex::task::sleep(1900);
  leftDrive(0);
  rightDrive(0);
  vex::task::sleep(100);
    
}