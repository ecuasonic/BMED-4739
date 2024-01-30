#include <Arduino.h>
#include "A4988.h"

// motor steps per revolution
#define MOTOR_STEPS 200
// target rmp for cruise speed
#define RPM 5
// acceleration and deceleration values are always in full steps
#define MOTOR_ACCEL 2000
#define MOTOR_DECEL 1000

#define DIR 2
#define STEP 3

A4988 stepper(MOTOR_STEPS, DIR, STEP);

void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps

  while (Serial.available() > 0) {
    Serial.read(); // clears the serial buffer
  }
  Serial.println();

  stepper.begin(RPM,1); // 25 is the rpm, 1 is the microstep
  Serial.println("Enter rotation angle in degrees:");

  stepper.setSpeedProfile(stepper.LINEAR_SPEED, MOTOR_ACCEL, MOTOR_DECEL);

  Serial.println("START");

  stepper.startRotate(360);
}

void loop() {
  static bool waitingForInput = true;

  if (waitingForInput && Serial.available() > 0) {
    float angle = Serial.parseFloat();
    if (angle != 0) {
      Serial.print("Rotating ");
      Serial.print(angle);
      Serial.println(" Degrees.");

      stepper.getCurrentRPM()
      stepper.getRPM()
      stepper.rotate(angle); // waits for motor to stop spinning
      

      waitingForInput = false;
    }
  }

  if (!waitingForInput && stepper.getStepsRemaining() == 0) {
    delay(500);
    Serial.println("Enter another rotation angle in degrees:");
    waitingForInput = true;
  }
}
