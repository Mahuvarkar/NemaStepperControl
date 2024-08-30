#ifndef NemaStepperControl_h
#define NemaStepperControl_h

#include "Arduino.h"
#include <Wire.h>

class NemaStepperControl {
  public:
    NemaStepperControl(bool ControlType, int stepPin, int dirPin, int enablePin, int microSteps); 
    void rotate(int distance, bool direction);
	void rotate(int stepAngle, int revolutions, bool direction);
    void enableDriver();
    void disableDriver();
  private:
	bool _ControlType; 
	bool _direction;
	int _StepAngleSelected;
    int _stepPin;
    int _dirPin;
    int _enablePin;
	int _revolutions;
	int _micro_steps;  	// Microsteps as per motor configuration... 
						// 16 for 42HHD4027-01 
						// 4 for Robokit-RKI-1127
	int _leads;			// (in mm) Distance travelled on the lead screw in one rotation.
	int _required_travel;
	double _steps_per_revolutions;// Steps per Revolution for the motor 
	double _steps_for_1mm;
};

#endif
