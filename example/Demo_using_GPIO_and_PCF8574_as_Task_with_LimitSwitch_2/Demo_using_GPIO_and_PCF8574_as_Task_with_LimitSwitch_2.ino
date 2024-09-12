#include "main.h"

void setup() {
  Serial.begin(115200);

  // pinMode(LimitSwitch1, INPUT_PULLUP);
  pinMode(pcf, LimitSwitch1, INPUT_PULLUP);
  pinMode(pcf, LimitSwitch2, INPUT_PULLUP);
  TaskDefinitions();
}

void loop() {
  // Repeat rotation in the loop if needed
  Serial.print("Void Loop runs on Core: ");
  Serial.println(xPortGetCoreID());

  delay(5000);
}
