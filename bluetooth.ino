#include<SoftwareSerial.h>
#include <avr/sleep.h>

int pwm_output = 11;

int i;

/* Create object named bt of the class SoftwareSerial */ 
SoftwareSerial bt(3,4); /* (Rx,Tx) */  
String temp = "",rid ="";
char ar[10],ai;
volatile int min,hour,p=0;
void setup() {
  bt.begin(9600); /* Define baud rate for software serial communication */
  Serial.begin(9600); /* Define baud rate for serial communication */
  attachInterrupt(1, toggle, RISING);
}
void toggle() {
 p = 1;
}
void loop() {
  if(p==1){
  rid = bt.readString();
  Serial.println(rid);
  Serial.println(rid.substring(0,2));
  p = 0;
  digitalWrite(pwm_output,1);
  digitalWrite(pwm_output,(rid.substring(2,5)).toInt());

  Serial.println(rid.substring(2,5).toInt());


    digitalWrite(pwm_output,(rid.substring(2,5)).toInt());

 led_blink(100);
 p=1;
  
  
}
}




int led_blink(int j)
{
  int i;
  for(i=0;i<255;i+=25)
  {
    digitalWrite(pwm_output,i);
    delay(j);
    Serial.println(i);
  }

    for(i=255;i>-1;i-=25)
  {
    digitalWrite(pwm_output,i);
    delay(j);
    Serial.println(i);
  }
}
