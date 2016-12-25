#include "FastLED.h"

#define NUM_LEDS 50
#define DATA_PIN 6



#define PURPLE (CRGB(25,0,25))
#define GREEN (CRGB(0,25,0))
#define RED (CRGB(25,0,0))
#define YELLOW (CRGB(20,20,0))
#define ORANGE (CRGB(25, 10, 0))
#define DIMRED (CRGB(20,0,0))

//the above is how many ms is a sixteenth note 
// BPM*4 = Sixteenths/min
// (BPM*4)/60000 = sixteenths/millisecond
// 60000/(BPM*4) = ms / sixteenths
// BPM for mad russian - 134
// 111.94, room for error? leap second?

unsigned long startTime;
float SIXTEENTH;

CRGB leds[NUM_LEDS];
CRGB gradient[NUM_LEDS];
CRGB rus[51];
int isOff = 0;


void setup() {
    SIXTEENTH = 111.94;
      
  for(int i=0;i<50;i+=2){
    rus[i] = RED;
    rus[i+1] = DIMRED;
  }
  rus[50] = RED;
	// sanity check delay - allows reprogramming if accidently blowing power w/leds
   	delay(2000);

    FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
    //fill_solid(leds, 50, CRGB(25,0,0));
    
    //Fill gradient array
//    double d;
//    for(int i=0; i<50;i++){
//      d = i/50.0;
//      gradient[i] = CRGB(25*d, 25*d, 25);
//    }
//    memcpy(leds, gradient, NUM_LEDS*sizeof(CRGB));
//
//    
//    FastLED.show();
    delay(100);
}

void blink(int start, int num, CRGB color, unsigned long endTime){ 
  if(!color){
      memcpy(leds+start, gradient+start, num*sizeof(CRGB)); 
      FastLED.show();
     while(millis()-startTime<endTime){}
  }
  else{
    fill_solid(leds+start, num, color);
    FastLED.show();
    while(millis()-startTime<endTime){}
    memcpy(leds+start, gradient+start, num*sizeof(CRGB));
  }
}

void blinkgr(short left, unsigned long endTime){ 
    //assumption: num is even!
    if(left){
      fill_solid(leds, 25, CRGB(25, 0, 0));
      fill_solid(leds+25, 25, CRGB(0, 25, 0));
    }else{
      fill_solid(leds, 25, CRGB(0, 25, 0));
      fill_solid(leds+25, 25, CRGB(25, 0, 0));
    }
    FastLED.show();
    while(millis()-startTime<endTime){}
    memcpy(leds, gradient, 50*sizeof(CRGB));
}

void blinkgr2(short odd, CRGB color, unsigned long endTime){
 
  for(int i=0+odd; i<50; i+=2){
    leds[i] = color;
    leds[(i+1)%50] = CRGB(25,25,25);
  }
  FastLED.show();
  while(millis()-startTime<endTime){}
  memcpy(leds, gradient, 50*sizeof(CRGB));
}
void turnOff(){
  if(!isOff){
    for(int i=0; i<50; i++){
      leds[i] = CRGB(0,0,0);
    }
    FastLED.show();
    isOff=1;
  }
}
unsigned long nextBeat;


void loop() {
//  turnOff();
//  return;
   double d;
   for(int i=0; i<50;i++){
      d = i/50.0;
      gradient[i] = CRGB(25*d, 25*d, 25);
    }
    memcpy(leds, gradient, NUM_LEDS*sizeof(CRGB));
  
  startTime = millis();
  nextBeat = 0;
  
   
    measure1();
    measure2();
    measure3();
    measure4();

    //MEASURES 5-7 ARE SAME AS MEASURES 1-3
    
    measure1();
    measure2();
    measure3();
    
    measure8();
    measure9();
    measure10();
    measure11();measure11();
    measure12();
    measure13();
//    delay(1000);
    //BEGIN RUSSIAN CHRISTMAS
     SIXTEENTH = 107.142857; //speeding up! Also more error D:
    memcpy(gradient, rus, 50*sizeof(CRGB));
 
    measure14();
    measure15();
}


