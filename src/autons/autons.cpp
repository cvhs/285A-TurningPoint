#include "autons.h"
#include "../config/config.h"
#include "../assistants/assistants.h"
#include "../PID/movePID.h"
#include "../PID/turnPID.h"
using namespace vex;


// EXECUTE

void execute() {
  double potVal = Pot.value(vex::percentUnits::pct);
  
  if (potVal > 40){
  //SKILLS

  } else if (potVal <= 10) {
  //RED FRONT IS BEST
  frontRed();
  } else if (potVal <= 20 && potVal > 10) {
  //RED BACK
  backRed();
  } else if (potVal <= 30 && potVal > 20) {
  //BLUE FRONT
  frontBlue();
  } else if (potVal <= 40 && potVal > 30){
  //BLUE BACK
  backBlue();
  }
}


