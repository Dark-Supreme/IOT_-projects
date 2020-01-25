

int led = 13;

int Gassensor_analog = A0;

int Gassensor_digital = 5;

int output = 7;



void setup() 

{
   pinMode(led,OUTPUT);

   Serial.begin(9600);
}



void loop() {


  int sensorValue_analog = analogRead(Gassensor_analog);

  Serial.println(sensorValue_analog);

  if(sensorValue_analog>=150)
  {
    digitalWrite(output,1);
    delay(1000);
  }
  else
  {
    digitalWrite(output,0);
  }
  

  

  int sensorValue_digital = digitalRead(Gassensor_digital);
  Serial.println(sensorValue_digital);

  delay(1000);

 
  

 

}
