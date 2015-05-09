/*
 *******************************
     MEC 441 Senior Desgin
       Control program
     Version 1 May 5, 2015
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
float pitchval, rollval, yawval, yawdiff,rolldiff,pitchdiff;//, prevpitchval, prevrollval, prevyawval ;
long pitchtime,rolltime,yawtime;
byte count = 0;
byte i = 1;
 float prevpitchval = 5.01;
float prevrollval = 5.01;
float prevyawval = 5.01;
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
delay(yawtime);
yawMotor->run(RELEASE);
}
else if (yawdiff>0){
yawMotor -> setSpeed(200);
yawMotor-> run(FORWARD);
delay(yawtime);
yawMotor->run(RELEASE);
}
else if(yawdiff ==0){
count = count +1;
}

if (pitchdiff<0){
pitchMotor -> setSpeed(200);
pitchMotor->run(FORWARD);
delay(pitchtime);
pitchMotor->run(RELEASE);

}
// pitch diff might alwasys be greater than 0
else if (pitchdiff>0){
pitchMotor -> setSpeed(200);
pitchMotor-> run(BACKWARD);
delay(pitchtime);
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
delay(rolltime);
rollMotor1->run(RELEASE);
rollMotor2 ->run(RELEASE);
}
// pitch diff might alwasys be greater than 0
else if (rolldiff>0){
rollMotor1 -> setSpeed(200);
rollMotor1->run(FORWARD);
rollMotor2 -> setSpeed(200);
rollMotor2 -> run(BACKWARD);
delay(rolltime);
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



int pitchpotentiometercalibration(const byte pitchPote, float prevpitchval){
pitchraw = analogRead(pitchPote);
pitchval = pitchraw * 0.0049;
pitchdiff= pitchval-prevpitchval;
pitchtime = 1000*(0.05549*pitchval);

return pitchtime;
return pitchdiff;
return pitchval;
}

int rollpotentiometercalibration(const byte rollPote, float prevrollval){
rollraw = analogRead(rollPote);
rollval = rollraw * 0.0049;
rolldiff = rollval - prevrollval;
rolltime = 1000*(0.24491*rollval);
return rolltime;
return rolldiff;
return rollval;
}

int yawpotentiometercalibration(const byte yawPote, float prevyawval){
yawraw = analogRead(yawPote);
yawval = yawraw * 0.0049;
yawdiff = yawval - prevyawval;
yawtime =1000*(0.24491*yawval);
return yawtime;
return yawdiff;
return yawval;
}
