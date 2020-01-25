import serial
from vpython import *
a=serial.Serial('com21',9600)
rod=cylinder(color=color.yellow, radius=50,axis=vector(100,100,0),pos=vector(-50,0,0))
while(1):
    rate(20)
    if (a.inWaiting()>0):
        myData=a.readline().decode('ascii')
        distance = float(myData)
        print(distance)
        rod.axis.x=distance

