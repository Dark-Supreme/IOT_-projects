int sensor=2; //The output of PIR sensor connected to pin 7
int sensor_value; //variable to hold read sensor value
volatile int val = 0;
unsigned long time1 = 0;
unsigned long time2=0;
int time_elapsed_after_stopping;
int time_elapsed_after_starting;
void setup()
{
pinMode(sensor,INPUT); // configuring pin 7 as Input
//digitalWrite(sensor, HIGH);
Serial.begin(9600); // To show output value of sensor in serial monitor
attachInterrupt(0, digitalInterrupt, CHANGE);
delay(10000);
}

void loop()
{
  if(val ==1){
  sensor_value=digitalRead(sensor);
  if(sensor_value){
    time1 = millis();
    time_elapsed_after_starting = time1-time2;
    Serial.println(time_elapsed_after_starting);
    Serial.println("Detection Started");
      
  }
  else{
    Serial.println("Detection Stopped");
    time2 = millis();
    time_elapsed_after_stopping = time2 - time1;
    Serial.println(time_elapsed_after_stopping);
  }

  val = 0;
  }
}

void digitalInterrupt(){
  val = 1;
}
