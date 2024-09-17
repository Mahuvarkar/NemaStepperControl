#include <NemaStepperControl.h>

#define PHYSICAL_STOP_BUTTON 35
#define DEBUG 1

int distance_travel = 50, limit_switch_debounce = 50;  // in mm
int StepDelay = 50;

bool buttonState = 0;

TaskHandle_t CheckZlimitSw, CheckYlimitSw, CheckXlimitSw, RunMotor1, StopButton_Physical;

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

  pinMode(PHYSICAL_STOP_BUTTON, INPUT);

  xTaskCreatePinnedToCore(
    TaskToRunMotor1, /* Function To Implement the Task */
    "Motor1Task",    /* Name of the Task */
    1000,            /* Stack size in bytes */
    NULL,            /* Task input Parameter */
    1,               /* Priority of the task */
    &RunMotor1,      /* Task Handle */
    1                /* Core where to run the task */
  );

  xTaskCreatePinnedToCore(
    TaskToStopButton,      /* Function To Implement the Task */
    "CheckStopButtonTask", /* Name of the Task */
    1000,                  /* Stack size in bytes */
    NULL,                  /* Task input Parameter */
    8,                     /* Priority of the task */
    &StopButton_Physical,  /* Task Handle */
    0                      /* Core where to run the task */
  );

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

void TaskToRunMotor1(void* parameter) {
  for (;;) {
    Serial.print("TaskToRunMotor1 runs on Core: ");
    Serial.println(xPortGetCoreID());

    steppersZ.enableDriverSimultaneous();
    sendToSerial("Drivers ENABLED");
    delay(1000);
    steppersZ.rotateSimultaneous(distance_travel, HIGH, HIGH, StepDelay);  // Rotate 50 mm both CW
    delay(5000);
    steppersZ.rotateSimultaneous(distance_travel, LOW, LOW, StepDelay);  // Rotate 50 mm both CCW
    steppersZ.disableDriverSimultaneous();
    delay(1000);
    sendToSerial("Drivers DISABLED");

    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}

void TaskToStopButton(void* parameter) {
  for (;;) {
    // sendToSerial("in Switch Task");
    if (!digitalRead(PHYSICAL_STOP_BUTTON)) {
      vTaskDelay(limit_switch_debounce / portTICK_PERIOD_MS);
      if (!digitalRead(PHYSICAL_STOP_BUTTON)) {
        buttonState = !buttonState;
        Serial.print("buttonState: ");
        Serial.println(buttonState);

        if (buttonState == 0) {
          sendToSerial("STOP_BUTTON_PRESSED");
          vTaskSuspend(RunMotor1);
          Serial.println("Drivers DISABLED");
        } else if (buttonState == 1) {
          sendToSerial("START_BUTTON_PRESSED");
          vTaskResume(RunMotor1);
          Serial.println("Drivers ENABLED");
        }
      }
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void loop() {
  // Serial.print("This Task runs on Core: ");
  // Serial.println(xPortGetCoreID());

  delay(5000);
}

void sendToSerial(String message) {
  if (DEBUG) {
    Serial.print("DEBUG>>");
    Serial.println(message);
  }
}
