#include <NemaStepperControl.h>

NemaStepperControl stepper1(4,  /* Step(Pulse) pin for the driver, has to be strictly on the GPOI of uC */
                            0,  /* To set the Direction Control Type as Internal or External, 0 -> Internal, 1 -> External */
                            5,  /* Direction Control pin for the driver, can be either GPIO or PCF Px pin */
                            0,  /* To set the Enable Control Type as Internal or External, 0 -> Internal, 1 -> External */
                            19, /* Enable pin for the driver, can be either GPIO or PCF Px pin */
                            16, /* Microstepping */
                            2,  /* LeadScrew Pitch */
                            4   /* Number of Starts on the Screw */
);

void setup() {
  Serial.begin(115200);
  stepper1.enableDriver();
  Serial.println("Driver ENABLED");
  delay(1000);
  stepper1.rotate(10, HIGH);  // Rotate 10 mm in one direction
  delay(5000);
  stepper1.rotate(10, LOW);  // Rotate 10 mm in the other direction
  stepper1.disableDriver();
  delay(1000);
  Serial.println("Driver DISABLED");
  delay(5000);
}

void loop() {
  // Repeat rotation in the loop if needed
  Serial.print("This Task runs on Core: ");
  Serial.println(xPortGetCoreID());

  stepper1.enableDriver();
  Serial.println("Driver ENABLED");
  delay(1000);
  stepper1.rotate(50, HIGH);  // Rotate 10 mm in one direction
  delay(5000);
  stepper1.rotate(50, LOW);  // Rotate 10 mm in the other direction
  stepper1.disableDriver();
  delay(1000);
  Serial.println("Driver DISABLED");
  delay(5000);
}
