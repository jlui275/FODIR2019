//Main Arduino Script
#include <Stepper.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Adafruit_PWMServoDriver.h>
#include <Servo.h>

String input;
bool normalSpeed = true;
int delayAmt = 100;


Servo panServo;
Servo tiltServo;
int panAngle = 90;
int tiltAngle = 90;


Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_StepperMotor *Motor1 = AFMS.getStepper(200, 1);

Adafruit_StepperMotor *Motor2 = AFMS.getStepper(200, 2);

void setup(){
  Serial.begin(9600);
    AFMS.begin();
    Motor1->setSpeed(30);
    Motor2->setSpeed(30);

  
  panServo.attach(9);
  tiltServo.attach(10);
  panServo.write(panAngle);//starts in middle
  tiltServo.write(tiltAngle);//starts fully upright so the camera is facing forward
}

void loop(){
  
  if(Serial.available()){         //From RPi to Arduino
    input = Serial.readStringUntil('\n');  //reading string from serial
    Serial.println(input);
  }
  
  //toggle speed 
  if(input == "B\n" && normalSpeed == true){//B button press
    delayAmt = 250;//slowing down from normal speed
  }else if(input == "B\n" && normalSpeed == false){
    delayAmt = 100;//speeding up from slowspeed
  }
  
  //move robot commands
  if(input == "LJF"){//move 1 step FW
      Motor1->step(1, FORWARD, SINGLE); 
      Motor2->step(1, BACKWARD, SINGLE); 
      delay(delayAmt);
      
    }else if(input == "LJB"){//move 1 step BW
      Motor2->step(1, FORWARD, SINGLE); 
      Motor1->step(1, BACKWARD, SINGLE);
      delay(delayAmt);
    }else if(input == "LJL"){//Turn 1 step L
      Motor1->step(1, FORWARD, SINGLE); 
      Motor2->step(1, FORWARD, SINGLE);
      delay(delayAmt);
     
    }else if(input == "LJR"){//Turn 1 step R
      Motor1->step(1, BACKWARD, SINGLE); 
      Motor2->step(1, BACKWARD, SINGLE);
      delay(delayAmt);


    }else if((input == "SM\n") || (input == "SR\n")|| (input == "RB\n")){//stop moving FW or BW
      Motor1->release();
      Motor2->release();
      delay(delayAmt);
          
     //pan or tilt camera mount
    }else if (input == "RJL"){//pan left
      //servo camera mount commands 
        panAngle += 3;
        if(panAngle < 0){
          panAngle = 0;
        }else if(panAngle > 180){
          panAngle = 180;
        }
        panServo.write(panAngle);
        Motor1->release();
        Motor2->release();  
        delay(delayAmt);
    }else if (input == "RJR"){//pan right
      //servo camera mount commands
        panAngle -= 3;
        if(panAngle < 0){
          panAngle = 0;
        }else if(panAngle > 180){
          panAngle = 180;
        }
        panServo.write(panAngle);
        Motor1->release();
        Motor2->release();
        delay(delayAmt); 
    }else if (input == "RJU"){//tilt up
        tiltAngle -= 5;
        if(tiltAngle > 180){
          tiltAngle = 180;
        }else if(tiltAngle < 0){
          tiltAngle = 0;
        }
        tiltServo.write(tiltAngle);
        Motor1->release();
        Motor2->release(); 
        delay(delayAmt);
    }else if (input == "RJD"){//tilt down
        tiltAngle += 5;
        if(tiltAngle > 180){
          tiltAngle = 180;
        }else if(tiltAngle < 0){
          tiltAngle = 0;
        }
        tiltServo.write(tiltAngle);
        Motor1->release();
        Motor2->release(); 
        delay(delayAmt);
    }else if (input =="Start"{
      panServo.write(90);
      tiltServo.write(90);
      tiltAngle = 90;
      panAngle = 90;
    }
}
