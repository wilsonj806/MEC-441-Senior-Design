/* MEC 441 Senior Design Program 
   April, 28 2015 Version 1
*/

/* Components called in this program
   -Potentiometers (x3)
   -Motors (x3)
   -Motor Shield (x1)
*/

/* Include the Wire.h byte transmission library and the 
   Adafruit_MotorShield.h motor shield control library
*/
#include <Wire.h>
#include <Adafruit_MotorShield.h>

/* Create the motor shield object with the default I2C address 
   Can stack motor shields but would have to define them with different addressses
*/
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Initialize the pitch, roll, yaw potentiometers that are connected to their respective pins

#define pitchPote = 0;
#define rollPote = 1;
#define yawPote= 2;

/* Initialize variables to store the input from the potentiometer pins
   Potentiometer inputs are from 0-5 volts
*/
float pitchVal, rollVal, yawVal;

/* Initialize a variable to get motor run time from potentiometer volage
   runTime is the final result from this relation and is assumed to be linear
   voltstoseconds converts potentiometer voltage to the number of degrees that a motor moves
   via the time that it takes for the motor to get to that position (WILL NEED CALIBARRATION)
   
   This will be in units of milliseconds probably
*/
float pitchTime, yawTime, rollTime;

/* Initialize a variable that linearly relates voltage to the time it takes for a motor to move
   a certain number of degrees
   
   May need to modify the variable "volt2sec" in each of the pitch/roll/ yaw Time equations to 
   match the degree of motion for each (i.e yawTime = volt2sec/180 ; rollTime = volt2sec/360; etc)
*/
float volt2sec;

// Start variables to call the motors
Adafruit_DCMotor *pitchMotor = AFMS.getMotor(1);
Adafruit_DCMotor *rollMotor = AFMS.getMotor(2);
Adafruit_DCMotor *yawMotor = AFMS.getMotor(3);


void setup() {
 
// Begin running the motor shield at the efault frequency of 1.6kHz
  AFMS.begin();
  
// Initialize the motors at 200 speed  
  pitchMotor-> setSpeed(200);
  rollMotor-> setSpeed(200);
  yawMotor-> setSpeed(200);
}

void loop() {
// Reads the voltage from the potentiometer and converts it from bits to Volts
  pitchVal = analogRead(pitchPote)*0.0049;
  rollVal = analogRead(rollPote)*0.0049;
  yawVal = analogRead(yawPote)*0.049;
  
// Converts volts to a motor run time
  pitchTime = volt2sec * pitchVal;
  yawTime = volt2sec * yawVal;
  rollTime = volt2sec * rollVal;

// Runs the motors
  pitchMotor->run(FORWARD);
  delay(pitchTime);
  pitchMotor->run(RELEASE);

  rollMotor->run(FORWARD);
  delay(rollTime);
  rollMotor->run(RELEASE);

  yawMotor->run(FORWARD);
  delay(yawTime);
  yawMotor->run(RELEASE);
}
