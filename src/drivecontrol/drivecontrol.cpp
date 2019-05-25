#include "../config/config.h"
#include "../assistants/assistants.h"
#include "drivecontrol.h"
using namespace vex;

void drivecontrol() {
  MotorLF.setStopping(brakeType::hold);
  MotorRF.setStopping(brakeType::hold);
  MotorLB.setStopping(brakeType::hold);
  MotorRB.setStopping(brakeType::hold);
  LED.set(false);
  activeBrakeOn = true;
  while (1) {
 
      //DRIVE 
      double leftPower = (double)Controller1.Axis3.value() + (double)Controller1.Axis1.value();
      double rightPower = (double)Controller1.Axis3.value() - (double)Controller1.Axis1.value();

      if (Controller1.ButtonDown.pressing()) {
          while(Controller1.ButtonDown.pressing()) {}
          if (activeBrakeOn) {
              MotorLF.setStopping(brakeType::coast);
              MotorRF.setStopping(brakeType::coast);
              MotorLB.setStopping(brakeType::coast);
              MotorRB.setStopping(brakeType::coast);
              activeBrakeOn = false;
              LED.set(true);
          } else {
              MotorLF.setStopping(brakeType::hold);
              MotorRF.setStopping(brakeType::hold);
              MotorLB.setStopping(brakeType::hold);
              MotorRB.setStopping(brakeType::hold);
              activeBrakeOn = true;
              LED.set(false);
          }
      }

      if (activeBrakeOn) {
        if (leftPower > 20 || rightPower > 20) {
          leftDrive(leftPower);
          rightDrive(rightPower);
        } else {
          MotorLF.stop(brakeType::hold);
          MotorRF.stop(brakeType::hold);
          MotorLB.stop(brakeType::hold);
          MotorRB.stop(brakeType::hold);
        }
      } else {
        leftDrive(leftPower);
        rightDrive(rightPower);
      }
      vex::task::sleep(20); 
    }
}