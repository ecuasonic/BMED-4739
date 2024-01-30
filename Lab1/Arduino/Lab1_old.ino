#include <Arduino.h>
#include "A4988.h"
// using a 200-step motor Nema 17 is also 200 steps/revolution. Make sure to
// recalculate if using gearbox
#define MOTOR_STEPS 200
// configure the pins connected
#define DIR 3
#define STEP 2
A4988 stepper(MOTOR_STEPS, DIR, STEP);
void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  stepper.begin(10,1); // 20 is the rpm, 1 is the microstep(rot/360)*200
}
void loop() {
  if(Serial.available() > 0) {
    float rot = Serial.parseFloat();
    while(Serial.available() > 0){
      Serial.read();
    }
    stepper.rotate(rot);
    delay(1000);
  }
}