//----------------------------------------------------------------
//-- Basic Otto´s setup
//-- You can add functions, gestures or sounds in loop
//-- https://github.com/OttoDIY
//-- CC BY SA (http://ottodiy.com)
//-----------------------------------------------------------------

#include <Servo.h> 
#include <Oscillator.h>
#include <US.h>
#include <Otto.h>
Otto Otto;  //This is Otto!
//---------------------------------------------------------
//-- First step: Make sure the pins for servos are in the right position
/*
         --------------- 
        |     O   O     |
        |---------------|
YR 3==> |               | <== YL 2
         --------------- 
            ||     ||
RR 5==>   -----   ------  <== RL 4
         |-----   ------|
*/
  #define PIN_YL 2 //servo[2]
  #define PIN_YR 3 //servo[3]
  #define PIN_RL 4 //servo[4]
  #define PIN_RR 5 //servo[5]

  #define INTERVALTIME 10.0 
  #define EEPROM_TRIM false 
  // Activate to take callibration data from internal memory
  #define TRIM_RR 7
  #define TRIM_RL 4
  #define TRIM_YR  4
  #define TRIM_YL -7
  #define N_SERVOS 4
  Oscillator servo[N_SERVOS];

  void goingUp(int tempo);
  void drunk (int tempo);
  void noGravity(int tempo);
  void kickLeft(int tempo);
  void kickRight(int tempo);
  void run(int steps, int T=500);
  void walk(int steps, int T=1000);
  void backyard(int steps, int T=3000);
  void backyardSlow(int steps, int T=5000);
  void turnLeft(int steps, int T=3000);
  void turnRight(int steps, int T=3000);
  void moonWalkLeft(int steps, int T=1000);
  void moonWalkRight(int steps, int T=1000);
  void crusaito(int steps, int T=1000);
  void swing(int steps, int T=1000);
  void upDown(int steps, int T=1000);
  void flapping(int steps, int T=1000);

/*SOUNDS******************
 * S_connection  S_disconnection  S_buttonPushed S_mode1 S_mode2 S_mode3 S_surprise S_OhOoh  S_OhOoh2  S_cuddly 
 * S_sleeping  S_happy S_superHappy S_happy_short S_sad S_confused S_fart1 S_fart2  S_fart3 
 */
/*MOVEMENTS LIST**************
 * dir=1---> FORWARD/LEFT
 * dir=-1---> BACKWARD/RIGTH
 * T : amount of movement. HIGHER VALUE SLOWER MOVEMENT usually 1000 (from 600 to 1400)
 * h: height of mov. around 20
     jump(steps=1, int T = 2000);
     walk(steps, T, dir);
     turn(steps, T, dir);
     bend (steps, T, dir); //usually steps =1, T=2000
     shakeLeg (steps, T, dir);
     updown(steps, T, HEIGHT);
     swing(steps, T, HEIGHT);
     tiptoeSwing(steps, T, HEIGHT);
     jitter(steps, T, HEIGHT); (small T)
     ascendingTurn(steps, T, HEIGHT);
     moonwalker(steps, T, HEIGHT,dir);
     crusaito(steps, T, HEIGHT,dir);
     flapping(steps, T, HEIGHT,dir);
/*GESTURES LIST***************
OttoHappy OttoSuperHappy  OttoSad   OttoSleeping  OttoFart  OttoConfused OttoLove  OttoAngry   
OttoFretful OttoMagic  OttoWave  OttoVictory  OttoFail*/
///////////////////////////////////////////////////////////////////
//-- Global Variables -------------------------------------------//
///////////////////////////////////////////////////////////////////
bool obstacleDetected = false;
int distance = 0;
int program = 0;
// TEMPO: 121 BPM
int t=495;
double pause=0;
///////////////////////////////////////////////////////////////////
//-- Setup ------------------------------------------------------//
///////////////////////////////////////////////////////////////////
void setup(){

  Serial.begin(9600);

  //Let's make it more random
  randomSeed(42); 
  
  checkMode(); // check mode which program to run
  
  if(program == 0) {
    //Set the servo pins
    Otto.init(PIN_YL,PIN_YR,PIN_RL,PIN_RR,true);
    Otto.sing(S_connection); //Otto wake up!
  
    Otto.home();
    delay(50);
  }
  if(program == 1) {
  
    servo[0].attach(PIN_RR);
    servo[1].attach(PIN_RL);
    servo[2].attach(PIN_YR);
    servo[3].attach(PIN_YL);
    
    //EEPROM.write(0,TRIM_RR);
    //EEPROM.write(1,TRIM_RL);
    //EEPROM.write(2,TRIM_YR);
    //EEPROM.write(3,TRIM_YL);
    
    int trim;

    if(EEPROM_TRIM){
      for(int x=0;x<4;x++){
        trim=EEPROM.read(x);
        if(trim>128)trim=trim-256;
        Serial.print("TRIM ");
        Serial.print(x);
        Serial.print(" en ");
        Serial.println(trim);
        servo[x].SetTrim(trim);
      }
    } else{
      servo[0].SetTrim(TRIM_RR);
      servo[1].SetTrim(TRIM_RL);
      servo[2].SetTrim(TRIM_YR);
      servo[3].SetTrim(TRIM_YL);
    }
    
    for(int i=0;i<4;i++) servo[i].SetPosition(90);
  }
}

