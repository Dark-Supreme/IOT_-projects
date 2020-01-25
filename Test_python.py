import serial
a=serial.Serial('com21',9600);
while(1==1):
    if(a.inWaiting()>0):
        myData=a.readline()
        print (myData)
        
    
