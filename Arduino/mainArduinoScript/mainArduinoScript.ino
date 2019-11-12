//Main Arduino Script

void setup(){
  Serial.begin(9600);
}

String input;
int potValue;
bool normalSpeed = true;

void loop(){
  
  if(Serial.available()){         //From RPi to Arduino
    input = Serial.readString();  //reading string from serial
  }
  
  //toggle speed 
  if(input == "A" && normalSpeed == true){
    //set speed to fast
  }else if(input == "A" && normalSpeed == false){
    //set speed to normal
  }
  
  //move robot
  if(input == "Right Joystick X"){
    potValue = Serial.read() //read potentiometer value for X direction
    //motor commands
  }else if (input == "Right Joystick Y"){
    potValue = Serial.read() //read potentiometer value for Y direction
    //motor commands
  }else if (input == "Left Joystick X"){
    potValue = Serial.read() //read potentiometer value for X direction
    //servo camera mount commands
  }else if (input == "Left Joystick Y"){
    potValue = Serial.read() //read potentiometer value for Y direction
    //servo cmaera mount commands
  } 

}