///////////////////////////////////////////////////////////////////
//-- Principal Loop ---------------------------------------------//
//--Uncomment lines or add you own-------------------------------//
///////////////////////////////////////////////////////////////////
void loop() {
  
   if(program == 0) {
      int randNumber = random(1,19); // generate random number between 1 & 18

      //OBSTACLE MODE ON!!!! 
      obstacleMode();
      
      Otto.home();
      delay(50);
      
      if((randNumber >= 1) && (randNumber < 8))
      {
        Serial.print("2 steps FORWARD\n");
        Otto.walk(2,1000,1); //2 steps FORWARD
      }
      if((randNumber >= 8) && (randNumber < 10))
      {
        Serial.print("2 steps BACKSWARD\n");
        Otto.walk(2,2000,-1); //2 steps BACKSWARD
      }
      if(randNumber == 3)
      {
        Serial.print("2 steps turning RIGHT\n");
        Otto.turn(2,1000,-1);//2 steps turning RIGHT                
      }
      if(randNumber == 4)
      {
        Serial.print("2 steps turning LEFT\n");
        Otto.turn(2,1000,1);//2 steps turning LEFT                
      }
      if(randNumber == 10)
      {
        Serial.print("moonwalker\n");
        Otto.moonwalker(3, 1000, 25, 1);
      }
      if(randNumber == 11)
      {
        Serial.print("bend\n");
        Otto.bend (1, 2000, 1);
      }
      if(randNumber == 12)
      {      
        Serial.print("ascendingTurn\n");
        Otto.ascendingTurn(1, 2000, 22);
      }
      if(randNumber == 13)
      {  
        Serial.print("updown\n");
        Otto.updown(1, 2000, 22);  
      }
      if(randNumber == 14)
      { 
        Serial.print("shakeLeg\n");
        Otto.shakeLeg(1,2000,-1);
        delay(50);
        Otto.shakeLeg(1,2000,1);
      }
      if(randNumber == 15)
      {  
        Serial.print("OttoSuperHappy\n");
        Otto.playGesture(OttoSuperHappy);
      }
      if(randNumber == 16)
      {  
        Serial.print("OttoVictory\n");
        Otto.playGesture(OttoVictory);
      }
      if(randNumber == 17)
      {  
        Serial.print("OttoConfused\n");
        Otto.playGesture(OttoConfused);
      }
      if(randNumber == 18)
      {  
        Serial.print("OttoAngry\n");
        Otto.playGesture(OttoAngry);
      }
   }
   
   if(program == 1) {
      dance();
   }
}

