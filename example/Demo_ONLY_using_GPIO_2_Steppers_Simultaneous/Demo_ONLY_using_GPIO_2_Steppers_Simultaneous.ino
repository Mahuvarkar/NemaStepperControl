#include <NemaStepperControl.h>

#define DEBUG 1

int distance_travel = 50;  // in mm
int StepDelay = 50;

NemaStepperControl steppersZ(2,  /* Step(Pulse) pin for the driver, has to be strictly on the GPOI of uC */
                             0,  /* To set the Direction Control Type as Internal or External, 0 -> Internal, 1 -> External */
                             18, /* Direction Control pin for the driver, can be either GPIO or PCF Px pin */
                             0,  /* To set the Enable Control Type as Internal or External, 0 -> Internal, 1 -> External */
                             15, /* Enable pin for the driver, can be either GPIO or PCF Px pin */
                             4,  /* Step(Pulse) pin for the driver, has to be strictly on the GPOI of uC */
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
  steppersZ.enableDriverSimultaneous();
  sendToSerial("Drivers ENABLED");
  delay(1000);
  steppersZ.rotateSimultaneous(distance_travel, HIGH, LOW, StepDelay);  // Rotate 50 mm in CW and CCW
  delay(5000);
  steppersZ.rotateSimultaneous(distance_travel, LOW, HIGH, StepDelay);  // Rotate 50 mm in CCW and CW
  steppersZ.disableDriverSimultaneous();
  delay(1000);
  sendToSerial("Drivers DISABLED");
  delay(5000);
}

void loop() {
  // Repeat rotation in the loop if needed
  sendToSerial("This Task runs on Core: " + (String)(xPortGetCoreID()));

  steppersZ.enableDriverSimultaneous();
  sendToSerial("Drivers ENABLED");
  delay(1000);
  steppersZ.rotateSimultaneous(distance_travel, HIGH, HIGH, StepDelay);  // Rotate 50 mm both CW
  delay(5000);
  steppersZ.rotateSimultaneous(distance_travel, LOW, LOW, StepDelay);  // Rotate 50 mm both CCW
  steppersZ.disableDriverSimultaneous();
  delay(1000);
  sendToSerial("Drivers DISABLED");

  delay(5000);
}

void sendToSerial(String message) {
  if (DEBUG) {
    Serial.print("DEBUG>>");
    Serial.println(message);
  }
}
