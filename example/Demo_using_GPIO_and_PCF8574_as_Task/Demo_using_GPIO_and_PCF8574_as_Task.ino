#include "main.h"

void TaskToRunMotor1(void* parameter) {
  for (;;) {
    Serial.print("TaskToRunMotor1 runs on Core: ");
    Serial.println(xPortGetCoreID());

    stepper1.enableDriver();
    Serial.println("Driver ENABLED 3");
    stepper1.rotate(distanceToTravel, CCW, StepDelay);  // Rotate 50 mm in Counter-Clockwise direction
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    stepper1.disableDriver();
    Serial.println("Driver DISABLED 3");
    vTaskDelay(5000 / portTICK_PERIOD_MS);
    stepper1.enableDriver();
    Serial.println("Driver ENABLED 4");
    stepper1.rotate(distanceToTravel, CW, StepDelay);  // Rotate 50 mm in Clockwise direction
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    stepper1.disableDriver();
    Serial.println("Driver DISABLED 4");
    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);

  xTaskCreatePinnedToCore(
    TaskToRunMotor1, /* Function To Implement the Task */
    "Motor1Task",    /* Name of the Task */
    1000,            /* Stack size in bytes */
    NULL,            /* Task input Parameter */
    1,               /* Priority of the task */
    &RunMotor1,      /* Task Handle */
    0                /* Core where to run the task */
  );
}

void loop() {
  // Repeat rotation in the loop if needed
  // Serial.print("Void Loop runs on Core: ");
  // Serial.println(xPortGetCoreID());

  delay(10);
}
