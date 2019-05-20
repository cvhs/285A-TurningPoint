#include "../config/config.h"
#include "../assistants/assistants.h"
#include "drivecontrol.h"
using namespace vex;

void drivecontrol() {
  LF.setStopping(brakeType::coast);
  RF.setStopping(brakeType::coast);
  LB.setStopping(brakeType::coast);
  RB.setStopping(brakeType::coast);
  LED.set(false);
    
  while (1) {
 
      //DRIVE 
      double leftPower = (double)Controller1.Axis3.value() + (double)Controller1.Axis1.value();
      double rightPower = (double)Controller1.Axis3.value() - (double)Controller1.Axis1.value();
      leftDrive(leftPower);
      rightDrive(rightPower);
      
      if (Controller1.ButtonDown.pressing()) {
          while(Controller1.ButtonDown.pressing()) {}
          if (activeBrakeOn) {
              LF.setStopping(brakeType::coast);
              RF.setStopping(brakeType::coast);
              LB.setStopping(brakeType::coast);
              RB.setStopping(brakeType::coast);
              activeBrakeOn = false;
              LED.set(false);
          } else {
              LF.setStopping(brakeType::hold);
              RF.setStopping(brakeType::hold);
              LB.setStopping(brakeType::hold);
              RB.setStopping(brakeType::hold);
              activeBrakeOn = true;
              LED.set(true);
          }
      }
      vex::task::sleep(20); 
    }
}