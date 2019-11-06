import serial
import time

ser = serial.Serial('/dev/ttyUSB0', 9600)

string1 = "Blink!"
string1_encode = string1.encode()

string2 = "Don't Blink!"
string2_encode = string2.encode()

while(1):
    ser.write(string1_encode)
    time.sleep(3)
    ser.write(string2_encode)
    time.sleep(3)