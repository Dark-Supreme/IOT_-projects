#include<SoftwareSerial.h>
#include <avr/sleep.h>
#include <TimerOne.h>
#include <RTClib.h>
#include <Wire.h>
RTC_DS3231 rtc;
/* Create object named bt of the class SoftwareSerial */ 
SoftwareSerial bt(3,4); /* (Rx,Tx) */  
int red_light_pin= 5;
int green_light_pin= 6;
int blue_light_pin= 11; 
//const int led = 13;
String temp="",rid="",rec2="",temper="";
char rec;
volatile int p = 0,tim=0,ter = 0;
int snh=0,snm=0,sfh=0,sfm=0,d=0,prev = 1;
DateTime now;
int del[6]= {25,50,100,150,250,300};
int idel[6] = {30,60,100,140,190,255};
int count=0,ad = 1,t=1,tep;
int i[6] = {0,50,120,180,255},j,p1c=0,rval=0,gval=0,bval=0;

void setup() {
  Timer1.initialize(10000000); //10 second timer interrupt
  Timer1.attachInterrupt(tog);
  bt.begin(9600); /* Define baud rate for software serial communication */
  //Serial.begin(9600); /* Define baud rate for serial communication */
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
  //pinMode(led, OUTPUT);
  Wire.begin();
  rtc.begin();
  //Serial.begin(115200);
  attachInterrupt(1, toggle, RISING);
}

void RGB_color(int rv, int gv, int bv)
 {
  analogWrite(red_light_pin, rv);
  analogWrite(green_light_pin, gv);
  analogWrite(blue_light_pin, bv);
}

