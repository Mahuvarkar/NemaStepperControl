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

NemaStepperControl::NemaStepperControl(int stepPin1, bool DirControlType1, int dirPin1, bool EnControlType1, int enablePin1, int microSteps, int ScrewPitch, int ScrewStart) {
	_DirControlType1 = DirControlType1;
	_EnControlType1 = EnControlType1;
	_stepPin1 = stepPin1;
	_dirPin1 = dirPin1;
	_enablePin1 = enablePin1;
	_micro_steps = microSteps; 
	_ScrewPitch = ScrewPitch;
	_ScrewStart = ScrewStart;
	_leads = (_ScrewPitch * _ScrewStart);
  
	pinMode(_stepPin1, OUTPUT);
	if (_DirControlType1 == InternalControl) {
		pinMode(_dirPin1, OUTPUT);
	} else if (_DirControlType1 == ExternalControl) {
		pinMode(ex0, _dirPin1, OUTPUT);
	}
	if (_EnControlType1 == InternalControl) {
		pinMode(_enablePin1, OUTPUT);
		digitalWrite(_enablePin1, HIGH);
	} else if (_EnControlType1 == ExternalControl) {
		pinMode(ex0, _enablePin1, OUTPUT);
		digitalWrite(ex0, _enablePin1, HIGH);
	}
  
	_steps_per_revolutions = (_micro_steps * 203); 	// refine 203 as per required for fine tuning
													// 203 for 42HHD4027-01
													// 200 for Robokit-RKI-1127
	_steps_for_1mm = (_steps_per_revolutions / _leads);
}

NemaStepperControl::NemaStepperControl(int stepPin1, bool DirControlType1, int dirPin1, bool EnControlType1, int enablePin1, 
											int stepPin2, bool DirControlType2, int dirPin2, bool EnControlType2, int enablePin2, 
											int microSteps, int ScrewPitch, int ScrewStart) {

	_DirControlType1 = DirControlType1;
	_DirControlType2 = DirControlType2;
	_EnControlType1 = EnControlType1;
	_EnControlType2 = EnControlType2;
	
	_stepPin1 = stepPin1;
	_stepPin2 = stepPin2;
	_dirPin1 = dirPin1;
	_dirPin2 = dirPin2;
	_enablePin1 = enablePin1;
	_enablePin2 = enablePin2;
	_micro_steps = microSteps; 
	_ScrewPitch = ScrewPitch;
	_ScrewStart = ScrewStart;
	_leads = (_ScrewPitch * _ScrewStart);
  
	pinMode(_stepPin1, OUTPUT);
	pinMode(_stepPin2, OUTPUT);
	
	if (_DirControlType1 == InternalControl) {
		pinMode(_dirPin1, OUTPUT);
	} else if (_DirControlType1 == ExternalControl) {
		pinMode(ex0, _dirPin1, OUTPUT);
	}
	if (_DirControlType2 == InternalControl) {
		pinMode(_dirPin2, OUTPUT);
	} else if (_DirControlType2 == ExternalControl) {
		pinMode(ex0, _dirPin2, OUTPUT);
	}
	
	if (_EnControlType1 == InternalControl) {
		pinMode(_enablePin1, OUTPUT);
		digitalWrite(_enablePin1, HIGH);
	} else if (_EnControlType1 == ExternalControl) {
		pinMode(ex0, _enablePin1, OUTPUT);
		digitalWrite(ex0, _enablePin1, HIGH);
	}
	if (_EnControlType2 == InternalControl) {
		pinMode(_enablePin2, OUTPUT);
		digitalWrite(_enablePin2, HIGH);
	} else if (_EnControlType2 == ExternalControl) {
		pinMode(ex0, _enablePin2, OUTPUT);
		digitalWrite(ex0, _enablePin2, HIGH);
	}
  
	_steps_per_revolutions = (_micro_steps * 203); 	// refine 203 as per required for fine tuning
													// 203 for 42HHD4027-01
													// 200 for Robokit-RKI-1127
	_steps_for_1mm = (_steps_per_revolutions / _leads);
	
}

