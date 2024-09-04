#ifndef _MAIN_H_
#define _MAIN_H_

#include <NemaStepperControl.h>

TaskHandle_t RunMotor1;

int distanceToTravel = 50;  // needs to volatile if it is uupdated by multiple tasks as per freeRTOS
bool CCW = HIGH, CW = LOW;

NemaStepperControl stepper1(2,  /* Step(Pulse) pin for the driver, has to be strictly on the GPOI of uC */
                            1,  /* To set the Direction Control Type as Internal or External, 0 -> Internal, 1 -> External */
                            3,  /* Direction Control pin for the driver, can be either GPIO or PCF Px pin */
                            1,  /* To set the Enable Control Type as Internal or External, 0 -> Internal, 1 -> External */
                            2,  /* Enable pin for the driver, can be either GPIO or PCF Px pin */
                            16, /* Microstepping */
                            2,  /* LeadScrew Pitch */
                            4   /* Number of Starts on the Screw */
);

#endif