#include "Arduino.h"
#include "NemaStepperControl.h"

enum StepAngleSelection {
	StepAngle0, // 1.8deg
	StepAngle1, // 0.18deg
	StepAngle2, // 0.9deg
	StepAngle3, // 3.6deg
	StepAngle4, // 7.5deg
	StepAngle5, // 15deg
};

NemaStepperControl::NemaStepperControl(int stepPin, int dirPin, int enablePin) {
  _stepPin = stepPin;
  _dirPin = dirPin;
  _enablePin = enablePin;

  pinMode(_stepPin, OUTPUT);
  pinMode(_dirPin, OUTPUT);
  pinMode(_enablePin, OUTPUT);
}

void NemaStepperControl::rotate(int steps, bool direction) {
  digitalWrite(_dirPin, direction);
  for (int i = 0; i < steps; i++) {
    digitalWrite(_stepPin, HIGH);
    delayMicroseconds(50);  // Adjust this delay to control speed
    digitalWrite(_stepPin, LOW);
    delayMicroseconds(50);  // Adjust this delay to control speed
  }
}

void NemaStepperControl::rotate(int stepAngle, int revolutions, bool direction) {
	int steps = 0;
  digitalWrite(_dirPin, direction);
  _revolutions = revolutions;
  
  switch (stepAngle) {
	  case StepAngle0:
		_StepAngleSelected = 1.8;
		break;
	  case StepAngle1:
		_StepAngleSelected = 0.18;
		break;
	  case StepAngle2:
		_StepAngleSelected = 0.9;
		break;
	  case StepAngle3:
		_StepAngleSelected = 3.6;
		break;
	  case StepAngle4:
		_StepAngleSelected = 7.5;
		break;
	  case StepAngle5:
		_StepAngleSelected = 15;
		break;
  }
  
  steps = (360 / _StepAngleSelected) * _revolutions;
  for (int i = 0; i < steps; i++) {
    digitalWrite(_stepPin, HIGH);
    delayMicroseconds(50);  // Adjust this delay to control speed
    digitalWrite(_stepPin, LOW);
    delayMicroseconds(50);  // Adjust this delay to control speed
  }
}

void NemaStepperControl::enableDriver() {
  digitalWrite(_enablePin, LOW);  // Assuming LOW enables the driver
}

void NemaStepperControl::disableDriver() {
  digitalWrite(_enablePin, HIGH);  // Assuming HIGH disables the driver
}
