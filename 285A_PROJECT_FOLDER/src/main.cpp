#include "assistants.h"
#include "autons.h"
#include "vex.h"

using namespace vex;

assistants assist;


void pre_auton(void) {
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  // Gyro.startCalibration();
  Pot.value(analogUnits::pct);
}

// AUTON FUNCTIONS

void autonomous(void) {
  vex::task::sleep(150);
  int autonState = 10;
  Controller1.Screen.print(Pot.value(vex::percentUnits::pct));
  Brain.Screen.setFont(vex::fontType::prop40);
  double potVal = Pot.value(vex::percentUnits::pct);
  if (potVal <= 10) {
    if (autonState != 0) {
      assist.flat();
      Brain.Screen.printAt(250, 100, true, "RED FRONT      ");
      Brain.Screen.drawCircle(40, 80, 15, vex::color::green);
    }
    autonState = 0;
  } else if (potVal > 10 && potVal <= 20) {
    if (autonState != 1) {
      assist.flat();
      Brain.Screen.printAt(250, 100, true, "RED BACK        ");
      Brain.Screen.drawCircle(40, 160, 15, vex::color::green);
    }
    autonState = 1;
  } else if (potVal > 20 && potVal <= 30) {
    if (autonState != 2) {
      assist.flat();
      Brain.Screen.printAt(250, 100, true, "BLUE FRONT       ");
      Brain.Screen.drawCircle(200, 80, 15, vex::color::green);
    }
    autonState = 2;
  } else if (potVal > 30 && potVal < 40) {
    if (autonState != 3) {
      assist.flat();
      Brain.Screen.printAt(250, 100, true, "BLUE BACK       ");
      Brain.Screen.drawCircle(200, 160, 15, vex::color::green);
    }
    autonState = 3;
  } else {
    if (autonState != 4) {
      assist.flat();
      Brain.Screen.printAt(250, 100, true, "SKILLS          ");
      Brain.Screen.drawCircle(40, 80, 15, vex::color::white);
    }
    autonState = 4;
  }

  autons aut;

  if (potVal > 40) {
    // SKILLS
  } else if (potVal <= 10) {
    // RED FRONT
    aut.redFront();
  } else if (potVal <= 20 && potVal > 10) {
    // RED BACK
    aut.redBack();
  } else if (potVal <= 30 && potVal > 20) {
    // BLUE FRONT
    aut.blueFront();
  } else if (potVal <= 40 && potVal > 30) {
    // BLUE BACK
    aut.blueBack();
  }
}



void usercontrol(void) {
  // GUI
  vex::task t4(assist.GUI());

  // TELEMETRY
  vex::task t3(assist.telemetryTask());
  LED.set(true);

  // DESCORER
  vex::task t1(assist.descorerTask());

  // INTAKE
  vex::task t2(assist.intakeTask());

  // FLYWHEEL
  flywheel.spin(directionType::rev, 540, velocityUnits::rpm);

  // DRIVE
  bool activeBrakeOn = false;
  /*MotorL1.setStopping( brakeType::hold );
  MotorL2.setStopping( brakeType::brake );
  MotorR1.setStopping( brakeType::brake );
  MotorR2.setStopping( brakeType::brake );*/

  while (1) {
    double vL = (double)Controller1.Axis3.value() * 12.0 / 127;
    MotorL1.spin(directionType::fwd, vL, voltageUnits::volt);
    MotorL2.spin(directionType::rev, vL, voltageUnits::volt);
    double vR = (double)Controller1.Axis2.value() * 12.0 / 127;
    MotorR1.spin(directionType::fwd, vR, voltageUnits::volt);
    MotorR2.spin(directionType::rev, vR, voltageUnits::volt);
    this_thread::sleep_for(10);

    // ACTIVE BRAKE
    if (Controller1.ButtonUp.pressing()) {
      while (Controller1.ButtonUp.pressing()) {
      }
      activeBrakeOn = !activeBrakeOn;
      if (activeBrakeOn) {
        LED.set(false);
        MotorL1.setStopping(brakeType::hold);
        MotorL2.setStopping(brakeType::hold);
        MotorR1.setStopping(brakeType::hold);
        MotorR2.setStopping(brakeType::hold);
      } else {
        LED.set(true);
        MotorL1.setStopping(brakeType::brake);
        MotorL2.setStopping(brakeType::brake);
        MotorR1.setStopping(brakeType::brake);
        MotorR2.setStopping(brakeType::brake);
      }
    }

    vex::task::sleep(20); // Sleep the task for a short amount of time to
                          // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {

  // Run the pre-autonomous function.
  pre_auton();

  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Prevent main from exiting with an infinite loop.
  while (1) {
    vex::task::sleep(100); // Sleep the task for a short amount of time to
                           // prevent wasted resources.
  }
}