//below code is first pass, can be compactified
void measure1(){

  nextBeat += SIXTEENTH;
  blink(45, 5, PURPLE, nextBeat);

  nextBeat += SIXTEENTH;
  blink(45, 5, 0,nextBeat );

  nextBeat += SIXTEENTH;
  blink(45, 5, PURPLE, nextBeat );

  nextBeat += SIXTEENTH;
  blink(40, 5, PURPLE, nextBeat );
  
  //longer notes
  nextBeat += 2*SIXTEENTH;
  blink(45, 5, PURPLE, nextBeat );

  nextBeat += 2*SIXTEENTH;
  blink(40, 10, PURPLE, nextBeat );

  nextBeat += 2*SIXTEENTH;
  blink(30, 10, PURPLE, nextBeat );

  nextBeat += 2*SIXTEENTH;
  blink(20, 10, PURPLE, nextBeat );

  nextBeat += 2*SIXTEENTH;
  blink(10, 10, PURPLE, nextBeat );

  nextBeat += 2*SIXTEENTH;
  blinkgr(0, nextBeat );
 
}

void measure2(){
  //shorter notes

  nextBeat += SIXTEENTH;
  blink(35, 5, PURPLE, nextBeat);

  nextBeat += SIXTEENTH;
  blink(35, 5, 0,nextBeat );

  nextBeat += SIXTEENTH;
  blink(35, 5, PURPLE, nextBeat );

  nextBeat += SIXTEENTH;
  blink(30, 5, PURPLE, nextBeat );
  
  //longer notes
  nextBeat += 2*SIXTEENTH;
  blink(35, 5, PURPLE, nextBeat );

  nextBeat += 2*SIXTEENTH;
  blink(30, 10, PURPLE, nextBeat );

  nextBeat += 2*SIXTEENTH;
  blink(20, 10, PURPLE, nextBeat );

  nextBeat += 2*SIXTEENTH;
  blink(10, 10, PURPLE, nextBeat );

  nextBeat += 2*SIXTEENTH;
  blink(0, 10, PURPLE, nextBeat );

  nextBeat += 2*SIXTEENTH;
  blinkgr2(1, GREEN, nextBeat );
  
}

void measure3(){

  nextBeat += 2*SIXTEENTH;
  blink(33, 16, YELLOW, nextBeat );
  nextBeat += 2*SIXTEENTH;
  blinkgr2(0, RED, nextBeat);
  nextBeat += 2*SIXTEENTH;
  blink(17, 16, YELLOW, nextBeat );
  nextBeat += 2*SIXTEENTH;
  blinkgr2(1, GREEN, nextBeat);
  nextBeat += 2*SIXTEENTH;
  blink(1, 16, YELLOW, nextBeat );
  nextBeat += 2*SIXTEENTH;
  blinkgr2(0, RED, nextBeat);
  nextBeat += 2*SIXTEENTH;
  blink(17, 16, YELLOW, nextBeat );
  nextBeat += 2*SIXTEENTH;
  blinkgr2(1, GREEN, nextBeat);
}
void measure4(){
  nextBeat += 2*SIXTEENTH;
  blink(33, 16, YELLOW, nextBeat );
  nextBeat += 2*SIXTEENTH;
  blinkgr2(0, RED, nextBeat);
  nextBeat += 2*SIXTEENTH;
  blink(1, 16, YELLOW, nextBeat );
  nextBeat += 2*SIXTEENTH;
  blinkgr2(1, GREEN, nextBeat);
  nextBeat += 2*SIXTEENTH;
  blink(17, 16, YELLOW, nextBeat );
  nextBeat += 2*SIXTEENTH;
  blinkgr(0,  nextBeat);
  nextBeat += 4*SIXTEENTH;
  blinkgr(1, nextBeat);
  

}

void measure8(){
  nextBeat += 2*SIXTEENTH;
  blink(33, 16, GREEN, nextBeat );
   nextBeat += 2*SIXTEENTH;
  blink(33, 16, RED, nextBeat);
  nextBeat += 2*SIXTEENTH;
  blink(17, 16, GREEN, nextBeat );
  nextBeat += 2*SIXTEENTH;
  blink(17, 16, RED, nextBeat);
  nextBeat += 2*SIXTEENTH;
  blink(1, 16, GREEN, nextBeat );
  nextBeat += 2*SIXTEENTH;
  blink(1, 16, RED, nextBeat);
  nextBeat += 2*SIXTEENTH;
  blink(37, 12, GREEN, nextBeat );
  nextBeat += 2*SIXTEENTH;
  blink(37, 12, RED, nextBeat);
  
}