void loop() {
if (ter==1) /* If data is available on serial port */
    {
     //ter=0;
     temp = bt.readString();
     rec = temp[0];
     rec2 = temp.substring(0,2);
     if(rec2 == "p0"){
          p=0;
      }
      else if(rec2 == "p1"){
          if(p==1 && p1c!=6){
            p1c+=1;
          }
          else if(p ==1 && p1c==6){
            p1c=0; 
          }
          else{
          p=1;
          prev = p;
          }
      }
      else if(rec2 == "p2"){
          if(p == 2 && p1c!=6){
            p1c+=1;
          }
          else if(p ==2 && p1c==6){
            p1c=0; 
          }
          else{
          p=2;
          prev = p;
          }
      }
      else if(rec2 == "p3"){
          if(p == 3 && p1c!=6){
            p1c+=1;
          }
          else if(p ==3 && p1c==6){
            p1c=0; 
          }
          else{
          p=3;
          prev = p;
          }
      }
      else if(rec2 == "p4"){
          if(p == 4 && p1c!=6){
            p1c+=1;
          }
          else if(p ==4 && p1c==6){
            p1c=0; 
          }
          else{
          p=4;
          prev = p;
          }
      }
      else if(rec2 == "p5"){
          if(p == 5 && p1c!=6){
            p1c+=1;
          }
          else if(p ==5 && p1c==6){
            p1c=0; 
          }
          else{
          p=5;
          prev = p;
          }
      }
      else if(rec2 == "c1"){
          p=100;
          prev = p;
          rval = (temp.substring(2,5)).toInt();
          gval = (temp.substring(6,9)).toInt();
          bval = (temp.substring(10,13)).toInt();
      }
      else if(rec2 == "c2"){
          p=200;
          prev = p;
          temper = temp.substring(2,13);
          if(temper == "255,000,000"){
            p1c = 0;
          }
          else if(temper == "000,255,000"){
            p1c = 1;
          }
          else if(temper == "000,000,255"){
            p1c = 2;
          }
          else if(temper == "255,255,000"){
            p1c = 3;
          }
          else if(temper == "000,255,255"){
            p1c = 4;
          }
          else if(temper == "255,000,255"){
            p1c = 5;
          }
          else if(temper == "255,255,255"){
            p1c = 6;
          }
      }
      else if(rec2 == "z0"){
          d=0;
      }
      else if(rec2 == "z1"){
          d=1;
      }
      else if(rec2 == "z2"){
          d=2;
      }
      else if(rec2 == "z3"){
          d=3;
      }
      else if(rec2 == "z4"){
          d=4;
      }
      else if(rec2 == "z5"){
          d=5;
      }
      else if(rec2 == "y0"){
          d=0;
      }
      else if(rec2 == "y1"){
          d=1;
      }
      else if(rec2 == "y2"){
          d=2;
      }
      else if(rec2 == "y3"){
          d=3;
      }
      else if(rec2 == "y4"){
          d=4;
      }
      else if(rec2 == "y5"){
          d=5;
      }

      else if(rec == 'so'){
        snh = (temp.substring(2,4)).toInt();
        snm = (temp.substring(5,7)).toInt();
      }
      else if(rec == 'to'){
        snh = 0;
        snm = 0;
      }
      else if(rec == 'sf'){
        sfh = (temp.substring(2,4)).toInt();
        sfm = (temp.substring(5,7)).toInt();
      }
      else if(rec == 'tf'){
        sfh = 0;
        sfm = 0;
      }
      else if(rec == 'p'){
         p = prev;
      }
      ter=0;
    }
if(p==0){
    RGB_color(0,0,0);
    while(p==0 && ter == 0){
      if(tim == 1){
        now = rtc.now();
        if(now.hour() == snh && now.minute()== snm){
          p = prev;
        }
        tim = 0;
      }
    }
  }

  else if(p==1){
    //RGB_color(255);
    tep = d;
    RGB_color(idel[d],idel[d],idel[d]);
    while(p==1 && ter == 0){
      if(tep!=d){
        if(p1c == 0){
        RGB_color(idel[d],0,0);
        }
        else if(p1c == 1){
        RGB_color(0,idel[d],0);
        }
        else if(p1c == 2){
        RGB_color(0,0,idel[d]);
        }
        else if(p1c == 3){
        RGB_color(idel[d],idel[d],0);
        }
        else if(p1c == 4){
        RGB_color(0,idel[d],idel[d]);
        }
        else if(p1c == 5){
        RGB_color(idel[d],0,idel[d]);
        }
        else if(p1c == 6){
        RGB_color(idel[d],idel[d],idel[d]);
        }
        tep = d;
      }
      if(tim == 1){
        now = rtc.now();
        if(now.hour() == sfh && now.minute()== sfm){
          p = 0;
        }
        tim = 0;
      }
    }
  }

  else if(p==2){
    count = 0;
    while(p==2 && ter == 0){
      if(p1c == 0){
      RGB_color(i[count],0,0);
      }
      else if(p1c == 1){
      RGB_color(0,i[count],0);
      }
      else if(p1c == 2){
      RGB_color(0,0,i[count]);
      }
      else if(p1c == 3){
      RGB_color(i[count],i[count],0);
      }
      else if(p1c == 4){
      RGB_color(0,i[count],i[count]);
      }
      else if(p1c == 5){
      RGB_color(i[count],0,i[count]);
      }
      else if(p1c == 6){
      RGB_color(i[count],i[count],i[count]);
      }
      delay(del[d]+50);
      if(count == 5){
        ad = -1;
        count+=ad;
      }
      else if(count == 0){
        ad = 1;
        count+=ad;
      }
      else{
        count+=ad;
        if(tim == 1){
        now = rtc.now();
        if(now.hour() == sfh && now.minute()== sfm){
          p = 0;
        }
        tim = 0;
      }
      }
    }
  }
  else if(p==3){
    count = 0;
    while(p==3 && ter == 0){
      if(p1c == 0){
      RGB_color(i[count],0,0);
      }
      else if(p1c == 1){
      RGB_color(0,i[count],0);
      }
      else if(p1c == 2){
      RGB_color(0,0,i[count]);
      }
      else if(p1c == 3){
      RGB_color(i[count],i[count],0);
      }
      else if(p1c == 4){
      RGB_color(0,i[count],i[count]);
      }
      else if(p1c == 5){
      RGB_color(i[count],0,i[count]);
      }
      else if(p1c == 6){
      RGB_color(i[count],i[count],i[count]);
      }
      delay(del[d]+100);
      if(count == 5){
        count = 0;
      }
      else if(count == 0){
        ad = 1;
        count+=ad;
      }
      else{
        count+=ad;
        if(tim == 1){
        now = rtc.now();
        if(now.hour() == sfh && now.minute()== sfm){
          p = 0;
        }
        tim = 0;
      }
      }
    }
  }

  else if(p==4){
    count = 0;
    while(p==4 && ter == 0){
      if(p1c == 0){
      RGB_color(i[count],0,0);
      }
      else if(p1c == 1){
      RGB_color(0,i[count],0);
      }
      else if(p1c == 2){
      RGB_color(0,0,i[count]);
      }
      else if(p1c == 3){
      RGB_color(i[count],i[count],0);
      }
      else if(p1c == 4){
      RGB_color(0,i[count],i[count]);
      }
      else if(p1c == 5){
      RGB_color(i[count],0,i[count]);
      }
      else if(p1c == 6){
      RGB_color(i[count],i[count],i[count]);
      }
      delay(del[d]+100);
      if(count == 5){
        ad = -1;
        count += ad;
      }
      else if(count == 0){
        count = 5;
      }
      else{
        count+=ad;
        if(tim == 1){
        now = rtc.now();
        if(now.hour() == sfh && now.minute()== sfm){
          p = 0;
        }
        tim = 0;
      }
      }
    }
  }


else if(p==5){
    count = 0;
    while(p==5 && ter == 0){
      if(p1c == 0){
      RGB_color(i[count],0,0);
      delay(del[d]+50);
      RGB_color(0,0,0);
      delay(del[d]+50);
      RGB_color(i[count],0,0);
      delay(del[d]+50);
      RGB_color(0,0,0);
      }
      else if(p1c == 1){
      RGB_color(0,i[count],0);
      delay(del[d]+50);
      RGB_color(0,0,0);
      delay(del[d]+50);
      RGB_color(0,i[count],0);
      delay(del[d]+50);
      RGB_color(0,0,0);
      }
      else if(p1c == 2){
      RGB_color(0,0,i[count]);
      delay(del[d]+50);
      RGB_color(0,0,0);
      delay(del[d]+50);
      RGB_color(0,0,i[count]);
      delay(del[d]+50);
      RGB_color(0,0,0);
      }
      else if(p1c == 3){
      RGB_color(i[count],i[count],0);
      delay(del[d]+50);
      RGB_color(0,0,0);
      delay(del[d]+50);
      RGB_color(i[count],i[count],0);
      delay(del[d]+50);
      RGB_color(0,0,0);
      }
      else if(p1c == 4){
      RGB_color(0,i[count],i[count]);
      delay(del[d]+50);
      RGB_color(0,0,0);
      delay(del[d]+50);
      RGB_color(0,i[count],i[count]);
      delay(del[d]+50);
      RGB_color(0,0,0);
      }
      else if(p1c == 5){
      RGB_color(i[count],0,i[count]);
      delay(del[d]+50);
      RGB_color(0,0,0);
      delay(del[d]+50);
      RGB_color(i[count],0,i[count]);
      delay(del[d]+50);
      RGB_color(0,0,0);
      }
      else if(p1c == 6){
      RGB_color(i[count],i[count],i[count]);
      delay(del[d]+50);
      RGB_color(0,0,0);
      delay(del[d]+50);
      RGB_color(i[count],i[count],i[count]);
      delay(del[d]+50);
      RGB_color(0,0,0);
      }
      delay(del[d]+50);
        if(tim == 1){
        now = rtc.now();
        if(now.hour() == sfh && now.minute()== sfm){
          p = 0;
        }
        tim = 0;
      }
      }
  }
  else if(p==100){
    RGB_color(rval,gval,bval);
    while(p==100 && ter ==0){
      if(tim == 1){
        now = rtc.now();
        if(now.hour() == sfh && now.minute()== sfm){
          p = 0;
        }
        tim = 0;
      }
      delay(10);
  }
  }
  else if(p==200){
    tep = d;
    while(p==200 && ter ==0){
      if(tep!=d){
        if(p1c == 0){
        RGB_color(idel[d],0,0);
        }
        else if(p1c == 1){
        RGB_color(0,idel[d],0);
        }
        else if(p1c == 2){
        RGB_color(0,0,idel[d]);
        }
        else if(p1c == 3){
        RGB_color(idel[d],idel[d],0);
        }
        else if(p1c == 4){
        RGB_color(0,idel[d],idel[d]);
        }
        else if(p1c == 5){
        RGB_color(idel[d],0,idel[d]);
        }
        else if(p1c == 6){
        RGB_color(idel[d],idel[d],idel[d]);
        }
        tep = d;
      }
      if(tim == 1){
        now = rtc.now();
        if(now.hour() == sfh && now.minute()== sfm){
          p = 0;
        }
        tim = 0;
      }
      delay(10);
  }
  }
 
}
  

  
void tog(){
  tim = 1;
}
void toggle() {
  ter = 1;
}
