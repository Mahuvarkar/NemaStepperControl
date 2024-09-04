/* 
THIS CODE NEEDS TO BE TESTED ON HARDWARE
TO BE TESTED AFTER "Demo_using_GPIO_and_PCF8574_as_Task.ino" 
*/

#include <NemaStepperControl.h>
#include <pcf8574.h>

PCF8574 pcf(0x20);

#define LimitSwitch1 0

TaskHandle_t RunMotor1, CheckLimitSw1;

int distanceToTravel = 50;  // needs to volatile if it is uupdated by multiple tasks as per freeRTOS

NemaStepperControl stepper1(2,  /* Step(Pulse) pin for the driver, has to be strictly on the GPOI of uC */
                            1,  /* To set the Direction Control Type as Internal or External, 0 -> Internal, 1 -> External */
                            3,  /* Direction Control pin for the driver, can be either GPIO or PCF Px pin */
                            1,  /* To set the Enable Control Type as Internal or External, 0 -> Internal, 1 -> External */
                            2,  /* Enable pin for the driver, can be either GPIO or PCF Px pin */
                            16, /* Microstepping */
                            1   /* LeadScrew or Ball Screw, 0 -> LEADSCREW_2_START, 1 -> LEADSCREW_4_START, 2 -> BALLSCREW_8MM */
);

void setup() {
  Serial.begin(115200);

  // pinMode(LimitSwitch1, INPUT_PULLUP);
  pinMode(pcf, LimitSwitch1, INPUT_PULLUP);

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
    1                    /* Core where to run the task */
  );
}

void loop() {
  // Repeat rotation in the loop if needed
  Serial.print("Void Loop runs on Core: ");
  Serial.println(xPortGetCoreID());

  delay(5000);
}
