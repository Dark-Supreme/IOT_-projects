#include

int Contrast=15;



LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

Int prox=A0;

Int green=7;

Int red=8;

Int p=0;

void setup()

{

Serial.begin(9600);

Serial.println("LCD test with PWM contrast adjustment");

pinMode(13,OUTPUT);

analogWrite(6,Contrast);


lcd.begin(16, 2);


lcd.print("LCD test!!");

pinMode(prox,INPUT);

pinMode(red,OUTPUT);

pinMode(green,OUTPUT);

}

void loop()

{

p =digitalRead(prox);

if (p==HIGH)

{

digitalWrite(green,HIGH);

digitalWrite(red,LOW);

lcd.print(“SITE 1 is free”);

}

Else

{

digitalWrite(red,HIGH);

digitalWrite(green,LOW);

lcd.print(“SITE 1 is not free”);

}

}
