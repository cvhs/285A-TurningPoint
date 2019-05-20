#include "../config/config.h"
#include "../assistants/assistants.h"
#include "movePID.h"

double moveTargetL = 0;
double moveTargetR = 0;

double vMaxL = 127;
double vMaxR = 127;
double leftSensor = (MotorLF.rotation(vex::rotationUnits::deg) + MotorLB.rotation(vex::rotationUnits::deg))/2;
double rightSensor = -(MotorRF.rotation(vex::rotationUnits::deg) + MotorRB.rotation(vex::rotationUnits::deg))/2;

bool MOVE_NOT_FINISHED = true;
int movePID() {
    MOVE_NOT_FINISHED = true;

    double leftError = moveTargetL - leftSensor;
    double rightError = moveTargetR - rightSensor;
    double oldLeftError = leftError;
    double oldRightError = rightError;
    double oldLeftVelocity = 0;
    double oldRightVelocity = 0;

    double accumilatedLeftError = 0;
    double accumilatedRightError = 0;

    double currentLMax = 0;
    double currentRMax = 0;
    double currentALMax = 0;
    double currentARMax = 0;


    while(MOVE_NOT_FINISHED) {
        leftSensor = (MotorLF.rotation(vex::rotationUnits::deg) + MotorLB.rotation(vex::rotationUnits::deg))/2;
        rightSensor = -(MotorRF.rotation(vex::rotationUnits::deg) + MotorRB.rotation(vex::rotationUnits::deg))/2;

        leftError = moveTargetL - leftSensor;
        rightError = moveTargetR - rightSensor;

        double leftVelocity = leftError - oldLeftError;
        double rightVelocity = rightError - oldRightError;
        double leftAcceleration = leftVelocity - oldLeftVelocity;
        double rightAcceleration = rightVelocity - oldRightVelocity;
        if (fabs(leftError) < 50) {
            accumilatedLeftError += leftError;
        } else {
            accumilatedLeftError += 0;
        }
        if (fabs(rightError) < 50) {
            accumilatedRightError += rightError;
        } else {
            accumilatedRightError += 0;
        }

        double kP = 0.4;
        double kI = 0.17;
        double kD = 0.25;
        double kA = 0;

        double P_L = kP * leftError;
        double P_R = kP * rightError;
        double I_L = kI * accumilatedLeftError;
        double I_R = kI * accumilatedRightError;
        double D_L = kD * leftVelocity;
        double D_R = kD * rightVelocity;
        double A_L = kA * leftAcceleration;
        double A_R = kA * rightAcceleration;

        double sum_L = P_L + D_L + A_L + I_L;
        double sum_R = P_R + D_R + A_R + I_R;


        if (fabs(sum_L) > vMaxL) {
            if (sum_L < 0) {
                sum_L = -vMaxL;
            } else {
                sum_L = vMaxL;
            }
        }
        if (fabs(sum_R) > vMaxR) {
            if (sum_R < 0) {
                sum_R = -vMaxR;
            } else {
                sum_R = vMaxR;
            }
        }

        leftDrive(sum_L);
        rightDrive(sum_R);

        double errorThreshold = 10;
        double velocityThreshold = 5;

        bool MOVE_NOT_FINISH_LEFT = !((fabs(leftError) < errorThreshold) && (fabs(leftVelocity) < velocityThreshold));
        bool MOVE_NOT_FINISH_RIGH = !((fabs(rightError) < errorThreshold) && (fabs(rightVelocity) < velocityThreshold));

        MOVE_NOT_FINISHED = MOVE_NOT_FINISH_LEFT || MOVE_NOT_FINISH_RIGH;

        oldLeftError = leftError;
        oldRightError = rightError;
        oldLeftVelocity = leftVelocity;
        oldRightVelocity = rightVelocity;

        vex::task::sleep(50);

        Brain.Screen.printAt(1,40,"Left Error: %f%%",leftError);
        Brain.Screen.printAt(1,80,"Righ Error: %f%%",rightError);

        if (fabs(currentLMax) < fabs(leftVelocity)) {
            Brain.Screen.printAt(1,120,"MaxL Veloc: %f%%",leftVelocity);
            currentLMax = leftVelocity;
        }
        if (fabs(currentRMax) < fabs(rightVelocity)) {
            Brain.Screen.printAt(1,160,"MaxR Veloc: %f%%",rightVelocity);
            currentRMax = rightVelocity;
        }

        if (fabs(currentALMax) < fabs(leftAcceleration)) {
            Brain.Screen.printAt(1,200,"AaxL Veloc: %f%%", leftAcceleration);
            currentALMax = leftAcceleration;
        }

        if (fabs(currentARMax) < fabs(rightAcceleration)) {
            Brain.Screen.printAt(1,240,"AaxR Veloc: %f%%", rightAcceleration);
            currentARMax = rightAcceleration;
        }


    }
    leftDrive(0);
    rightDrive(0);

    Brain.Screen.clearScreen();
    Brain.Screen.printAt(1,40,"Left Error: %f%%",leftError);
    Brain.Screen.printAt(1,80,"Righ Error: %f%%",rightError);

    return 0;
}

void moveForward(double degreesL, double degreesR, double velocityMaxL, double velocityMaxR) {
    moveTargetL = degreesL;
    moveTargetR = degreesR;
    vMaxL = velocityMaxL;
    vMaxR = velocityMaxR;
    vex::task moving(movePID);
    while(MOVE_NOT_FINISHED){
        vex::task::sleep(50);
    }
    moving.stop();
    leftDrive(0);
    rightDrive(0);
    MOVE_NOT_FINISHED = true;
}

void moveForwardFor(double degL, double degR, double vML, double vMR) {
    leftSensor = (MotorLF.rotation(vex::rotationUnits::deg) + MotorLB.rotation(vex::rotationUnits::deg))/2;
    rightSensor = -(MotorRF.rotation(vex::rotationUnits::deg) + MotorRB.rotation(vex::rotationUnits::deg))/2;
    moveForward(degL + leftSensor, degR + rightSensor, vML, vMR);
}