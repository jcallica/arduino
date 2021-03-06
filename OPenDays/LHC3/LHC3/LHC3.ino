#include "LPD8806.h"
#include "SPI.h"

// Example to control LPD8806-based RGB LED Modules in a strip

/*****************************************************************************/

// Number of RGB LEDs in strand:
int nLEDs = 32*5; //

// Chose 2 pins for output; can be any valid output pins:
int dataPin  = 2;
int clockPin = 3;
int SPEED = 80;

int LED = 0;

// First parameter is the number of LEDs in the strand.  The LED strips
// are 32 LEDs per meter but you can extend or cut the strip.  Next two
// parameters are SPI data and clock pins:
LPD8806 strip = LPD8806(nLEDs, dataPin, clockPin);

// You can optionally use hardware SPI for faster writes, just leave out
// the data and clock pin parameters.  But this does limit use to very
// specific pins on the Arduino.  For "classic" Arduinos (Uno, Duemilanove,
// etc.), data = pin 11, clock = pin 13.  For Arduino Mega, data = pin 51,
// clock = pin 52.  For 32u4 Breakout Board+ and Teensy, data = pin B2,
// clock = pin B1.  For Leonardo, this can ONLY be done on the ICSP pins.
//LPD8806 strip = LPD8806(nLEDs);

void setup() {
  // Start up the LED strip
  strip.begin();

  // Update the strip, to start they are all 'off'
  strip.show();
}


void loop() {
  int j;


  LED = 0;
  SPEED = 75;
   /// LINAC
   for (j=0; j < 1; j++) { 
  colorChase_segment(strip.Color(50, 0, 50), SPEED,LED,10); // White
  
   }
  LED = LED+10; //10\
  
////////////////////////////////////////////////////////
    // BOOSTER   
      for (j=0; j < 3; j++) { 
  colorChase_segment(strip.Color(60, 0, 30), SPEED,LED,5); // White
  SPEED = SPEED -2;
  
  }
  LED = LED + 5; //15  -50
//////////////////////////////////////////////////////////
  
   for (j=0; j < 1; j++) { 
  colorChase_segment(strip.Color(60, 0, 30 ), SPEED,LED,6); // White
   }
   
   LED = LED + 6;  //21//
   
   // PS
  for (j=0; j < 4; j++) { 
  colorChase_segment(strip.Color(100, 0, 15), SPEED,LED,10); // White
  SPEED = SPEED - 3;
  }
  
  LED = LED + 10; //31   -25
///////////////////////////////////////////////
   
   
   
  // SPS
  
  for (j=0; j < 1; j++) { 
  colorChase_segment(strip.Color(100, 0, 15), SPEED ,LED,20); // White
  }
  
    LED = LED + 20; //51
      
  
     for (j=0; j < 5; j++) { 
  colorChase_segment(strip.Color(127, 0, 0), SPEED,LED,25); // White
  SPEED = SPEED - 10;  
  }
  LED = LED + 25; //76
  
  ////////////////////////////////////////////////////////////
  //LHC 
  
  
      for (j=0; j < 5; j++) { 
  colorChase_segment(strip.Color(127, 0, 0), SPEED,LED,80); // White
  SPEED = SPEED - 1;  
  }
  
  
  // 160 -107 = 53   -5
  
    for (j=0; j < 1; j++) { 
  colorChase_segment(strip.Color(127, 0, 0), SPEED ,LED,42); // White
  }

    
   // Fill the entire strip with...
  colorWipe_segment(strip.Color(127, 127, 127), 50, LED + 42 ,42);  // white
  colorWipe_segment(strip.Color(127, 127, 127), 50, LED ,42);  // white
 // rainbow(3);


  for (j=0; j < 5; j++)
  
   { 
     
  allOn(1000);
  allOff(1000);
  
  }
 
  rainbowCycle(0);  // make it go through the cycle fairly fast
  
  
}

 




