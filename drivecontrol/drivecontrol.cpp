#include "../config/config.h"
#include "drivecontrol.h"
using namespace vex;

void drivecontrol() {
  bool activeBrakeOn = false;
  /*MotorL1.setStopping( brakeType::hold );
  MotorL2.setStopping( brakeType::brake );
  MotorR1.setStopping( brakeType::brake );
  MotorR2.setStopping( brakeType::brake );*/

  while (1) {
    double vL = (double)Controller1.Axis3.value() * 12.0 / 127;
      MotorL1.spin( directionType::fwd, vL, voltageUnits::volt );
      MotorL2.spin( directionType::rev, vL, voltageUnits::volt );
      double vR = (double)Controller1.Axis2.value() * 12.0 / 127;
      MotorR1.spin( directionType::fwd, vR, voltageUnits::volt );
      MotorR2.spin( directionType::rev, vR, voltageUnits::volt );
      this_thread::sleep_for(10);

      // ACTIVE BRAKE
      if (Controller1.ButtonUp.pressing()) {
          while (Controller1.ButtonUp.pressing()){}
          activeBrakeOn = !activeBrakeOn;
          if (activeBrakeOn) {
              LED.set(false);
              MotorL1.setStopping( brakeType::hold );
              MotorL2.setStopping( brakeType::hold );
              MotorR1.setStopping( brakeType::hold );
              MotorR2.setStopping( brakeType::hold );
          } else {
              LED.set(true);
              MotorL1.setStopping( brakeType::brake );
              MotorL2.setStopping( brakeType::brake );
              MotorR1.setStopping( brakeType::brake );
              MotorR2.setStopping( brakeType::brake );
          }

      }

    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources.
  }
}