///////////////////////////////////////////////////////////////////
//-- Function to checkmode using sensor obstacles
void checkMode(){
  int i = 0;
  int counter = 0;
  const int trigPin = 8;
  const int echoPin = 9;
  long lduration;
  int ldistance;

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  Serial.print("Selecting mode... \n");
  while(i < 3){
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
  
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
  
    // Reads the echoPin, returns the sound wave travel time in microseconds
    lduration = pulseIn(echoPin, HIGH);
  
    // Calculating the distance
    ldistance = lduration*0.034/2;
    Serial.print("Checking... distance<15\n");
    Serial.print(ldistance);
    Serial.print("\n");
    if(ldistance<15){
      counter++;             
    }
    delay(1000);
    i++;
  }

  if(counter == i){
    program = 1;
    Serial.print("MODE: SMOTH CRIMINAL\n");
    Otto.sing(S_superHappy);   
  } else {
    program = 0;
    Serial.print("MODE: BASIC\n");
    Otto.sing(S_happy); 
  }
  
   delay(50);
}


//-- Function to avoid obstacles
void obstacleMode(){
      int randNumber = random(1,3); // generate random number between 1 & 2
      distance = Otto.getDistance();
      if(distance<15){
        Serial.print("obstacles detected! \n");
        Otto.sing(S_OhOoh2); 
        Serial.print("walk back\n");
        Otto.walk(6,2000,-1);
        if(randNumber == 1){
          Serial.print("turning RIGHT\n");
          Otto.turn(8,1000,-1);//2 steps turning RIGHT    
        }
        else {
          Serial.print("turning LEFT\n");
          Otto.turn(8,1000,1);//2 steps turning LEFT    
        }
      }
}



void dance(){
  primera_parte();
  segunda_parte();
  moonWalkLeft(4,t*2);
  moonWalkRight(4,t*2);
  moonWalkLeft(4,t*2);
  moonWalkRight(4,t*2);
  primera_parte(); 
  crusaito(1,t*8);
  crusaito(1,t*7);

  for (int i=0; i<16; i++){
    flapping(1,t/4);
    delay(3*t/4);
  }
 
  moonWalkRight(4,t*2);
  moonWalkLeft(4,t*2);
  moonWalkRight(4,t*2);
  moonWalkLeft(4,t*2);

  drunk(t*4);
  drunk(t*4);
  drunk(t*4);
  drunk(t*4);
  kickLeft(t);
  kickRight(t);
  drunk(t*8);
  drunk(t*4);
  drunk(t/2);
  delay(t*4); 

  drunk(t/2);

  delay(t*4); 
  walk(2,t*2);
  backyard(2,t*2);
  goingUp(t*2);
  goingUp(t*1);
  noGravity(t*2);
  crusaito(1,t*2);
  crusaito(1,t*8);
  crusaito(1,t*2);
  crusaito(1,t*8);
  crusaito(1,t*2);
  crusaito(1,t*3);

  delay(t);
  primera_parte();
    for (int i=0; i<32; i++){
    flapping(1,t/2);
    delay(t/2);
  }
  
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
}


////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////FUNCIONES DE CONTROL//////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

void oscillate(int A[N_SERVOS], int O[N_SERVOS], int T, double phase_diff[N_SERVOS]){
  for (int i=0; i<4; i++) {
    servo[i].SetO(O[i]);
    servo[i].SetA(A[i]);
    servo[i].SetT(T);
    servo[i].SetPh(phase_diff[i]);
  }
  double ref=millis();
   for (double x=ref; x<T+ref; x=millis()){
     for (int i=0; i<4; i++){
        servo[i].refresh();
     }
  }
}

unsigned long final_time;
unsigned long interval_time;
int oneTime;
int iteration;
float increment[N_SERVOS]; 
int oldPosition[]={90,90,90,90};

void moveNServos(int time, int  newPosition[]){
  for(int i=0;i<N_SERVOS;i++)  increment[i] = ((newPosition[i])-oldPosition[i])/(time/INTERVALTIME);
  
  final_time =  millis() + time; 
  
  iteration = 1; 
  while(millis() < final_time){ //Javi del futuro cambia esto  
      interval_time = millis()+INTERVALTIME;  
      
      oneTime=0;      
      while(millis()<interval_time){    
          if(oneTime<1){ 
              for(int i=0;i<N_SERVOS;i++){
                  servo[i].SetPosition(oldPosition[i] + (iteration * increment[i]));
              }     
              iteration++;
              oneTime++;
          }
      }     
  }   

  for(int i=0;i<N_SERVOS;i++){  
    oldPosition[i] = newPosition[i];
  }   
}


