# NemaStepperControl
This library allows the microcontroller to use a dedicated GPIO or a PCF8574 io expander module to control the pins required. STEP(Pulse), DIR (direction), and EN(enable/disable driver) of a basic driver (either DRV8825 or similar) connected to a GPIO or a PCF8574.
The PCF8574 library used in the package is written by ***"MSZ98"*** [Github Link](https://github.com/MSZ98/pcf8574) with version **1.0.3**.
Main focus is on getting the libraryto work on ESP32 as task-based option instead of the standard way of practice.

> [!IMPORTANT]
> There os no support for USART as of now.
> This is my first library so if there are any mistakes found by you please let me know.
> Code is being tested on ESP32-Wroom32D and NodeMCU Devkit, with DRV8825 and TMC2209 drivers.

## How to use this lbrary

### Include the library in your code:
Simply add this line at the begining of your code.
```
#include <NemaStepperControl.h>
```

### Initializing the library with the correct parameters

```
NemaStepperControl stepper1(2, 1, 3, 1, 2, 16, 2, 4);
```
There are a total of "8" parameters used to initialize the class and create a object.
1. GPIO connected to the Step(Pulse) pin of the driver
2. Bool value whether the Enable pin is connected to the ESP32 GPIO or the PCF8574 GPIO.
3. GPIO connected to the 
4. Bool value whether the Enable pin is connected to the ESP32 GPIO or the PCF8574 GPIO.
5. GPIO connected to the Enable pin of the driver.
6. Micro-Stepping Selected physically on the driver circuit.
7. Screw Pitch.
8. Number of starts on the Screw.

> [!NOTE]
> Parameters "2." and "4." are to be used to determine the connection as, "0" -> connected to ESP32 GPIO and "1" -> connected to PCF8574 GPIO.
> Parameters "7." and "8." are only useful for you if you are using any type of a lead-screw or ball-screw in your application and need precise distance control on the same. (in mm)

### Enable the Motor Driver
```
stepper1.enableDriver();

```
This will internally pull-down the Enable pin to 0v (GND).

### Disable the Motor Driver
```
stepper1.disableDriver();
```
This will internally pull-up the Enable pin to 5v (or to VIO voltage).

### Rotate to achieve a distance travel
```
stepper1.rotate(distanceToTravel, CCW); 
```
"distanceToTravel" is the target travel distance in a particular direction.
"CCW" is to select the Direction, can be either CCW(HIGH) or CW(LOW).

> [!WARNING]
> function rotate(int* , int* , bool*) is yet to be tested on hardware.