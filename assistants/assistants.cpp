// assistants.cpp
#include "../config/config.h"
#include "assistants.h"
using namespace vex;


void leftDrive(double x) {
    double vL = (double)x * 12.0 / 127;
    MotorLF.spin(directionType::fwd, vL, voltageUnits::volt);
    MotorLB.spin(directionType::fwd, vL, voltageUnits::volt);
}

void rightDrive(double x) {
    double vR = (double)x * -12.0 / 127;
    MotorRF.spin(directionType::fwd, vR, voltageUnits::volt);
    MotorRB.spin(directionType::fwd, vR, voltageUnits::volt);
}

int intakeTask() {
    bool intakeOn = false;
    double intakeSpeedPCT = 100;
    while(true) {
        if (Controller1.ButtonR2.pressing()) {
            while(Controller1.ButtonR2.pressing()) {}
            intakeOn = !intakeOn;
        }
        if (Controller1.ButtonR1.pressing()) {
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
        } else if (Controller1.ButtonA.pressing()) {
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
        if (Controller1.ButtonL1.pressing()) {
            while(Controller1.ButtonL1.pressing()) {}
            descorerDown = !descorerDown;
            if (descorerDown) {
                decsorer.setStopping(brakeType::hold);
                //decsorer.rotateTo(550, rotationUnits::deg, 100, velocityUnits::pct);
                decsorer.rotateTo(180, rotationUnits::deg, 100, velocityUnits::pct);
                //decsorer.rotateTo(3200, rotationUnits::deg, 90, velocityUnits::pct);
            } else {
                decsorer.setStopping(brakeType::coast);
                decsorer.rotateTo(-10, rotationUnits::deg, 90, velocityUnits::pct);
                decsorer.stop();
                decsorer.resetRotation();
            }
        }
       
        if (Controller1.ButtonL2.pressing()){
            while(Controller1.ButtonL2.pressing()) {}
            descorerDownX = !descorerDownX;
            if(descorerDownX){
                decsorer.setStopping(brakeType::hold);
                decsorer.rotateTo(1100, rotationUnits::deg, 90, velocityUnits::pct);
            } else {
                decsorer.setStopping(brakeType::coast);
                decsorer.rotateTo(-10, rotationUnits::deg, 90, velocityUnits::pct);
                decsorer.stop();
                decsorer.resetRotation();
            }
            
        }
        
       if (Controller1.ButtonUp.pressing()){
            while(Controller1.ButtonUp.pressing()) {}
            descorerDownUp = !descorerDownUp;
            if(descorerDownUp){
                decsorer.setStopping(brakeType::coast);
                decsorer.rotateTo(1400, rotationUnits::deg, 80, velocityUnits::pct);
            } else {
                decsorer.setStopping(brakeType::coast);
                decsorer.rotateTo(-10, rotationUnits::deg, 90, velocityUnits::pct);
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

int ledBlinkLoop() {
    while(true) {
        
        if (blinkLED) {
           LED.set(!LED.value());
        }
        vex::task::sleep(500);
    }
}