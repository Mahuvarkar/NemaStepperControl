/*
THIS CODE NEEDS TO BE TESTED ON HARDWARE
FIRST TEST THIS CODE THEN GO FOR "Demo_using_GPIO_and_PCF8574_as_Task_with_LimitSwitch.ino" 
*/

#include <NemaStepperControl.h>

TaskHandle_t RunMotor1;

int distanceToTravel = 50;  // needs to volatile if it is uupdated by multiple tasks as per freeRTOS

NemaStepperControl stepper1(2,  /* Step(Pulse) pin for the driver, has to be strictly on the GPOI of uC */
                            1,  /* To set the Direction Control Type as Internal or External, 0 -> Internal, 1 -> External */
                            3,  /* Direction Control pin for the driver, can be either GPIO or PCF Px pin */
                            1,  /* To set the Enable Control Type as Internal or External, 0 -> Internal, 1 -> External */
                            2,  /* Enable pin for the driver, can be either GPIO or PCF Px pin */
                            16, /* Microstepping */
                            1   /* LeadScrew or Ball Screw, 0 -> LEADSCREW_2_START, 1 -> LEADSCREW_4_START, 2 -> BALLSCREW_8MM */
);

void TaskToRunMotor1(void* parameter) {
  for (;;) {
    Serial.print("TaskToRunMotor1 runs on Core: ");
    Serial.println(xPortGetCoreID());

    stepper1.enableDriver();
    Serial.println("Driver ENABLED 3");
    stepper1.rotate(50, HIGH);  // Rotate 50 mm in one direction
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    stepper1.disableDriver();
    Serial.println("Driver DISABLED 3");
    vTaskDelay(5000 / portTICK_PERIOD_MS);
    stepper1.enableDriver();
    Serial.println("Driver ENABLED 4");
    stepper1.rotate(50, LOW);  // Rotate 50 mm in the other direction
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    stepper1.disableDriver();
    Serial.println("Driver DISABLED 4");
    vTaskDelay(5000 / portTICK_PERIOD_MS);

    /*stepper1.enableDriver();
    Serial.println("Driver ENABLED");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    stepper1.rotate(distanceToTravel, HIGH);  // Rotate 50 mm in one direction
    vTaskDelay(5000 / portTICK_PERIOD_MS);
    stepper1.rotate(distanceToTravel, LOW);  // Rotate 50 mm in the other direction
    stepper1.disableDriver();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    Serial.println("Driver DISABLED");
    vTaskDelay(5000 / portTICK_PERIOD_MS);*/
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
