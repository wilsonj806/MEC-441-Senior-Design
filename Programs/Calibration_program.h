/*
 ******************************************
 MEC 441 Senior Design Calibration Program
        April 28, 2015 Version 1
 ******************************************

 ********************************
        Change History
 ********************************
4/28/15 - Version 1 
- Created base version of the program
 ********************************
        End Change History
 ********************************

This program is used to relate the run time of the VEX 2-Wire 393 motors to the
rotational position change

NOTE: This program should be used to test ONE VEX motor at a time.
      If you want to test a different motor, change the number
      in the getMotor function at Line 39 to the desired port (M1-M4)

This is done by having a variety of motor run times and from that,
using a linear approximation, we can relate motor run time to degrees of motion

Components used:
- Motor Shield (x1)
- Motors (x3)

*/

// Include the prequisite libraries required for operation
#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Start variables that will call a motor
Adafruit_DCMotor *motorOne = AFMS.getMotor(1);

void setup(){

// Begin running the motor shield at default frequency  
 AFMS.begin();
 motorOne->setSpeed(200)
}

void loop() {

/*
This loop runs the motors for a set amount of time and then stops
for 10 seconds to give time for the user to mark down the degree of motion
*/
 motorOne-> run(FORWARD);
 delay(50);
 motorOne-> run(RELEASE);
 
 delay(10000); 
 
 motorOne-> run(FORWARD);
 delay(100);
 motorOne-> run(RELEASE);

 delay(10000);
 
 motorOne-> run(FORWARD);
 delay(150);
 motorOne-> run(RELEASE);

 delay(10000);
 
 motorOne-> run(FORWARD);
 delay(200);
 motorOne-> run(RELEASE);

 delay(10000);
 
 motorOne-> run(FORWARD);
 delay(250);
 motorOne-> run(RELEASE);

 delay(10000);
 
 motorOne-> run(FORWARD);
 delay(300);
 motorOne-> run(RELEASE);

 delay(10000);
 
 motorOne-> run(FORWARD);
 delay(350);
 motorOne-> run(RELEASE);

 delay(10000);
 
 motorOne-> run(FORWARD);
 delay(400);
 motorOne-> run(RELEASE);

 delay(10000);
 
 motorOne-> run(FORWARD);
 delay(450);
 motorOne-> run(RELEASE);

 delay(10000);
 
 motorOne-> run(FORWARD);
 delay(500);
 motorOne-> run(RELEASE);

 delay(10000);
}
