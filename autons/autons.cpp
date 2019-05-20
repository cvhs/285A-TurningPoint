#include "../config/config.h"
#include "autons.h"
#include "../assistants/assistants.h"
#include "../PID/movePID.h"
#include "../PID/turnPID.h"
using namespace vex;


// AUTONS

void backBlue() {
    intake.spin(directionType::rev,100,velocityUnits::pct);
    //FORWARD: 1020 degrees
    moveForwardFor(1020, 1020, 127, 127);

    //moveForwardFor(-1020, -1020, 127, 127);
    //TURN: 110 degrees clockwise
    
    turnClockwiseFor(1150);

    //BACKWARDS: 270 degrees
    moveForwardFor(-390, -390, 127, 127);

    decsorer.rotateTo(150, rotationUnits::deg, 100, velocityUnits::pct);
    vex::task::sleep(500);
    decsorer.rotateTo(0, rotationUnits::deg, 100, velocityUnits::pct);
    //TURN: 37 degrees clockwise
    turnClockwiseFor(400);

    //FORWARD: 1300 degrees
    moveForwardFor(1300, 1300, 127, 127);
    intake.spin(directionType::rev,0,velocityUnits::pct);
    
    

    
    
    //TURN
    turnClockwiseFor(-610);
    
    //FORWARD
    moveForwardFor(370, 370, 127, 127);
    
    //TURN
    turnClockwiseFor(-900);
    
    
    
    //FORWARD
    leftDrive(100);
    rightDrive(100);
    vex::task::sleep(1500);
    leftDrive(0);
    rightDrive(0);
    vex::task::sleep(100);
}

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
    /*turnClockwiseFor(-360);

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
    vex::task::sleep(100);*/
}


void frontRed() {
    
    flywheel.spin(directionType::rev, 540, velocityUnits::rpm);
    intake.spin(directionType::rev,100,velocityUnits::pct);
    //FORWARD: 1020 degrees
    moveForwardFor(1120, 1120, 127, 127);
    leftDrive(0);
    rightDrive(0);
    vex::task::sleep(500);
    moveForwardFor(-1300, -1300, 127, 127);
    turnClockwiseFor(-825);
    indexer.rotateFor(360, rotationUnits::deg,100,velocityUnits::pct);
    moveForwardFor(710, 710, 127, 127);
    indexer.rotateFor(360, rotationUnits::deg, 100, velocityUnits::pct);
    moveForwardFor(700, 700, 127, 127);
    moveForwardFor(-2200, -2200, 127, 127);
    turnClockwiseFor(900);
    leftDrive(100);
    rightDrive(100);
    vex::task::sleep(1900);
    leftDrive(0);
    rightDrive(0);
    vex::task::sleep(100);
}

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





// EXECUTE

void execute() {
  if (potVal > 40){
  //SKILLS

  } else if (potVal <= 10) {
  //RED FRONT
  frontRed();
  } else if (potVal <= 20 && potVal > 10) {
  //RED BACK
  backRed();
  } else if (potVal <= 30 && potVal > 20) {
  //BLUE FRONT
  frontBlue();
  } else if (potVal <= 40 && potVal > 30){
  //BLUE BACK
  backBlue();
  }
}


