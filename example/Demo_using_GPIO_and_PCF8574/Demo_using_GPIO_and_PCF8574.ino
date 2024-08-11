#include <NemaStepperControl.h>

NemaStepperControl stepper1(2, 3, 4);  // Pins for STEP, DIR, and ENABLE
NemaStepperControl stepper2(6, 7, 8);  // Pins for STEP, DIR, and ENABLE

void setup() {
  stepper1.enableDriver();
  stepper1.rotate(200, HIGH);  // Rotate 200 steps in one direction
  delay(1000);
  stepper1.rotate(200, LOW);   // Rotate 200 steps in the other direction
  stepper1.disableDriver();
  
  stepper2.enableDriver();
  stepper2.rotate(0, 10, HIGH);  // Rotate 10 steps in one direction
  delay(1000);
  stepper2.rotate(0, 10, LOW);   // Rotate 10 steps in the other direction
  stepper2.disableDriver();
}

void loop() {
  // Repeat rotation in the loop if needed
}
