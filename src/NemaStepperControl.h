#ifndef NemaStepperControl_h
#define NemaStepperControl_h

#include "Arduino.h"
#include <Wire.h>

class NemaStepperControl {
  public:
    NemaStepperControl(int stepPin1, bool DirControlType1, int dirPin1, bool EnControlType1, int enablePin1, int microSteps, int ScrewPitch, int ScrewStart); 
	NemaStepperControl(int stepPin1, bool DirControlType1, int dirPin1, bool EnControlType1, int enablePin1, 
					   int stepPin2, bool DirControlType2, int dirPin2, bool EnControlType2, int enablePin2, 
					   int microSteps, int ScrewPitch, int ScrewStart);
    void rotate(int distance, bool direction1, int MicroSecDelay);
	void rotateSimultaneous(int distance, bool direction1, bool direction2, int MicroSecDelay);
	//void rotate(int stepAngle, int revolutions, bool direction);
    void enableDriver();
	void enableDriverSimultaneous();
    void disableDriver();
	void disableDriverSimultaneous();
	
  private:
	bool _DirControlType1, _DirControlType2,
		 _EnControlType1, _EnControlType2,
		 _direction1, _direction2;
	int _StepAngleSelected;
    int _stepPin1, _stepPin2, 
		_dirPin1, _dirPin2, 
		_enablePin1, _enablePin2;
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
