#define Output 4                                               //Assigning pin 4 as output

void setup() 
{
  pinMode(Output, OUTPUT);
  
  
  for (int i = 0; i < 15; i++) 
  {
    if(i != 2)                                                  // interrupt0 is assigned as an input pin while the rest is assigned as output
      pinMode(i, OUTPUT); 
  }
  
  attachInterrupt(0, digitalInterrupt, FALLING);                //falling edge interrupt for waking up at interrupt0
  
  
  //SETUP WATCHDOG TIMER
  WDTCSR = (24);                                                //change enable and WDE - also resets
  WDTCSR = (33);                                                //setting the timer of the interrupt to 8 secs
  WDTCSR |= (1<<6);                                             //enable interrupt mode

  
  // ADCSRA &= ~(1 << 7);                                       // Disable analog to digital converter.

}





void loop() 
{

  digitalWrite(Output, HIGH);
  delay(1000);
  digitalWrite(Output, LOW);
  delay(1000);

  SMCR |= (1 << 2);                                             //power down mode in SMCR register
  SMCR |= 1;                                                    //enables sleep





  //BOD DISABLE 
  MCUCR |= (3 << 5);                                            //set both BODS and BODSE at the same time       //Brown out detection disable
  MCUCR = (MCUCR & ~(1 << 5)) | (1 << 6);                       //set the BODS bit and clear the BODSE bit at the same time
  __asm__  __volatile__("sleep");                               //Inline assembler to switch to sleep mode

  
}

void digitalInterrupt()                                         // Interrupt Service Routine
{

}

ISR(WDT_vect)                                                   // Interrupt Service Routine for Watchdog Timer
{
  
}
