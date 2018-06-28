volatile int brightness = 1;         //initializing a integer for incrementing and decrementing duty ratio.
volatile int flow = 1;
void setup() 
{
  // declare pin 3 to be an output:
  pinMode(3, OUTPUT);

  // declare pin 5 to be an output:
  pinMode(5, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() 
{
     analogWrite(3, brightness);
     analogWrite(5, brightness);
     
    if((flow == 1) && (brightness<255))
    {
      brightness++;       
    }

    if((flow == 0) && (brightness>0))
    {
      brightness--;       
    }

    if(brightness == 0)
    {
      flow = 1;
      delay(5000);
    }

    if(brightness == 255)
    {
      flow = 0;
      delay(5000);
    }
    
    delay(20);
}
