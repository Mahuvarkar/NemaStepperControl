void TaskDefinitions () {
    xTaskCreatePinnedToCore(
    TaskToRunMotor1, /* Function To Implement the Task */
    "Motor1Task",    /* Name of the Task */
    1000,            /* Stack size in bytes */
    NULL,            /* Task input Parameter */
    1,               /* Priority of the task */
    &RunMotor1,      /* Task Handle */
    0                /* Core where to run the task */
  );
  // vTaskSuspend(RunMotor1);

  xTaskCreatePinnedToCore(
    TaskToCheckLimitSw1, /* Function To Implement the Task */
    "CheckLimitSw1Task", /* Name of the Task */
    1000,                /* Stack size in bytes */
    NULL,                /* Task input Parameter */
    1,                   /* Priority of the task */
    &CheckLimitSw1,      /* Task Handle */
    0                    /* Core where to run the task */
  );
}

void TaskToRunMotor1(void* parameter) {
  for (;;) {
    Serial.print("TaskToRunMotor1 runs on Core: ");
    Serial.println(xPortGetCoreID());

    Serial.println("Received Semaphore....");

    stepper1.enableDriver();
    Serial.println("Driver ENABLED");
    // vTaskDelay(1000 / portTICK_PERIOD_MS);
    stepper1.rotate(distanceToTravel, HIGH);  // Rotate 50 mm in one direction
    vTaskDelay(5000 / portTICK_PERIOD_MS);
    // stepper1.rotate(distanceToTravel, LOW);  // Rotate 50 mm in the other direction
    stepper1.disableDriver();
    vTaskDelay(10000 / portTICK_PERIOD_MS);
    Serial.println("Driver DISABLED");
    // vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}

void TaskToCheckLimitSw1(void* parameter) {
  for (;;) {
    // Serial.println("Checking Limit Switches...");
    // if (digitalRead(LimitSwitch1) == LOW) {
    if (!digitalRead(pcf, LimitSwitch1)) {
      Serial.println("Limit Switch pressed... SUSPENDING motor task....");
      vTaskSuspend(RunMotor1);
      Serial.println("SUSPENDED RunMotor Task");
    } 
    // if (digitalRead(LimitSwitch1) == LOW) {
    if (!digitalRead(pcf, LimitSwitch2)) {
      Serial.println("Limit Switch pressed... RESUMING motor task....");
      vTaskResume(RunMotor1);
      Serial.println("RESUMED RunMotor Task");
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}