#include "Arduino.h"
#include "NemaStepperControl.h"

#include <pcf8574.h>

/*
addresses available for PCF are between 0x20 and 0x27
A0 A1 A2 -> Address
0  0  0  -> 0x20
0  0  1  -> 0x21
0  1  0  -> 0x22
0  1  1  -> 0x23
1  0  0  -> 0x24
1  0  1  -> 0x25
1  1  0  -> 0x26
1  1  1  -> 0x27
*/

PCF8574 ex0(0x20);
// PCF8574 ex1(0x21);
// PCF8574 ex2(0x22);
// PCF8574 ex3(0x23);
// PCF8574 ex4(0x24);
// PCF8574 ex5(0x25);
// PCF8574 ex6(0x26);
// PCF8574 ex7(0x27);

enum StepAngleSelection {
	StepAngle0, // 1.8deg
	StepAngle1, // 0.18deg
	StepAngle2, // 0.9deg
	StepAngle3, // 3.6deg
	StepAngle4, // 7.5deg
	StepAngle5, // 15deg
};

enum InternalOrExternalControl {
	InternalControl,
	ExternalControl,
};

enum ScrewTypeSelection {
	LEADSCREW_2_START,
	LEADSCREW_4_START,
	BALLSCREW_8MM
};

NemaStepperControl::NemaStepperControl(int stepPin, bool DirControlType, int dirPin, bool EnControlType, int enablePin, int microSteps, int ScrewPitch, int ScrewStart) {
	_DirControlType = DirControlType;
	_EnControlType = EnControlType;
	_stepPin = stepPin;
	_dirPin = dirPin;
	_enablePin = enablePin;
	_micro_steps = microSteps; 
	_ScrewPitch = ScrewPitch;
	_ScrewStart = ScrewStart;
	_leads = (_ScrewPitch * _ScrewStart);
  
	pinMode(_stepPin, OUTPUT);
	if (_DirControlType == InternalControl) {
		pinMode(_dirPin, OUTPUT);
	} else if (_DirControlType == ExternalControl) {
		pinMode(ex0, _dirPin, OUTPUT);
	}
	if (_EnControlType == InternalControl) {
		pinMode(_enablePin, OUTPUT);
		digitalWrite(_enablePin, HIGH);
	} else if (_EnControlType == ExternalControl) {
		pinMode(ex0, _enablePin, OUTPUT);
		digitalWrite(ex0, _enablePin, HIGH);
	}
  
	_steps_per_revolutions = (_micro_steps * 203); 	// refine 203 as per required for fine tuning
													// 203 for 42HHD4027-01
													// 200 for Robokit-RKI-1127
	_steps_for_1mm = (_steps_per_revolutions / _leads);
}

void NemaStepperControl::rotate(int distance, bool direction, int MicroSecDelay) {
	_required_travel = distance;
	_direction = direction;
	_MicroSecDelay = MicroSecDelay;

	if (_DirControlType == InternalControl) {
		digitalWrite(_dirPin, _direction);
	} else if (_DirControlType == ExternalControl) {
		digitalWrite(ex0, _dirPin, _direction);
	}
	for (int k = 0; k < _required_travel; k++) {
		for (int i = 0; i < _steps_for_1mm; i++) {
			digitalWrite(_stepPin, HIGH);
			delayMicroseconds(_MicroSecDelay);  // Adjust this delay to control speed
			digitalWrite(_stepPin, LOW);
			delayMicroseconds(_MicroSecDelay);  // Adjust this delay to control speed
		}
	}
}

/*void NemaStepperControl::rotate(int stepAngle, int revolutions, bool direction) {
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
}*/

void NemaStepperControl::enableDriver() {
	if (_EnControlType == InternalControl) {
		digitalWrite(_enablePin, LOW);  // Assuming LOW enables the driver
	} else if (_EnControlType == ExternalControl) {
		digitalWrite(ex0, _enablePin, LOW);  // Assuming LOW enables the driver
	}
}

void NemaStepperControl::disableDriver() {
	if (_EnControlType == InternalControl) {
		digitalWrite(_enablePin, HIGH);  // Assuming HIGH disables the driver
	} else if (_EnControlType == ExternalControl) {
		digitalWrite(ex0, _enablePin, HIGH);  // Assuming HIGH disables the driver
	}
}
