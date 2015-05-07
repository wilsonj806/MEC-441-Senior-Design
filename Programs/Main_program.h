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
const byte yawPote = 2;

int pitchmod = 1;
int rollmod = 2;
int pitchraw, rollraw, yawraw;
float prevpitchval = 0;
float prevrollval = 0;
float prevyawval = 0;
float pitchval, rollval, yawval, yawdiff,rolldiff,pitchdiff ;
float pitchtoangle,rolltoangle,yawtoangle;

// Start the motor shield object and the motor
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *pitchMotor = AFMS.getMotor(1);
Adafruit_DCMotor *rollMotor1 = AFMS.getMotor(2);
Adafruit_DCMotor *rollMotor2 = AFMS.getMotor(3);
Adafruit_DCMotor *yawMotor = AFMS.getMotor(4);

void setup() {
AFMS.begin();
//Serial.begin(9600);

pitchMotor -> setSpeed(200);
rollMotor1 -> setSpeed(200);
rollMotor2 -> setSpeed(200);
yawMotor -> setSpeed(200);
}

void loop() {
long pitchtime = potentiometercalibration(pitchPote, 0, 0);
long rolltime = potentiometercalibration(0,rollPote,0);
long yawtime = potentiometercalibration(0,0, yawPote);
//Serial.println("pitch time");
//Serial.println(pitchtime);
//Serial.println("roll time");
//Serial.println(rolltime);
//Serial.println("yaw time");
//Serial.println(yawtime);
//if (pitchdiff <0){
//  pitch
if (yawdiff>0){
yawMotor->run(FORWARD);
delay(yawtime);
yawMotor->run(RELEASE);
}
else if (yawdiff<0){
yawMotor-> run(BACKWARD);
delay(yawtime);
yawMotor->run(RELEASE);
}
}
int potentiometercalibration(const byte pitchPote,const byte rollPote,const byte yawPote){
pitchraw = analogRead(pitchPote);
rollraw = analogRead(rollPote);
yawraw = analogRead(yawPote);

pitchval = pitchraw * 0.0049;
rollval = rollraw * 0.0049;
yawval = yawraw * 0.0049;

pitchdiff= pitchval-prevpitchval;
rolldiff = rollval - prevrollval;
yawdiff = yawval - prevyawval;
pitchtoangle = (1.227-0.24491*pitchval);
rolltoangle = (1.227-0.24491*rollval);
yawtoangle =(1.227-0.24491*yawval);
float pitchreturn = 1000*(pow(-1,-6)*pow(pitchtoangle,3)-pow(6,-6)*pow(pitchtoangle,2)+0.028*pitchtoangle); 
float rollreturn = 1000*(pow(-1,-6)*pow(rolltoangle,3)-pow(6,-6)*pow(rolltoangle,2)+0.028*rolltoangle);
float yawreturn = (pow(-1,-6)*pow(yawtoangle,3)-pow(6,-6)*pow(yawtoangle,2)+0.028*yawtoangle)*1000;

/*Serial.println("pitch raw");
Serial.println(pitchraw);
Serial.println("roll raw");
Serial.println(rollraw);
Serial.println("yaw raw");
Serial.println(yawraw);

Serial.println("pitch convert to val");
Serial.println(pitchtoangle);
Serial.println("roll conversion to val");
Serial.println(rolltoangle);
Serial.println("yaw conversion to val");
Serial.println(yawtoangle);


Serial.println("pitch conversion to time");
Serial.println(pitchreturn);
Serial.println("roll conversion to time");
Serial.println(rollreturn);
Serial.println("yaw conversion to time");
Serial.println(yawreturn);
delay(500);
*/
return yawreturn;
return rollreturn;
return pitchreturn;
return pitchdiff;
return rolldiff;
return yawdiff;
}

