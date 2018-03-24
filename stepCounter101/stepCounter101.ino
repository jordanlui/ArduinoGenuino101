/*
 * This script implements a step counter using the Intel Curie Genuino 101 IMU
 * Based on the demo from here, although error corrections were required:
 * https://www.arduino.cc/en/Tutorial/Genuino101CurieIMUStepCounter
 * 
 * Fixes over the original version
 * This tutorial originally uses the #include "CurieImu.h" command but this can lead to issues.
 * Using #include <CurieIMU.h> is generally better practice
 * Additionally the original script calls for CurieImu objects instead of CurieIMU, which is the naming convention used in the current v2.0.2
 * And finally this newer version uses CurieIMU.begin() instead of the Curie.initialize() function, which seems to throw errors, and expect some int for addressing sensors.
 * 
 */

#include <CurieIMU.h> // More general, accepted method
int lastStepCount = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("Initializing IMU...");
//  CurieIMU.initialize(0); // initialise the IMU
  CurieIMU.begin();
  CurieIMU.setStepDetectionMode(BMI160_STEP_MODE_NORMAL); // set step detection mode to normal
  CurieIMU.setStepCountEnabled(true); // enable step count

  Serial.println("IMU initialisation complete, waiting for events...");
}

void loop() {
  /* we can now check the step count periodically */
  updateStepCount();
  delay(1000);
}

void updateStepCount()
{
  int stepCount = CurieIMU.getStepCount(); // set stepCount to read stepCount from function
  if (stepCount != lastStepCount) { // if stepCount has changed
    Serial.print("Step count: "); Serial.println(stepCount);
    lastStepCount = stepCount;
  }
}
