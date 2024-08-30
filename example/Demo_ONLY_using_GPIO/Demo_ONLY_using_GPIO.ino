#include <NemaStepperControl.h>

NemaStepperControl stepper1(4, 5, 19, 16);  // Pins for STEP, DIR, ENABLE, and MICROSTEPS

void setup() {
  Serial.begin(115200);
  stepper1.enableDriver();
  Serial.println("Driver ENABLED");
  delay(1000);
  stepper1.rotate(10, HIGH);  // Rotate 200 steps in one direction
  delay(5000);
  stepper1.rotate(10, LOW);   // Rotate 200 steps in the other direction
  stepper1.disableDriver();
  delay(1000);
  Serial.println("Driver DISABLED");
  delay(5000);
}

void loop() {
  // Repeat rotation in the loop if needed
  stepper1.enableDriver();
  Serial.println("Driver ENABLED");
  delay(1000);
  stepper1.rotate(50, HIGH);  // Rotate 200 steps in one direction
  delay(5000);
  stepper1.rotate(50, LOW);   // Rotate 200 steps in the other direction
  stepper1.disableDriver();
  delay(1000);
  Serial.println("Driver DISABLED");
  delay(5000);
}