void measure9(){

  nextBeat += 2*SIXTEENTH;
  blink(25, 12, GREEN, nextBeat );
  nextBeat += 2*SIXTEENTH;
  blink(25, 12, RED, nextBeat);
  nextBeat += 2*SIXTEENTH;
  blink(13, 12, GREEN, nextBeat );
  nextBeat += 2*SIXTEENTH;
  blink(13, 12, RED, nextBeat);
  nextBeat += 2*SIXTEENTH;
  blink(1, 12, GREEN, nextBeat );
  nextBeat += 2*SIXTEENTH;
  blink(1, 12, RED, nextBeat);
  nextBeat += 2*SIXTEENTH;
  blink(13, 12, GREEN, nextBeat );
  nextBeat += 2*SIXTEENTH;
  blink(13, 12, RED, nextBeat);
  
}

void measure10(){
  
  nextBeat += 2*SIXTEENTH;
  blink(25, 12, GREEN, nextBeat );
  nextBeat += 2*SIXTEENTH;
  blink(25, 12, RED, nextBeat);
  nextBeat += 2*SIXTEENTH;
  blink(13, 12, GREEN, nextBeat );
  nextBeat += 2*SIXTEENTH;
  blink(13, 12, RED, nextBeat);
  nextBeat += 2*SIXTEENTH;
  blink(1, 12, GREEN, nextBeat );
  nextBeat += 2*SIXTEENTH;
  blink(1, 12, RED, nextBeat);
  nextBeat += 2*SIXTEENTH;
  blink(25, 12, GREEN, nextBeat );
  nextBeat += 2*SIXTEENTH;
  blink(25, 12, RED, nextBeat);
  
}

void measure11(){
  nextBeat += 2*SIXTEENTH;
  blink(13, 12, GREEN, nextBeat );
  nextBeat += 2*SIXTEENTH;
  blink(13, 12, RED, nextBeat);
   nextBeat += 2*SIXTEENTH;
  blink(37, 12, GREEN, nextBeat );
  nextBeat += 2*SIXTEENTH;
  blink(37, 12, RED, nextBeat);
  nextBeat += 2*SIXTEENTH;
  blink(25, 12, GREEN, nextBeat );
  nextBeat += 2*SIXTEENTH;
  blink(25, 12, RED, nextBeat);
   nextBeat += 2*SIXTEENTH;
  blink(1, 12, GREEN, nextBeat );
  nextBeat += 2*SIXTEENTH;
  blink(1, 12, RED, nextBeat);
}
void measure12(){
   for(int i=0;i<2;i++){
      nextBeat += 2*SIXTEENTH;
      blink(25, 12, GREEN, nextBeat );
      nextBeat += 2*SIXTEENTH;
      blink(25, 12, RED, nextBeat);
      nextBeat += 2*SIXTEENTH;
      blink(13, 12, GREEN, nextBeat );
      nextBeat += 2*SIXTEENTH;
      blink(13, 12, RED, nextBeat);
   }
  
}
void measure13(){
  nextBeat += 2*SIXTEENTH;
  blink(25, 12, GREEN, nextBeat );
  nextBeat += 2*SIXTEENTH;
  blink(25, 12, RED, nextBeat);
   nextBeat += 2*SIXTEENTH;
  blink(13, 12, GREEN, nextBeat );
  nextBeat += 2*SIXTEENTH;
  blink(13, 12, RED, nextBeat);
  nextBeat += 2*SIXTEENTH;
  blink(25, 12, GREEN, nextBeat );
  nextBeat += 2*SIXTEENTH;
  blinkgr(1, nextBeat );
  nextBeat+=4*SIXTEENTH;
  blinkgr(0, nextBeat);
}

