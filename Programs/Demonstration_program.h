/*
 **************************
   MEC 441 Senior Design
   Presentation Program
     April 30, 2015
 **************************

 **********************
    Change History
 **********************
4/30/15 - Version 1
- Created base version of the program

 ***********************
   End Change History
 ***********************
This is a program so we can demo what we have

*/

#include <Wire.h>;
#include <Adafruit_MotorShield.h>;

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *motorOne = AFMS.getMotor(1);

void setup() {
  // put your setup code here, to run once:
// Begin running the motor shield at default frequency  
 AFMS.begin();
 motorOne-> setSpeed(200);
}

void loop() {

while (byte i=0, i<3, i++){

  motorOne-> run(FORWARD);
  delay(500);
  motorOne-> run(RELEASE);
 
  delay(1000); 
 
 motorOne-> run(BACKWARD);
 delay(500);
 motorOne-> run(RELEASE);
} 
}
