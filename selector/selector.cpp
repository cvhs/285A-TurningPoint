#include "config/config.h"
#include "selector.h"

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