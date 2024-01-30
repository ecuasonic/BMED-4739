#include <Arduino.h>
#include "A4988.h"

#define MOTOR_STEPS 200
#define DIR 2
#define STEP 3

A4988 stepper(MOTOR_STEPS, DIR, STEP);

void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  while (Serial.available() > 0) {
    Serial.read(); // clears the serial buffer
  }
  Serial.println();
  stepper.begin(30,1); // 30 is the rpm, 1 is the microstep
  Serial.println("Enter rotation angle in degrees:");
}

void loop() {
  static bool waitingForInput = true;

  if (waitingForInput && Serial.available() > 0) {
    float angle = Serial.parseFloat();
    if (angle != 0) {
      Serial.print("Rotating ");
      Serial.print(angle);
      Serial.println(" Degrees.");
      rotateStepper(angle);
      waitingForInput = false;
    }
  }

  if (!waitingForInput && stepper.getStepsRemaining() == 0) {
    delay(500);
    Serial.println("Enter another rotation angle in degrees:");
    waitingForInput = true;
  }
}

void rotateStepper(int angle) {
  stepper.rotate(angle);
}