void measure14(){
  

  byte mod = 0;

    for(int i=0; i<3; i++){
      memcpy(leds, rus+mod, 50*sizeof(CRGB));
      mod = (mod+1)%2;
      
      nextBeat += SIXTEENTH;
      blink(1, 8, YELLOW, nextBeat);
      nextBeat += SIXTEENTH;
      blink(1, 8, CRGB(10,10,0), nextBeat);
    }
    
      memcpy(leds, rus+mod, 50*sizeof(CRGB));
      mod = (mod+1)%2;
    nextBeat += 2*SIXTEENTH;
    blink(9, 8, YELLOW, nextBeat);
  
    for(int i=0; i<3; i++){
      memcpy(leds, rus+mod, 50*sizeof(CRGB));
      mod = (mod+1)%2;
      nextBeat += SIXTEENTH;
      blink(17, 8, YELLOW, nextBeat);
      nextBeat += SIXTEENTH;
      blink(17, 8, CRGB(10,10,0), nextBeat);
    }
    
      memcpy(leds, rus+mod, 50*sizeof(CRGB));
      mod = (mod+1)%2;
    nextBeat += 2*SIXTEENTH;
    blink(25, 8, YELLOW, nextBeat);
  
    
    for(int i=0; i<3; i++){
      memcpy(leds, rus+mod, 50*sizeof(CRGB));
      mod = (mod+1)%2;
      nextBeat += SIXTEENTH;
      blink(33, 8, YELLOW, nextBeat);
      nextBeat += SIXTEENTH;
      blink(33, 8, CRGB(10,10,0), nextBeat);
    
    }
      memcpy(leds, rus+mod, 50*sizeof(CRGB));
      mod = (mod+1)%2;
    nextBeat += 2*SIXTEENTH;
    blink(41, 8, YELLOW, nextBeat);
   
    for(int i=0; i<3; i++){
      memcpy(leds, rus+mod, 50*sizeof(CRGB));
      mod = (mod+1)%2;
      nextBeat += SIXTEENTH;
      blink(33, 8, YELLOW, nextBeat);
      nextBeat += SIXTEENTH;
      blink(33, 8, CRGB(10,10,0), nextBeat);
     
    }
      memcpy(leds, rus+mod, 50*sizeof(CRGB));
      mod = (mod+1)%2;
    nextBeat += 2*SIXTEENTH;
    blink(25, 8, YELLOW, nextBeat);
  
    for(int i=0; i<3; i++){
       memcpy(leds, rus+mod, 50*sizeof(CRGB));
      mod = (mod+1)%2;
      nextBeat += SIXTEENTH;
      blink(17, 8, YELLOW, nextBeat);
      nextBeat += SIXTEENTH;
      blink(17, 8, CRGB(10,10,0), nextBeat);
     
    }
      memcpy(leds, rus+mod, 50*sizeof(CRGB));
      mod = (mod+1)%2;
    nextBeat += 2*SIXTEENTH;
    blink(25, 8, YELLOW, nextBeat);
    
    for(int i=0; i<3; i++){
      memcpy(leds, rus+mod, 50*sizeof(CRGB));
      mod = (mod+1)%2;
      nextBeat += SIXTEENTH;
      blink(17, 8, YELLOW, nextBeat);
      nextBeat += SIXTEENTH;
      blink(17, 8, CRGB(10,10,0), nextBeat);
     
    }
      memcpy(leds, rus+mod, 50*sizeof(CRGB));
      mod = (mod+1)%2;
    nextBeat += 2*SIXTEENTH;
    blink(9, 8, YELLOW, nextBeat);
}
void measure15(){
  byte mod=0;
    for(int i=0; i<3; i++){
      memcpy(leds, rus+mod, 50*sizeof(CRGB));
      mod = (mod+1)%2;
      nextBeat += SIXTEENTH;
      blink(1, 8, YELLOW, nextBeat);
      nextBeat += SIXTEENTH;
      blink(1, 8, CRGB(10,10,0), nextBeat);
     
    }
      memcpy(leds, rus+mod, 50*sizeof(CRGB));
      mod = (mod+1)%2;
    nextBeat += 2*SIXTEENTH;
    blink(9, 8, YELLOW, nextBeat);
  
    for(int i=0; i<3; i++){
      memcpy(leds, rus+mod, 50*sizeof(CRGB));
      mod = (mod+1)%2;
      nextBeat += SIXTEENTH;
      blink(1, 8, YELLOW, nextBeat);
      nextBeat += SIXTEENTH;
      blink(1, 8, CRGB(10,10,0), nextBeat);
     
    }
      memcpy(leds, rus+mod, 50*sizeof(CRGB));
      mod = (mod+1)%2;
    nextBeat += 2*SIXTEENTH;
    blink(9, 8, YELLOW, nextBeat);
  
}


















