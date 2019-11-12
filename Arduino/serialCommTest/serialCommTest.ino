//Test Script for Serial Communication

void setup(){
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

String input
void loop(){
  if(Serial.available()){         //From RPi to Arduino
    input = Serial.readString();  //reading string from serial
  }
  if(input == "Blink!"){
    digitalWrite(LED_BUILTIN, HIGH);
  }
  if(input == "Don't Blink!"){
    digitalWrite(LED_BUILTIN, LOW);
  }
}
