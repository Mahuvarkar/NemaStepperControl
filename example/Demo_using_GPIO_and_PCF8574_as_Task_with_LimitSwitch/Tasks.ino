void TaskToRunMotor1(void* parameter) {
  for (;;) {
    Serial.print("TaskToRunMotor1 runs on Core: ");
    Serial.println(xPortGetCoreID());

    stepper1.enableDriver();
    Serial.println("Driver ENABLED 3");
    stepper1.rotate(distanceToTravel, CCW, StepDelay);  // Rotate 50 mm in Counter-Clockwise direction
    stepper1.disableDriver();
    Serial.println("Driver DISABLED 3");
    vTaskDelay(5000 / portTICK_PERIOD_MS);
    stepper1.enableDriver();
    Serial.println("Driver ENABLED 4");
    stepper1.rotate(distanceToTravel, CW, StepDelay);  // Rotate 50 mm in Clockwise direction
    stepper1.disableDriver();
    Serial.println("Driver DISABLED 4");
    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}

void TaskToCheckLimitSw1(void* parameter) {
  for (;;) {
    // if (!digitalRead(LimitSwitch1)) {
    if (!digitalRead(pcf, LimitSwitch1)) {
      Serial.println("Limit Switch pressed... suspending motor task....");
      vTaskSuspend(RunMotor1);
      Serial.println("Suspended RunMotor Task");
    // } else {
    //   vTaskResume(RunMotor1);
    }
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}