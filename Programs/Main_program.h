/*
 *******************************
     MEC 441 Senior Desgin
       Control program
     Version 4 May 15, 2015
 *******************************

 ****************************
       Change History
 ****************************
 Version 1 - 5/5/15
 - Created the base version of the program
 Version 2 - 5/6/15
 - Added the curve fit of desired angle to motor run time and voltage
 - Need to adjust the pitchtoangle relation for the max range of motion we want
 Version 3 - 5/7/15
 - Redid the curve fit, did not need a polynomial
 - Separated the potentiometer calibration for each movement
 - Check the program for rounding errors and change delay(); to delaymicros(); if need be
 - Can either:
   a) change the variable type of pitchdiff, rolldiff, yawdiff
   b) add a multiplier when calculating pitchtime, rolltime, yawtime
 Version 4 - 5/15/15
 - Changed "float" variables to "double" variables
 - Changed the run time from milliseconds to microseconds
 - Adjusted voltage to time relations accordingly to account for milliseconds
 ****************************
      End Change History
 ****************************
  
  This program controls the motors with potentiometers
  
*/ 
#include <Adafruit_MotorShield.h>
#include <Wire.h>
const byte pitchPote = 0;
const byte rollPote = 1;
const byte yawPote = 2;

int pitchmod = 1;
int rollmod = 2;
int pitchraw, rollraw, yawraw;
double pitchval, rollval, yawval, yawdiff,rolldiff,pitchdiff;//, prevpitchval, prevrollval, prevyawval ;
long pitchtime,rolltime,yawtime;
byte count = 0;
byte i = 1;
double prevpitchval = 5.01;
double prevrollval = 5.01;
double prevyawval = 5.01;
// Start the motor shield object and the motor
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *pitchMotor = AFMS.getMotor(1);
Adafruit_DCMotor *rollMotor1 = AFMS.getMotor(2);
Adafruit_DCMotor *rollMotor2 = AFMS.getMotor(3);
Adafruit_DCMotor *yawMotor = AFMS.getMotor(4);

void setup() {
AFMS.begin();
Serial.begin(9600);

pitchMotor -> setSpeed(200);
rollMotor1 -> setSpeed(200);
rollMotor2 -> setSpeed(200);

}

void loop() {
 i=0;

  while (i <2){
long pitchtime = pitchpotentiometercalibration(pitchPote, prevpitchval);
long rolltime = rollpotentiometercalibration(rollPote,prevrollval);
long yawtime = yawpotentiometercalibration(yawPote,prevyawval);
Serial.println("pitch diff");
Serial.println(pitchdiff);
Serial.println("roll time");
Serial.println(rolltime);
Serial.println("yaw time");
Serial.println(yawtime);
prevpitchval = pitchval;
prevyawval = yawval;
prevrollval = rollval;


if (yawdiff<0){
yawMotor -> setSpeed(200);
yawMotor->run(BACKWARD);
delayMicroseconds(yawtime);
yawMotor->run(RELEASE);
}
else if (yawdiff>0){
yawMotor -> setSpeed(200);
yawMotor-> run(FORWARD);
delayMicroseconds(yawtime);
yawMotor->run(RELEASE);
}
else if(yawdiff ==0){
count = count +1;
}

if (pitchdiff<0){
pitchMotor -> setSpeed(200);
pitchMotor->run(FORWARD);
delayMicroseconds(pitchtime);
pitchMotor->run(RELEASE);

}
// pitch diff might alwasys be greater than 0
else if (pitchdiff>0){
pitchMotor -> setSpeed(200);
pitchMotor-> run(BACKWARD);
delayMicroseconds(pitchtime);
pitchMotor->run(RELEASE);

}
else if(pitchdiff ==0){
count = count +1;
}

if (rolldiff<0){
rollMotor1 -> setSpeed(200);
rollMotor1->run(FORWARD);
rollMotor2 -> setSpeed(200);
rollMotor2 -> run(BACKWARD);
delayMicroseconds(rolltime);
rollMotor1->run(RELEASE);
rollMotor2 ->run(RELEASE);
}
// pitch diff might alwasys be greater than 0
else if (rolldiff>0){
rollMotor1 -> setSpeed(200);
rollMotor1->run(FORWARD);
rollMotor2 -> setSpeed(200);
rollMotor2 -> run(BACKWARD);
delayMicroseconds(rolltime);
rollMotor1->run(RELEASE);
rollMotor2 ->run(RELEASE);
}
else if(rolldiff ==0){
count = count +1;
}

else if(count >5){
  yawMotor-> setSpeed(0);
  pitchMotor -> setSpeed(0);
  rollMotor1 -> setSpeed(0);
  rollMotor2 -> setSpeed(0);
  i=3;
}

}

}



int pitchpotentiometercalibration(const byte pitchPote, double prevpitchval){
pitchraw = analogRead(pitchPote);
pitchval = pitchraw * 0.0049*1000;
pitchdiff= pitchval-prevpitchval;
pitchtime = 1000*(0.05549*pitchval);

return pitchtime;
return pitchdiff;
return pitchval;
}

int rollpotentiometercalibration(const byte rollPote, double prevrollval){
rollraw = analogRead(rollPote);
rollval = rollraw * 0.0049*1000;
rolldiff = rollval - prevrollval;
rolltime = 1000*(0.24491*rollval);
return rolltime;
return rolldiff;
return rollval;
}

int yawpotentiometercalibration(const byte yawPote, double prevyawval){
yawraw = analogRead(yawPote);
yawval = yawraw * 0.0049*1000;
yawdiff = yawval - prevyawval;
yawtime =1000*(0.24491*yawval);
return yawtime;
return yawdiff;
return yawval;
}
