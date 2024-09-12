#ifndef NemaStepperControl_h
#define NemaStepperControl_h

#include "Arduino.h"
#include <Wire.h>

class NemaStepperControl {
  public:
    NemaStepperControl(int stepPin, bool DirControlType, int dirPin, bool EnControlType, int enablePin, int microSteps, int ScrewPitch, int ScrewStart); 
    void rotate(int distance, bool direction, int MicroSecDelay);
	//void rotate(int stepAngle, int revolutions, bool direction);
    void enableDriver();
    void disableDriver();
  private:
	bool _DirControlType;
	bool _EnControlType;
	bool _direction;
	int _StepAngleSelected;
    int _stepPin;
    int _dirPin;
    int _enablePin;
	int _revolutions;
	int _micro_steps;  	// Microsteps as per motor configuration... 
						// 16 for 42HHD4027-01 
						// 4 for Robokit-RKI-1127
	int _ScrewPitch;	// pitch of the lead-screw or ball-screw
	int _ScrewStart;    // number of starts on the screw, it can be 1 or 2 or 4 or so on....
	int _leads;			// (in mm) Distance travelled on the lead screw in one rotation.
	int _required_travel;
	int _MicroSecDelay; // delay in microseconds for motor driver pulse
	double _steps_per_revolutions;// Steps per Revolution for the motor 
	double _steps_for_1mm;
};

#endif