//////////////////////////////////////////////////////////////////////////////
////////////////////////////////PASOS DE BAILE////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void goingUp(int tempo){
  
      pause=millis();
      for(int i=0;i<4;i++) servo[i].SetPosition(90);
      delay(tempo);
      servo[0].SetPosition(80);
      servo[1].SetPosition(100);
      delay(tempo);
      servo[0].SetPosition(70);
      servo[1].SetPosition(110);
      delay(tempo);
      servo[0].SetPosition(60);
      servo[1].SetPosition(120);
      delay(tempo);
      servo[0].SetPosition(50);
      servo[1].SetPosition(130);
      delay(tempo);
      servo[0].SetPosition(40);
      servo[1].SetPosition(140);
      delay(tempo);
      servo[0].SetPosition(30);
      servo[1].SetPosition(150);
      delay(tempo);
      servo[0].SetPosition(20);
      servo[1].SetPosition(160);
      delay(tempo);
      
      while(millis()<pause+8*t);

}

void primera_parte(){
  
  int move1[4] = {60,120,90,90};
  int move2[4] = {90,90,90,90};
  int move3[4] = {40,140,90,90};
  
  for(int x=0; x<3; x++){
    for(int i=0; i<3; i++){
      lateral_fuerte(1,t/2);
      lateral_fuerte(0,t/4);
      lateral_fuerte(1,t/4);
      delay(t);
    }
  
    pause=millis();
    for(int i=0;i<4;i++) servo[i].SetPosition(90);
    moveNServos(t*0.4,move1);
    moveNServos(t*0.4,move2);
    while(millis()<(pause+t*2));
  }
  
  for(int i=0; i<2; i++){
    lateral_fuerte(1,t/2);
    lateral_fuerte(0,t/4);
    lateral_fuerte(1,t/4);
    delay(t);
  }
    
  pause=millis();
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
  crusaito(1,t*1.4);
  moveNServos(t*1,move3);
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
  while(millis()<(pause+t*4));
}

void segunda_parte(){
  
  int move1[4] = {90,90,80,100};
  int move2[4] = {90,90,100,80};
  int move3[4] = {90,90,80,100};
  int move4[4] = {90,90,100,80};
    
  int move5[4] = {40,140,80,100};
  int move6[4] = {40,140,100,80};
  int move7[4] = {90,90,80,100};
  int move8[4] = {90,90,100,80};
       
  int move9[4] = {40,140,80,100};
  int move10[4] = {40,140,100,80};
  int move11[4] = {90,90,80,100};
  int move12[4] = {90,90,100,80};
  
  for(int x=0; x<7; x++){ 
    for(int i=0; i<3; i++){
      pause=millis();
      moveNServos(t*0.15,move1);
      moveNServos(t*0.15,move2);
      moveNServos(t*0.15,move3);
      moveNServos(t*0.15,move4);
      while(millis()<(pause+t));
    }
    pause=millis();
    moveNServos(t*0.15,move5);
    moveNServos(t*0.15,move6);
    moveNServos(t*0.15,move7);
    moveNServos(t*0.15,move8);
    while(millis()<(pause+t));
  }
 
  for(int i=0; i<3; i++){
    pause=millis();
    moveNServos(t*0.15,move9);
    moveNServos(t*0.15,move10);
    moveNServos(t*0.15,move11);
    moveNServos(t*0.15,move12);
    while(millis()<(pause+t));
  }
}

void lateral_fuerte(boolean side, int tempo){
  
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
  if (side) servo[0].SetPosition(40);
  else servo[1].SetPosition(140);
  delay(tempo/2);
  servo[0].SetPosition(90);
  servo[1].SetPosition(90);
  delay(tempo/2);

}

