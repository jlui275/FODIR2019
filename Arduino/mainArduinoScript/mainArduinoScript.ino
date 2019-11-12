//Main Arduino Script
#include <Servo.h>

String input;
int potValue;
bool normalSpeed = true;

Servo panServo;
Servo tiltServo;
int panAngle = 90;
int tiltAngle = 90;

void setup(){
  Serial.begin(9600);
  panServo.attach(9);
  tiltServo.attach(10);
  panServo.write(panAngle);
  tiltServo.write(tiltAngle);
}

void loop(){
  
  if(Serial.available()){         //From RPi to Arduino
    input = Serial.readString();  //reading string from serial
  }
  
  //toggle speed 
  if(input == "B" && normalSpeed == true){
    //set speed to fast
  }else if(input == "B" && normalSpeed == false){
    //set speed to normal
  }
  
  //move robot commands
  if(input == "Right Joystick X"){
    potValue = Serial.read() //read potentiometer value for X direction
    //motor commands
  }else if (input == "Right Joystick Y"){
    potValue = Serial.read() //read potentiometer value for Y direction
    //motor commands
  }else if (input == "Left Joystick X"){
    potValue = Serial.read() //read potentiometer value for X direction
    //servo camera mount commands
    if(potValue > 30000){
      panAngle += 5;
      panServo.write(tiltAngle);
    }else if(potValue < 10000){
      panAngle -= 5;
      panServo.write(tiltAngle);
    }
  }else if (input == "Left Joystick Y"){
    potValue = Serial.read() //read potentiometer value for Y direction
    //servo cmaera mount commands
    if(potValue > 30000){
      tiltAngle += 5;
      tiltServo.write(tiltAngle);
    }else if(potValue < 10000){
      tiltAngle -= 5;
      tiltServo.write(tiltAngle);
    }
  } 

}
