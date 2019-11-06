#import evdev
from evdev import InputDevice, categorize, ecodes

#creates object 'controller' to store the data
controller = InputDevice('/dev/input/event4')

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
print(controller.capabilities())

#loop and filter by event code and print the mapped label
for event in controller.read_loop():
    #triggers, joysticks, and crosspad
    if event.type == ecodes.EV_ABS:
        #cross pad values
        if (event.code, event.value) == crossPadUp:
            print("Crosspad Up")
        elif (event.code, event.value) == crossPadDown:
            print("Crosspad Down")
        elif (event.code, event.value) == crossPadLeft:
            print("Crosspad Left")
        elif (event.code, event.value) == crossPadRight:
            print("Crosspad Right")
        #trigger values
        elif event.code == leftTrigger:
            print "Left Trigger: %s" %event.value
        elif event.code == rightTrigger:
            print "Right Trigger: %s" %event.value
        #joystick values
        elif (event.code == leftJoystickX):
            print "Left Joystick X: %s" %event.value
        elif (event.code == leftJoystickY):
            print "Left Joystick Y: %s" %event.value
        elif event.code == rightJoystickX:
            print "Right Joystick X: %s" %event.value
        elif event.code == rightJoystickY:
            print "Right Joystick Y: %s" %event.value
    #button cases
    elif event.type == ecodes.EV_KEY:
        if (event.code, event.value) == aBtn:
            print("A")
        elif (event.code, event.value) == bBtn:
            print("B")
        elif (event.code, event.value) == xBtn:
            print("X")
        elif (event.code, event.value) == yBtn:
            print("Y")
        elif (event.code, event.value) == leftJoystick:
            print("Left Joystick Clicked")
        elif (event.code, event.value) == rightJoystick:
            print("Right Joystick Clicked")
        elif (event.code, event.value) == selectBtn:
            print("Select")
        elif (event.code, event.value) == startBtn:
            print("Start")
        elif (event.code, event.value) == leftBumper:
            print("Left Bumper")
        elif (event.code, event.value) == rightBumper:
            print("Right Bumper")