void drunk (int tempo){
  
  pause=millis();
  
  int move1[] = {60,70,90,90};
  int move2[] = {110,120,90,90};
  int move3[] = {60,70,90,90};
  int move4[] = {110,120,90,90};
  
  moveNServos(tempo*0.235,move1);
  moveNServos(tempo*0.235,move2);
  moveNServos(tempo*0.235,move3);
  moveNServos(tempo*0.235,move4);
  while(millis()<(pause+tempo));

}


void noGravity(int tempo){
  
  int move1[4] = {120,140,90,90};
  int move2[4] = {140,140,90,90};
  int move3[4] = {120,140,90,90};
  int move4[4] = {90,90,90,90};
  
  
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
  for(int i=0;i<N_SERVOS;i++) oldPosition[i]=90;
  moveNServos(tempo*2,move1);
  moveNServos(tempo*2,move2);
  delay(tempo*2);
  moveNServos(tempo*2,move3);
  moveNServos(tempo*2,move4);

 

}

void kickLeft(int tempo){
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
  delay(tempo);
  servo[0].SetPosition(50); //pie derecho
  servo[1].SetPosition(70); //pie izquiero
  delay(tempo);
  servo[0].SetPosition(80); //pie derecho
  servo[1].SetPosition(70); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(30); //pie derecho
  servo[1].SetPosition(70); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(80); //pie derecho
  servo[1].SetPosition(70); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(30); //pie derecho
  servo[1].SetPosition(70); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(80); //pie derecho
  servo[1].SetPosition(70); //pie izquiero
  delay(tempo);
}

void kickRight(int tempo){
for(int i=0;i<4;i++) servo[i].SetPosition(90);
  delay(tempo);
  servo[0].SetPosition(110); //pie derecho
  servo[1].SetPosition(130); //pie izquiero
  delay(tempo);
  servo[0].SetPosition(110); //pie derecho
  servo[1].SetPosition(100); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(110); //pie derecho
  servo[1].SetPosition(150); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(110); //pie derecho
  servo[1].SetPosition(80); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(110); //pie derecho
  servo[1].SetPosition(150); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(110); //pie derecho
  servo[1].SetPosition(100); //pie izquiero
  delay(tempo);
}

void walk(int steps, int T){
    int A[4]= {15, 15, 30, 30};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)};
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void run(int steps, int T){
    int A[4]= {10, 10, 10, 10};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void backyard(int steps, int T){
    int A[4]= {15, 15, 30, 30};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(-90), DEG2RAD(-90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void backyardSlow(int steps, int T){
    int A[4]= {15, 15, 30, 30};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(-90), DEG2RAD(-90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}


void turnLeft(int steps, int T){
    int A[4]= {20, 20, 10, 30};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void turnRight(int steps, int T){
    int A[4]= {20, 20, 30, 10};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void moonWalkRight(int steps, int T){
    int A[4]= {25, 25, 0, 0};
    int O[4] = {-15 ,15, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180 + 120), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void moonWalkLeft(int steps, int T){
    int A[4]= {25, 25, 0, 0};
    int O[4] = {-15, 15, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180 - 120), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void crusaito(int steps, int T){
    int A[4]= {25, 25, 30, 30};
    int O[4] = {- 15, 15, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180 + 120), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void swing(int steps, int T){
    int A[4]= {25, 25, 0, 0};
    int O[4] = {-15, 15, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)};
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void upDown(int steps, int T){
    int A[4]= {25, 25, 0, 0};
    int O[4] = {-15, 15, 0, 0};
    double phase_diff[4] = {DEG2RAD(180), DEG2RAD(0), DEG2RAD(270), DEG2RAD(270)};
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void flapping(int steps, int T){
    int A[4]= {15, 15, 8, 8};
    int O[4] = {-A[0], A[1], 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180), DEG2RAD(90), DEG2RAD(-90)};
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void test(int steps, int T){
    int A[4]= {15, 15, 8, 8};
    int O[4] = {-A[0] + 10, A[1] - 10, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180), DEG2RAD(90), DEG2RAD(-90)};
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}
