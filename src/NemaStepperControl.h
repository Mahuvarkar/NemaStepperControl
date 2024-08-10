#ifndef NemaStepperControl_h
#define NemaStepperControl_h

#include "Arduino.h"

class NemaStepperControl {
  public:
    NemaStepperControl(int stepPin, int dirPin, int enablePin); 
    void rotate(int steps, bool direction);
	void rotate(int stepAngle, int revolutions, bool direction);
    void enableDriver();
    void disableDriver();
  private:
	int _StepAngleSelected;
    int _stepPin;
    int _dirPin;
    int _enablePin;
	int _revolutions;
};

#endif
