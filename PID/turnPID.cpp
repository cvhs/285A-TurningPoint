#include "../config/config.h"
#include "../assistants/assistants.h"
#include "turnPID.h"
using namespace vex;

double turnTarget = 0;
bool TURN_NOT_FINISH = true;
int turnPID() {
    TURN_NOT_FINISH = true;
    double sensorValue = Gyro.value(rotationUnits::raw);
    double error = turnTarget - sensorValue;
    double oldError = error;
    double accumilatedError = 0;


    while(TURN_NOT_FINISH) {
        sensorValue = Gyro.value(rotationUnits::raw);
        error = turnTarget - sensorValue;
        double changeInError = oldError - error;
        if (fabs(error) < 50.0) {
            accumilatedError += error;
        } else {
            accumilatedError = 0;
        }

        double kP = 0.35;
        double kI = 0.13;
        double kD = 0.35;

        double P = kP * error;
        double I = kI * accumilatedError;
        double D = kD * changeInError;

        double sum = P - D + I;


        if (fabs(sum) > 100) {
            if (sum < 0) {
                sum = -100;
            } else {
                sum = 100;
            }
        }

        leftDrive(sum);
        rightDrive(-sum);

        double errorThreshold = 10;
        double velocityThreshold = 5;

        TURN_NOT_FINISH = !((fabs(error) < errorThreshold) && (fabs(changeInError) < velocityThreshold));


        oldError = error;
        vex::task::sleep(50);
        Brain.Screen.printAt(1,40,"Error: %f%%",error);

        Brain.Screen.printAt(1,80,"FinishNot: %d%%", TURN_NOT_FINISH);
    }
    leftDrive(0);
    rightDrive(0);
    return 0;
}

void turnClockwiseTo(int x) {
    turnTarget = x;
    vex::task turning(turnPID);
    while(TURN_NOT_FINISH){
        vex::task::sleep(50);
    }
    turning.stop();
    leftDrive(0);
    rightDrive(0);
    TURN_NOT_FINISH = true;
}

void turnClockwiseFor(int x) {
    double turnTo = x + Gyro.value(rotationUnits::raw);;
    turnClockwiseTo(turnTo);

}