void rainbow(uint8_t wait) {
  int i, j;
   
  for (j=0; j < 384; j++) {     // 3 cycles of all 384 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel( (i + j) % 384));
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}

// Slightly different, this one makes the rainbow wheel equally distributed 
// along the chain
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
  
  for (j=0; j < 384 * 5; j++) {     // 5 cycles of all 384 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      // tricky math! we use each pixel as a fraction of the full 384-color wheel
      // (thats the i / strip.numPixels() part)
      // Then add in j which makes the colors go around per pixel
      // the % 384 is to make the wheel cycle around
      strip.setPixelColor(i, Wheel( ((i * 384 / strip.numPixels()) + j) % 384) );
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}

// Fill the dots progressively along the strip.
void colorWipe(uint32_t c, uint8_t wait) {
  int i;

  for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}



// Fill the dots progressively along the strip.
void colorWipe_segment (uint32_t c, uint8_t wait,  uint8_t start_led , uint8_t segment ) {
  int i;

  for (i= start_led; i < start_led + segment; i++) {
      strip.setPixelColor(i, c);
      
      strip.show();
      delay(wait);
  }
}

// Chase one dot down the full strip.
void colorChase(uint32_t c, uint8_t wait) {
  int i;

  // Start by turning all pixels off:
  for(i=0; i<strip.numPixels(); i++) strip.setPixelColor(i, 0);

  // Then display one pixel at a time:
  for(i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c); // Set new pixel 'on'
    strip.setPixelColor(i+1, c);
    strip.setPixelColor(i+2, c);
    strip.setPixelColor(i+3, c);
    strip.show();              // Refresh LED states
    strip.setPixelColor(i, 0); // Erase pixel, but don't refresh!
    strip.setPixelColor(i+1, c);
    strip.setPixelColor(i+2, c);
    strip.setPixelColor(i+3, c);

    delay(wait);
  }

  strip.show(); // Refresh to turn off last pixel
}


// Chase one dot down the full strip.
void colorChase_segment(uint32_t c, uint8_t wait, uint8_t start_led , uint8_t segment ) {
  int i;

  // Start by turning all pixels off:
  for(i=0; i<strip.numPixels(); i++) strip.setPixelColor(i, 0);

  // Then display one pixel at a time:
  for(i=start_led; i< segment+start_led ; i++) {
    strip.setPixelColor(i, c); // Set new pixel 'on'
    strip.setPixelColor(i+1, c);
    strip.setPixelColor(i+2, c);
    strip.setPixelColor(i+3, c);
    strip.show();              // Refresh LED states
    strip.setPixelColor(i, 0); // Erase pixel, but don't refresh!
    strip.setPixelColor(i+1, c);
    strip.setPixelColor(i+2, c);
    strip.setPixelColor(i+3, c);
    
    delay(wait);
  }

  strip.show(); // Refresh to turn off last pixel
}

void allOff(uint8_t wait) {

  int i;

  // Start by turning all pixels off:
  for(i=0; i<strip.numPixels(); i++) strip.setPixelColor(i, 0);
 delay(wait);
  

  strip.show(); // Refresh to turn off last pixel
}

void allOn(uint8_t wait) {

  int i;

  // Start by turning all pixels off:
  for(i=0; i<strip.numPixels(); i++) strip.setPixelColor(i,strip.Color(127, 0,0 ) );
 delay(wait);
  

  strip.show(); // Refresh to turn off last pixel
}



/* Helper functions */

//Input a value 0 to 384 to get a color value.
//The colours are a transition r - g -b - back to r

uint32_t Wheel(uint16_t WheelPos)
{
  byte r, g, b;
  switch(WheelPos / 128)
  {
    case 0:
      r = 127 - WheelPos % 128;   //Red down
      g = WheelPos % 128;      // Green up
      b = 0;                  //blue off
      break; 
    case 1:
      g = 127 - WheelPos % 128;  //green down
      b = WheelPos % 128;      //blue up
      r = 0;                  //red off
      break; 
    case 2:
      b = 127 - WheelPos % 128;  //blue down 
      r = WheelPos % 128;      //red up
      g = 0;                  //green off
      break; 
  }
  return(strip.Color(r,g,b));
}
