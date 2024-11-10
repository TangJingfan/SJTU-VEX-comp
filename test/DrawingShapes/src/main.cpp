/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Wed Sep 25 2019                                           */
/*    Description:  Drawing Shapes                                            */
/*    This program creates a star made of different colored lines, and then a */
/*    large box with a solid filled color.                                    */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // Creates the red line in the star
  Brain.Screen.setPenColor(red);
  Brain.Screen.drawLine(200, 50, 175, 100);

  // Creates the blue line in the star
  Brain.Screen.setPenColor(blue);
  Brain.Screen.drawLine(200, 50, 225, 100);

  // Creates the green line in the star
  Brain.Screen.setPenColor(green);
  Brain.Screen.drawLine(160, 70, 225, 100);

  // Creates the cyan line in the star
  Brain.Screen.setPenColor(cyan);
  Brain.Screen.drawLine(160, 70, 240, 70);

  // Creates the yellow line in the star
  Brain.Screen.setPenColor(yellow);
  Brain.Screen.drawLine(175, 100, 240, 70);

  // Creates the white box below the star
  Brain.Screen.setFillColor(white);
  Brain.Screen.drawRectangle(125, 110, 150, 110);
}
