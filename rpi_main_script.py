#import evdev
from evdev import InputDevice, categorize, ecodes

#import brightlight library for LED module
from brightpi import *

#import serial library
import serial

#initialize pins for LED module
leds = LED_ALL
brightPi = BrightPi()
brightPi.get_led_on_off(leds)
brightPi.set_led_on_off(leds, OFF)

lightOn = 0     #0 - light on    1 - light off
fast = 0    #0 - normal speed   1 - fast speed

#intialize serial
ser = serial.Serial('/dev/ttyACM0', 9600)
instruction = ""

#creates object 'controller' to store the data
controller = InputDevice('/dev/input/event5')

#button code variables
#(event.code, event.value)
aBtn = (304, 1)
bBtn = (305, 1)
xBtn = (307, 1)
yBtn = (308, 1)

#click joystick
leftJoystick = (317, 1)
rightJoystick = (318, 1)

#start and select button
selectBtn = (158, 1)
startBtn = (315, 1)

#LB and RB buttons
leftBumper = (310, 1)
rightBumper = (311, 1)

#cross pad variables
#(event.code, event.value)
crossPadUp = (17, -1)
crossPadDown = (17, 1)
crossPadLeft = (16, -1)
crossPadRight = (16, 1)

#joystick variables
# event.code         min, mid, and max values
leftJoystickX = 0    #0 - min, 32768 - mid, 65535 - max
leftJoystickY = 1    #0 - min, 32768 - mid, 65535 - max
rightJoystickX = 2   #0 - min, 32768 - mid, 65535 - max
rightJoystickY = 5   #0 - min, 32768 - mid, 65535 - max

#trigger variables
leftTrigger = 10        #max - 1023
rightTrigger = 9        #max 1023
#prints out device info at start
#print(controller.capabilities())


#loop and filter by event code and print the mapped label
for event in controller.read_loop():
    prevInstruction = instruction
    #triggers, joysticks, and crosspad
    if event.type == ecodes.EV_ABS:
        #cross pad values
        if (event.code, event.value) == crossPadUp:
            instruction = "Crosspad Up"
        elif (event.code, event.value) == crossPadDown:
            instruction = "Crosspad Down"
        elif (event.code, event.value) == crossPadLeft:
            instruction = "Crosspad Left"
        elif (event.code, event.value) == crossPadRight:
            instruction = "Crosspad Right"
        #trigger values
        elif event.code == leftTrigger:
            print ("Left Trigger: {}".format(event.value)) 
        elif event.code == rightTrigger:
            print ("Right Trigger: {}".format(event.value))
        #joystick values
        elif (event.code == leftJoystickX):
            #print ("Left Joystick X: {}".format(event.value))
            if event.value >= 55000:
                #instruction = "Left Joystick Right"
                instruction = "LJR"
            elif event.value <= 13000:
                #instruction = "Left Joystick Left"
                instruction = "LJL"
            elif (event.value > 13000 and event.value <= 25000) or (event.value < 55000 and event.value >= 45000):
                #instruction = "Stop Rotate"
                instruction = "SR"
        elif (event.code == leftJoystickY):
            #print ("Left Joystick Y: {}".format(event.value))
            if event.value >= 55000:
                #instruction = "Left Joystick Backward"
                instruction = "LJB"
            elif event.value <= 13000:
                #instruction = "Left Joystick Forward"
                instruction = "LJF"
            elif (event.value > 13000 and event.value <= 25000) or (event.value < 55000 and event.value >= 45000):
                #instruction = "Stop Move"
                instruction = "SM"
        elif event.code == rightJoystickX:
            #print ("Right Joystick X: {}".format(event.value))
            #pan right
            if event.value >= 50000:
                #instruction = "Right Joystick Right"
                instruction = "RJR"
            #pan left
            elif event.value <= 20000:
                #instruction = "Right Joystick Left"
                instruction = "RJL"
            elif (event.value > 20000 and event.value <= 25000) or (event.value < 50000 and event.value >= 40000):
                #instruction = "Stop Pan"
                instruction = "SP"
        elif event.code == rightJoystickY:
            #print ("Right Joystick Y: {}".format(event.value))
            #tilt up
            if event.value >= 50000:
                #instruction = "Right Joystick Down"
                instruction = "RJD"
            #tilt down
            elif event.value <= 20000:
                #instruction = "Right Joystick Up"
                instruction = "RJU"
            elif (event.value > 20000 and event.value <= 25000) or (event.value < 50000 and event.value >= 40000):
                #instruction = "Stop Tilt"
                instruction = "ST"
    #button cases
    elif event.type == ecodes.EV_KEY:
        if (event.code, event.value) == aBtn:
            instruction = "A"
        elif (event.code, event.value) == bBtn:
            if fast == 1:
                #instruction = "B Norm"
                instruction = "BN"
                fast = 0
            else:
                #instruction = "B Fast"
                instruction = "BF"
                fast = 1
        elif (event.code, event.value) == xBtn:
            instruction = "X"
        elif (event.code, event.value) == yBtn:
            instruction = "Y"
        elif (event.code, event.value) == leftJoystick:
            instruction = "Left Joystick Clicked"
        elif (event.code, event.value) == rightJoystick:
            instruction = "Right Joystick Clicked"
        elif (event.code, event.value) == selectBtn:
            instruction = "Select"
            if lightOn == 1:
                brightPi.set_led_on_off(leds, OFF)
                lightOn = 0
            else:
                brightPi.set_led_on_off(leds, ON)
                lightOn = 1
        elif (event.code, event.value) == startBtn:
            instruction = "Start"
        elif (event.code, event.value) == leftBumper:
            instruction = "Left Bumper"
        elif (event.code, event.value) == rightBumper:
            instruction = "Right Bumper"
    if prevInstruction != instruction:
        print(instruction)
        instruction_encode = instruction.encode()
        ser.write(instruction_encode)
