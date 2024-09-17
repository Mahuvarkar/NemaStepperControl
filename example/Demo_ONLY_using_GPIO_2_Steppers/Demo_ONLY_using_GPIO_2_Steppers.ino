#include <NemaStepperControl.h>

int distance_travel = 50;  // in mm
int StepDelay = 50;

NemaStepperControl stepperz1(2,  /* Step(Pulse) pin for the driver, has to be strictly on the GPOI of uC */
                            0,  /* To set the Direction Control Type as Internal or External, 0 -> Internal, 1 -> External */
                            18, /* Direction Control pin for the driver, can be either GPIO or PCF Px pin */
                            0,  /* To set the Enable Control Type as Internal or External, 0 -> Internal, 1 -> External */
                            15, /* Enable pin for the driver, can be either GPIO or PCF Px pin */
                            16, /* Microstepping */
                            2,  /* LeadScrew Pitch */
                            4   /* Number of Starts on the Screw */
);

NemaStepperControl stepperz2(4,  /* Step(Pulse) pin for the driver, has to be strictly on the GPOI of uC */
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
  stepperz1.enableDriver();
  stepperz2.enableDriver();
  Serial.println("Driver ENABLED");
  delay(1000);
  stepperz1.rotate(distance_travel, HIGH, StepDelay);  // Rotate 50 mm in one direction
  stepperz2.rotate(distance_travel, HIGH, StepDelay);  // Rotate 50 mm in one direction
  delay(5000);
  stepperz1.rotate(distance_travel, LOW, StepDelay);  // Rotate 50 mm in the other direction
  stepperz2.rotate(distance_travel, LOW, StepDelay);  // Rotate 50 mm in the other direction
  stepperz1.disableDriver();
  stepperz2.disableDriver();
  delay(1000);
  Serial.println("Driver DISABLED");
  delay(5000);
}

void loop() {
  // Repeat rotation in the loop if needed
  Serial.print("This Task runs on Core: ");
  Serial.println(xPortGetCoreID());

  stepperz1.enableDriver();
  stepperz2.enableDriver();
  Serial.println("Driver ENABLED");
  delay(1000);
  stepperz1.rotate(distance_travel, HIGH, StepDelay);  // Rotate 50 mm in one direction
  stepperz2.rotate(distance_travel, HIGH, StepDelay);  // Rotate 50 mm in one direction
  delay(5000);
  stepperz1.rotate(distance_travel, LOW, StepDelay);  // Rotate 50 mm in the other direction
  stepperz2.rotate(distance_travel, LOW, StepDelay);  // Rotate 50 mm in the other direction
  stepperz1.disableDriver();
  stepperz2.disableDriver();
  delay(1000);
  Serial.println("Driver DISABLED");
  delay(5000);
}
