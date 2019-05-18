#include "config.h"
#include "vex.h"

using namespace vex;

class assistants {
public:
  // GUI ASSIST FUNCTIONS
  void flat(void) {
    // Field
    Brain.Screen.drawRectangle(20, 20, 200, 200, "#A9A9A9");
    Brain.Screen.drawRectangle(20, 60, 40, 40, vex::color::red);
    Brain.Screen.drawRectangle(20, 140, 40, 40, vex::color::red);
    Brain.Screen.drawRectangle(180, 60, 40, 40, vex::color::blue);
    Brain.Screen.drawRectangle(180, 140, 40, 40, vex::color::blue);

    // Flags
    Brain.Screen.drawRectangle(40, 20, 20, 15, vex::color::blue);
    Brain.Screen.drawRectangle(60, 20, 20, 15, vex::color::red);

    Brain.Screen.drawRectangle(100, 20, 20, 15, vex::color::blue);
    Brain.Screen.drawRectangle(120, 20, 20, 15, vex::color::red);

    Brain.Screen.drawRectangle(160, 20, 20, 15, vex::color::blue);
    Brain.Screen.drawRectangle(180, 20, 20, 15, vex::color::red);
  }

  task GUI() {
    flat();
    Brain.Screen.setFont(vex::fontType::prop40);

    int autonState = 10;
    while (true) {
      double potVal = Pot.value(vex::percentUnits::pct);
      if (potVal <= 10) {
        if (autonState != 0) {
          assistants::flat();
          Brain.Screen.printAt(250, 100, true, "RED FRONT      ");
          Brain.Screen.drawCircle(40, 80, 15, vex::color::green);
        }
        autonState = 0;
      } else if (potVal > 10 && potVal <= 20) {
        if (autonState != 1) {
          assistants::flat();
          Brain.Screen.printAt(250, 100, true, "RED BACK        ");
          Brain.Screen.drawCircle(40, 160, 15, vex::color::green);
        }
        autonState = 1;
      } else if (potVal > 20 && potVal <= 30) {
        if (autonState != 2) {
          assistants::flat();
          Brain.Screen.printAt(250, 100, true, "BLUE FRONT       ");
          Brain.Screen.drawCircle(200, 80, 15, vex::color::green);
        }
        autonState = 2;
      } else if (potVal > 30 && potVal < 40) {
        if (autonState != 3) {
          assistants::flat();
          Brain.Screen.printAt(250, 100, true, "BLUE BACK       ");
          Brain.Screen.drawCircle(200, 160, 15, vex::color::green);
        }
        autonState = 3;
      } else {
        if (autonState != 4) {
          assistants::flat();
          Brain.Screen.printAt(250, 100, true, "SKILLS          ");
          Brain.Screen.drawCircle(40, 80, 15, vex::color::white);
        }
        autonState = 4;
      }
    }
  }

  // DRIVER ASSISTANT FUNCTIONS
  task intakeTask() {
    bool intakeOn = false;
    double intakeSpeedPCT = 100;
    while (true) {
      if (Controller1.ButtonR2.pressing()) {
        while (Controller1.ButtonR2.pressing()) {
        }
        intakeOn = !intakeOn;
      }
      if (Controller1.ButtonL1.pressing()) {
        // Intake
        intakeOn = false;

        /*if(Light.value(analogUnits::pct) < 40){
            this_thread::sleep_for(1000);
            decsorer.setStopping(brakeType::hold);
            decsorer.rotateTo(100, rotationUnits::deg, 80, velocityUnits::pct);
        } else {
            decsorer.setStopping(brakeType::coast);
            decsorer.rotateTo(-10, rotationUnits::deg, 80, velocityUnits::pct);
        }*/
        intake.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
        indexer.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
      } else if (Controller1.ButtonR1.pressing()) {
        // Reverse
        // Turn off ball intake indexer sensor stuff
        intakeOn = false;
        intake.spin(vex::directionType::fwd, intakeSpeedPCT,
                    vex::velocityUnits::pct);
        indexer.spin(directionType::rev, 100, vex::velocityUnits::pct);
      } else {

        if (intakeOn) {

          if (Light.value(analogUnits::pct) > 50) {
            intake.spin(directionType::rev, intakeSpeedPCT,
                        vex::velocityUnits::pct);
            indexer.spin(vex::directionType::fwd, 34, vex::velocityUnits::pct);

          } else {
            intake.spin(directionType::rev, 80, vex::velocityUnits::pct);
            indexer.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
          }

        } else {
          intake.spin(directionType::fwd, 0, vex::velocityUnits::pct);
          indexer.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
        }
      }
    }
  }

  task descorerTask() {
    bool descorerDown = false;
    bool descorerDownX = false;
    bool descorerDownUp = false;
    while (true) {
      decsorer.setTimeout(1, vex::timeUnits::sec);
      if (Controller1.ButtonL2.pressing()) {
        while (Controller1.ButtonL2.pressing()) {
        }
        descorerDown = !descorerDown;
        if (descorerDown) {
          decsorer.setStopping(brakeType::coast);
          // decsorer.rotateTo(550, rotationUnits::deg, 100,
          // velocityUnits::pct);
          decsorer.rotateTo(100, rotationUnits::deg, 70, velocityUnits::pct);
          // decsorer.rotateTo(3200, rotationUnits::deg, 90,
          // velocityUnits::pct);
        } else {
          decsorer.setStopping(brakeType::coast);
          decsorer.rotateTo(-20, rotationUnits::deg, 60, velocityUnits::pct);
          decsorer.stop();
        }
      }

      if (Controller1.ButtonX.pressing()) {
        while (Controller1.ButtonX.pressing()) {
        }
        descorerDownX = !descorerDownX;
        if (descorerDownX) {
          decsorer.setStopping(brakeType::coast);
          decsorer.rotateTo(1500, rotationUnits::deg, 90, velocityUnits::pct);
        } else {
          decsorer.setStopping(brakeType::coast);
          decsorer.rotateTo(-20, rotationUnits::deg, 90, velocityUnits::pct);
          decsorer.stop();
        }
      }

      if (Controller1.ButtonUp.pressing()) {
        while (Controller1.ButtonUp.pressing()) {
        }
        descorerDownUp = !descorerDownUp;
        if (descorerDownUp) {
          decsorer.setStopping(brakeType::coast);
          decsorer.rotateTo(1100, rotationUnits::deg, 80, velocityUnits::pct);
        } else {
          decsorer.setStopping(brakeType::coast);
          decsorer.rotateTo(-20, rotationUnits::deg, 90, velocityUnits::pct);
          decsorer.stop();
        }
      }
      this_thread::sleep_for(10);
    }
  }

  task telemetryTask() {

    while (true) {
      Controller1.Screen.print(flywheel.velocity(velocityUnits::rpm));
      this_thread::sleep_for(1000);
    }
  }
};
