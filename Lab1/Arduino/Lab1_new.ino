#include <Arduino.h>
#include "A4988.h"

#define MOTOR_STEPS 200
#define DIR 2
#define STEP 3

A4988 stepper(MOTOR_STEPS, DIR, STEP);

void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  while (Serial.available() > 0) {
    Serial.read(); // clears the serial buffer before starting, just in case
  }
  Serial.println();
  stepper.begin(30,1); // 30 is the rpm, 1 is the microstep
  Serial.println("Enter rotation angle in degrees:");
}

void loop() {
  static bool waitingForInput = true;

  // waits for input in general, either directly from serial or through MatLab
  if (waitingForInput && Serial.available() > 0) {
    float angle = Serial.parseFloat();
    // this part will not be seen if using through MatLab
    if (angle != 0) {
      Serial.print("Rotating ");
      Serial.print(angle);
      Serial.println(" Degrees.");
      stepper.rotate(angle);
      waitingForInput = false;
    }
  }

  // waits for the motor to finish, in order to free itself for another input
  if (!waitingForInput && stepper.getStepsRemaining() == 0) {
    delay(500);
    Serial.println("Enter another rotation angle in degrees:");
    waitingForInput = true;
  }
}
