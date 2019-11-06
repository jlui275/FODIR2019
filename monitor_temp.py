import os

def measure_temp():
        temp = os.popen("vcgencmd measure_temp").readline()
        return (temp.replace("temp=",""))

def convert_fahrenheit(temp):
    temp = temp[:3]
    fahrenheit = (float(temp) * (9/5)) + 32
    return fahrenheit

print(measure_temp())
print "%s'F" %convert_fahrenheit(measure_temp())
