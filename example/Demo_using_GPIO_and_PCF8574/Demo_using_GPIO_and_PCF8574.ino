#include <NemaStepperControl.h>

NemaStepperControl stepper1(2,  /* Step(Pulse) pin for the driver, has to be strictly on the GPOI of uC */
                            1,  /* To set the Direction Control Type as Internal or External, 0 -> Internal, 1 -> External */
                            3,  /* Direction Control pin for the driver, can be either GPIO or PCF Px pin */
                            1,  /* To set the Enable Control Type as Internal or External, 0 -> Internal, 1 -> External */
                            2,  /* Enable pin for the driver, can be either GPIO or PCF Px pin */
                            16, /* Microstepping */
                            2,  /* LeadScrew Pitch */
                            4   /* Number of Starts on the Screw */
);

void setup() {
  Serial.begin(115200);
  stepper1.enableDriver();
  Serial.println("Driver ENABLED 1");
  stepper1.rotate(50, HIGH);  // Rotate 50 mm in one direction
  stepper1.disableDriver();
  Serial.println("Driver DISABLED 1");
  delay(5000);
  stepper1.enableDriver();
  Serial.println("Driver ENABLED 2");
  stepper1.rotate(50, LOW);  // Rotate 50 mm in the other direction
  stepper1.disableDriver();
  Serial.println("Driver DISABLED 2");
  delay(5000);
}

void loop() {
  // Repeat rotation in the loop if needed
  // Serial.print("This Task runs on Core: ");
  // Serial.println(xPortGetCoreID());
  stepper1.enableDriver();
  Serial.println("Driver ENABLED 3");
  stepper1.rotate(50, HIGH);  // Rotate 50 mm in one direction
  stepper1.disableDriver();
  Serial.println("Driver DISABLED 3");
  delay(5000);
  stepper1.enableDriver();
  Serial.println("Driver ENABLED 4");
  stepper1.rotate(50, LOW);  // Rotate 50 mm in the other direction
  stepper1.disableDriver();
  Serial.println("Driver DISABLED 4");
  delay(5000);
}