void NemaStepperControl::rotate(int distance, bool direction1, int MicroSecDelay) {
	_required_travel = distance;
	_direction1 = direction1;
	_MicroSecDelay = MicroSecDelay;

	if (_DirControlType1 == InternalControl) {
		digitalWrite(_dirPin1, _direction1);
	} else if (_DirControlType1 == ExternalControl) {
		digitalWrite(ex0, _dirPin1, _direction1);
	}
	for (int k = 0; k < _required_travel; k++) {
		for (int i = 0; i < _steps_for_1mm; i++) {
			digitalWrite(_stepPin1, HIGH);
			delayMicroseconds(_MicroSecDelay);  // Adjust this delay to control speed
			digitalWrite(_stepPin1, LOW);
			delayMicroseconds(_MicroSecDelay);  // Adjust this delay to control speed
		}
	}
}

void NemaStepperControl::rotateSimultaneous(int distance, bool direction1, bool direction2, int MicroSecDelay) {
	_required_travel = distance;
	_direction1 = direction1;
	_direction2 = direction2;
	_MicroSecDelay = MicroSecDelay;

	if (_DirControlType1 == InternalControl) {
		digitalWrite(_dirPin1, _direction1);
	} else if (_DirControlType1 == ExternalControl) {
		digitalWrite(ex0, _dirPin1, _direction1);
	}
	if (_DirControlType2 == InternalControl) {
		digitalWrite(_dirPin2, _direction2);
	} else if (_DirControlType2 == ExternalControl) {
		digitalWrite(ex0, _dirPin2, _direction2);
	}
	for (int k = 0; k < _required_travel; k++) {
		for (int i = 0; i < _steps_for_1mm; i++) {
			digitalWrite(_stepPin1, HIGH);
			digitalWrite(_stepPin2, HIGH);
			delayMicroseconds(_MicroSecDelay);  // Adjust this delay to control speed
			digitalWrite(_stepPin1, LOW);
			digitalWrite(_stepPin2, LOW);
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
	if (_EnControlType1 == InternalControl) {
		digitalWrite(_enablePin1, LOW);  // Assuming LOW enables the driver
	} else if (_EnControlType1 == ExternalControl) {
		digitalWrite(ex0, _enablePin1, LOW);  // Assuming LOW enables the driver
	}
}

void NemaStepperControl::enableDriverSimultaneous() {
	if (_EnControlType1 == InternalControl) {
		digitalWrite(_enablePin1, LOW);  // Assuming LOW enables the driver
	} else if (_EnControlType1 == ExternalControl) {
		digitalWrite(ex0, _enablePin1, LOW);  // Assuming LOW enables the driver
	}
	if (_EnControlType2 == InternalControl) {
		digitalWrite(_enablePin2, LOW);  // Assuming LOW enables the driver
	} else if (_EnControlType2 == ExternalControl) {
		digitalWrite(ex0, _enablePin2, LOW);  // Assuming LOW enables the driver
	}
}

void NemaStepperControl::disableDriver() {
	if (_EnControlType1 == InternalControl) {
		digitalWrite(_enablePin1, HIGH);  // Assuming HIGH disables the driver
	} else if (_EnControlType1 == ExternalControl) {
		digitalWrite(ex0, _enablePin1, HIGH);  // Assuming HIGH disables the driver
	}
}

void NemaStepperControl::disableDriverSimultaneous() {
	if (_EnControlType1 == InternalControl) {
		digitalWrite(_enablePin1, HIGH);  // Assuming HIGH disables the driver
	} else if (_EnControlType1 == ExternalControl) {
		digitalWrite(ex0, _enablePin1, HIGH);  // Assuming HIGH disables the driver
	}
	if (_EnControlType2 == InternalControl) {
		digitalWrite(_enablePin2, HIGH);  // Assuming HIGH disables the driver
	} else if (_EnControlType2 == ExternalControl) {
		digitalWrite(ex0, _enablePin2, HIGH);  // Assuming HIGH disables the driver
	}
}