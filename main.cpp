#include "vex.h"
#include "config.h"
using namespace vex;



int intakeTask() {
    bool intakeOn = false;
    double intakeSpeedPCT = 100;
    while(true) {
        if (Controller1.ButtonR2.pressing()) {
            while(Controller1.ButtonR2.pressing()) {}
            intakeOn = !intakeOn;
        }
        if (Controller1.ButtonL1.pressing()) {
            //Intake
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
            //Reverse
            //Turn off ball intake indexer sensor stuff
            intakeOn = false;
            intake.spin(vex::directionType::fwd, intakeSpeedPCT, vex::velocityUnits::pct);
            indexer.spin(directionType::rev, 100, vex::velocityUnits::pct);
        } else {

            if (intakeOn) {


                if(Light.value(analogUnits::pct) > 50){
                    intake.spin(directionType::rev, intakeSpeedPCT, vex::velocityUnits::pct);
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
    return(0);
}

int descorerTask() {
    bool descorerDown = false;
    bool descorerDownX = false;
    bool descorerDownUp = false;
    while(true) {
        decsorer.setTimeout(1,vex::timeUnits::sec);
        if (Controller1.ButtonL2.pressing()) {
            while(Controller1.ButtonL2.pressing()) {}
            descorerDown = !descorerDown;
            if (descorerDown) {
                decsorer.setStopping(brakeType::coast);
                //decsorer.rotateTo(550, rotationUnits::deg, 100, velocityUnits::pct);
                decsorer.rotateTo(100, rotationUnits::deg, 70, velocityUnits::pct);
                //decsorer.rotateTo(3200, rotationUnits::deg, 90, velocityUnits::pct);
            } else {
                decsorer.setStopping(brakeType::coast);
                decsorer.rotateTo(-20, rotationUnits::deg, 60, velocityUnits::pct);
                decsorer.stop();
            }
        }

        if (Controller1.ButtonX.pressing()){
            while(Controller1.ButtonX.pressing()) {}
            descorerDownX = !descorerDownX;
            if(descorerDownX){
                decsorer.setStopping(brakeType::coast);
                decsorer.rotateTo(1500, rotationUnits::deg, 90, velocityUnits::pct);
            } else {
                decsorer.setStopping(brakeType::coast);
                decsorer.rotateTo(-20, rotationUnits::deg, 90, velocityUnits::pct);
                decsorer.stop();
            }

        }

       if (Controller1.ButtonUp.pressing()){
            while(Controller1.ButtonUp.pressing()) {}
            descorerDownUp = !descorerDownUp;
            if(descorerDownUp){
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
    return(0);
}

int telemetryTask() {

    while(true) {
        Controller1.Screen.print(flywheel.velocity(velocityUnits::rpm));
        this_thread::sleep_for(1000);
    }
    return(0);
}

void flat(void) {
    // Field
    Brain.Screen.drawRectangle(20,20,200,200,"#A9A9A9");
    Brain.Screen.drawRectangle(20,60,40,40,vex::color::red);
    Brain.Screen.drawRectangle(20,140,40,40,vex::color::red);
    Brain.Screen.drawRectangle(180,60,40,40,vex::color::blue);
    Brain.Screen.drawRectangle(180,140,40,40,vex::color::blue);

    // Flags
    Brain.Screen.drawRectangle(40, 20, 20, 15, vex::color::blue);
    Brain.Screen.drawRectangle(60, 20, 20, 15, vex::color::red);

    Brain.Screen.drawRectangle(100, 20, 20, 15, vex::color::blue);
    Brain.Screen.drawRectangle(120, 20, 20, 15, vex::color::red);

    Brain.Screen.drawRectangle(160, 20, 20, 15, vex::color::blue);
    Brain.Screen.drawRectangle(180, 20, 20, 15, vex::color::red);
}

void pre_auton( void ) {
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
    //Gyro.startCalibration();
    Pot.value(analogUnits::pct);
}

//AUTON FUNCTIONS
void motors(int degrees, int power) {
    //L1 = LF
    //R1 = RF

    LF.rotateFor(degrees,vex::rotationUnits::deg,power,vex::velocityUnits::pct, false);
    LB.rotateFor(degrees,vex::rotationUnits::deg,power,vex::velocityUnits::pct, false);
    RF.rotateFor(degrees,vex::rotationUnits::deg,power,vex::velocityUnits::pct, false);
    RB.rotateFor(degrees,vex::rotationUnits::deg,power,vex::velocityUnits::pct);
}

void turnCW(int degrees, int power){
    LF.rotateFor(degrees,vex::rotationUnits::deg,power,vex::velocityUnits::pct, false);
    LB.rotateFor(degrees,vex::rotationUnits::deg,power,vex::velocityUnits::pct, false);
    RF.rotateFor(-degrees,vex::rotationUnits::deg,power,vex::velocityUnits::pct, false);
    RB.rotateFor(-degrees,vex::rotationUnits::deg,power,vex::velocityUnits::pct);

}

/*void turnGyro(int degrees, int power){
    float lastError = 0;
    float erTotal = 0;
    float lastD = 0;

    int target = degrees;

    float kp = 0;
    float ki = 0;
    float kd = 0;

    globalTurnError = Gyro.


}*/

void autonomous( void ) {
  vex::task::sleep(150);
    int autonState = 10;
    Controller1.Screen.print(Pot.value(vex::percentUnits::pct));
    Brain.Screen.setFont(vex::fontType::prop40);
    double potVal = Pot.value(vex::percentUnits::pct);
    if (potVal <= 10){
        if (autonState != 0) {
            flat();
            Brain.Screen.printAt(250,100,true,"RED FRONT      ");
            Brain.Screen.drawCircle(40,80,15,vex::color::green);
        }
        autonState = 0;
    } else if (potVal > 10 && potVal <= 20){
        if (autonState != 1) {
            flat();
            Brain.Screen.printAt(250,100,true,"RED BACK        ");
            Brain.Screen.drawCircle(40,160,15,vex::color::green);
        }
        autonState = 1;
    } else if (potVal > 20 && potVal <= 30){
        if (autonState != 2) {
            flat();
            Brain.Screen.printAt(250,100,true,"BLUE FRONT       ");
            Brain.Screen.drawCircle(200,80,15,vex::color::green);
        }
        autonState = 2;
    } else if (potVal > 30 && potVal < 40){
        if (autonState != 3) {
            flat();
            Brain.Screen.printAt(250,100,true,"BLUE BACK       ");
            Brain.Screen.drawCircle(200,160,15,vex::color::green);
        }
        autonState = 3;
    } else {
        if (autonState != 4) {
            flat();
            Brain.Screen.printAt(250,100,true,"SKILLS          ");
            Brain.Screen.drawCircle(40,80,15,vex::color::white);
        }
        autonState = 4;
    }


  if (potVal > 40){
      //SKILLS

  } else if (potVal <= 10) {
  //RED FRONT
  flywheel.spin( directionType::fwd, 180, velocityUnits::rpm);
  intake.spin(directionType::rev, 80, velocityUnits::pct);
  motors(1100, 60);
  vex::task::sleep(800);
  motors(-1000, 50);
  vex::task::sleep(500);
  turnCW(-270, 50);
  vex::task::sleep(500);

  motors(60, 20);
  indexer.rotateFor(470, vex::rotationUnits::deg, 100, vex::velocityUnits::pct);
  motors(665, 30);
   indexer.rotateFor(600, vex::rotationUnits::deg, 100, vex::velocityUnits::pct);
   //motors(530, 60);
    intake.stop();
   turnCW(-35, 50);
   LF.spin(directionType::fwd, 95, velocityUnits::pct);
   LB.spin(directionType::fwd, 95, velocityUnits::pct);
   RF.spin(directionType::fwd, 95, velocityUnits::pct);
   RB.spin(directionType::fwd, 95, velocityUnits::pct);
   vex::task::sleep(800);
   LF.spin(directionType::fwd, 0, velocityUnits::pct);
   LB.spin(directionType::fwd, 0, velocityUnits::pct);
   RF.spin(directionType::fwd, 0, velocityUnits::pct);
   RB.spin(directionType::fwd, 0, velocityUnits::pct);
   motors(-695, 50);
   turnCW(290, 40);
   intake.spin(directionType::fwd, 80, velocityUnits::pct);
   motors(750, 60);
   intake.stop();
   motors(-700, 50);
  } else if (potVal <= 20 && potVal > 10) {
     //RED BACK
      intake.spin(directionType::rev, 60, velocityUnits::pct);
      //Collect ball
      motors(1050, 50);
      vex::task::sleep(500);
      motors(-965, 50);
      vex::task::sleep(500);
      //Turn
      intake.stop();
      turnCW(-280, 50);
      vex::task::sleep(500);
      //Move forward towards platform
      motors(590, 50);
      //Turn towards platform
      turnCW(280, 30);
      //Platform
      LF.spin(directionType::fwd, 80, velocityUnits::pct);
       LB.spin(directionType::fwd, 80, velocityUnits::pct);
       RF.spin(directionType::fwd, 80, velocityUnits::pct);
       RB.spin(directionType::fwd, 80, velocityUnits::pct);
        vex::task::sleep(1800);
    LF.spin(directionType::fwd, 0, velocityUnits::pct);
       LB.spin(directionType::fwd, 0, velocityUnits::pct);
       RF.spin(directionType::fwd, 0, velocityUnits::pct);
       RB.spin(directionType::fwd, 0, velocityUnits::pct);
  } else if (potVal <= 30 && potVal > 20) {
           //BLUE FRONT
      flywheel.spin( directionType::fwd, 180, velocityUnits::rpm);
      intake.spin(directionType::rev, 60, velocityUnits::pct);
      motors(1050, 50);
      vex::task::sleep(500);
      motors(-965, 50);
      vex::task::sleep(500);
      turnCW(274, 50);
      vex::task::sleep(500);
      motors(170, 30);
      indexer.rotateFor(560, vex::rotationUnits::deg, 100, vex::velocityUnits::pct);
      //indexer.spin(directionType::fwd, 100, velocityUnits::pct);
      //vex::task::sleep(300);
      //indexer.stop();
      //intake.spin(directionType::rev, 100, velocityUnits::pct);
      motors(600, 30);

       indexer.rotateFor(600, vex::rotationUnits::deg, 100, vex::velocityUnits::pct);
       turnCW(46, 50);
       motors(530, 60);
       RF.rotateFor(140,vex::rotationUnits::deg,70,vex::velocityUnits::pct, false);
       RB.rotateFor(140,vex::rotationUnits::deg,70,vex::velocityUnits::pct);
       LF.spin(directionType::fwd, 60, velocityUnits::pct);
       LB.spin(directionType::fwd, 60, velocityUnits::pct);
       RF.spin(directionType::fwd, 60, velocityUnits::pct);
       RB.spin(directionType::fwd, 60, velocityUnits::pct);
       vex::task::sleep(350);

      motors(-650, 50);
       turnCW(-280, 40);
    intake.spin(directionType::fwd, 80, velocityUnits::pct);
    motors(750, 50);
   intake.stop();
   motors(-700, 50);
      /* motors(-2050, 100);
       turnCW(-320, 70);
       vex::task::sleep(300);
       LF.spin(directionType::fwd, 80, velocityUnits::pct);
       LB.spin(directionType::fwd, 80, velocityUnits::pct);
       RF.spin(directionType::fwd, 80, velocityUnits::pct);
       RB.spin(directionType::fwd, 80, velocityUnits::pct);
        vex::task::sleep(2900);

        motors(0,0);*/
       //motors(-500, 1000);

      /* indexer.spin(directionType::fwd, 100, velocityUnits::pct);
      vex::task::sleep(1000);
       indexer.stop();  */
  } else if (potVal <= 40 && potVal > 30){
      //BLUE BACK
      intake.spin(directionType::rev, 60, velocityUnits::pct);
      //Collect ball
      motors(1050, 50);
      vex::task::sleep(500);
      motors(-965, 50);
      vex::task::sleep(500);
      //Turn
      intake.stop();
      turnCW(280, 50);
      vex::task::sleep(500);
      //Move forward towards platform
      motors(660, 50);
      //Turn towards platform
      turnCW(-280, 30);
      //Platform
      LF.spin(directionType::fwd, 80, velocityUnits::pct);
       LB.spin(directionType::fwd, 80, velocityUnits::pct);
       RF.spin(directionType::fwd, 80, velocityUnits::pct);
       RB.spin(directionType::fwd, 80, velocityUnits::pct);
        vex::task::sleep(1700);
    LF.spin(directionType::fwd, 0, velocityUnits::pct);
       LB.spin(directionType::fwd, 0, velocityUnits::pct);
       RF.spin(directionType::fwd, 0, velocityUnits::pct);
       RB.spin(directionType::fwd, 0, velocityUnits::pct);

  }

}



int GUI() {
    flat();
    Brain.Screen.setFont(vex::fontType::prop40);

    int autonState = 10;
    while(true) {
        double potVal = Pot.value(vex::percentUnits::pct);
        if (potVal <= 10){
            if (autonState != 0) {
                flat();
                Brain.Screen.printAt(250,100,true,"RED FRONT      ");
                Brain.Screen.drawCircle(40,80,15,vex::color::green);
            }
            autonState = 0;
        } else if (potVal > 10 && potVal <= 20){
            if (autonState != 1) {
                flat();
                Brain.Screen.printAt(250,100,true,"RED BACK        ");
                Brain.Screen.drawCircle(40,160,15,vex::color::green);
            }
            autonState = 1;
        } else if (potVal > 20 && potVal <= 30){
            if (autonState != 2) {
                flat();
                Brain.Screen.printAt(250,100,true,"BLUE FRONT       ");
                Brain.Screen.drawCircle(200,80,15,vex::color::green);
            }
            autonState = 2;
        } else if (potVal > 30 && potVal < 40){
            if (autonState != 3) {
                flat();
                Brain.Screen.printAt(250,100,true,"BLUE BACK       ");
                Brain.Screen.drawCircle(200,160,15,vex::color::green);
            }
            autonState = 3;
        } else {
            if (autonState != 4) {
                flat();
                Brain.Screen.printAt(250,100,true,"SKILLS          ");
                Brain.Screen.drawCircle(40,80,15,vex::color::white);
            }
            autonState = 4;
        }
    }
    return(0);
}

void usercontrol( void ) {
    //GUI
    vex::task t4(GUI);

    //TELEMETRY
    vex::task t3(telemetryTask);
    LED.set(true);

    //DESCORER
    vex::task t1(descorerTask);

    //INTAKE
    vex::task t2(intakeTask);

    //FLYWHEEL
    flywheel.spin( directionType::rev, 540, velocityUnits::rpm);


    //DRIVE
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

//
// Main will set up the competition functions and callbacks.
//
int main() {

    //Run the pre-autonomous function.
    pre_auton();

    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );

    //Prevent main from exiting with an infinite loop.
    while(1) {
      vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }

}
