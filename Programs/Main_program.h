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
 ****************************
      End Change History
 ****************************
  
  This program controls the motors with potentiometers
  
*/ 
#include <Adafruit_MotorShield.h>
#include <Wire.h>
const byte pitchPote = 0;
const byte rollPote = 1;
const byte yawPote = 3;

int pitchmod = 1;
int rollmod = 2;
int pitchraw, rollraw, yawraw;
float pitchval, rollval, yawval ;
long pitchtoangle,rolltoangle,yawtoangle;

// Start the motor shield object and the motor
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *pitchMotor = AFMS.getMotor(1);
Adafruit_DCMotor *rollMotor = AFMS.getMotor(2);
Adafruit_DCMotor *yawMotor = AFMS.getMotor(3);

void setup() {
AFMS.begin();
Serial.begin(115200);

pitchMotor -> setSpeed(200);
rollMotor -> setSpeed(200);
yawMotor -> setSpeed(200);
}

void loop() {
long pitchtime = potentiometercalibration(pitchPote, 0, 0);
long rolltime = potentiometercalibration(0,rollPote,0);
long yawtime = potentiometercalibration(0,0, yawPote);



}

int potentiometercalibration(const byte pitchPote,const byte rollPote,const byte yawPote){
pitchraw = analogRead(pitchPote);
rollraw = analogRead(rollPote);
yawraw = analogRead(yawPote);

pitchval = pitchraw * 0.0049;
rollval = rollraw * 0.0049;
yawval = yawraw * 0.0049;
pitchtoangle = (1.227-0.24491*pitchval)*1000;
rolltoangle = (1.227-0.24491*rollval)*1000;
yawtoangle =(1.227-0.24491*yawval)*1000;
long pitchreturn = pow(-1,-6)*pow(pitchtoangle,3)-pow(6,-6)*pow(pitchtoangle,2)+0.028*pitchtoangle-0.0002; 
long rollreturn = pow(-1,-6)*pow(rolltoangle,3)-pow(6,-6)*pow(rolltoangle,2)+0.028*rolltoangle-0.0002;
long yawreturn = pow(-1,-6)*pow(yawtoangle,3)-pow(6,-6)*pow(yawtoangle,2)+0.028*yawtoangle-0.0002;

Serial.println("pitch conversion to time");
Serial.println(pitchreturn);
Serial.println("roll conversion to time");
Serial.println(rollreturn);
Serial.println("yaw conversion to time");
Serial.println(yawreturn);
return yawreturn;
return rollreturn;
return pitchreturn;
}

