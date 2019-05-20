#include "../config/config.h"
#include "autons.h"

using namespace vex;

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


// EXECUTE

void execute() {
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


