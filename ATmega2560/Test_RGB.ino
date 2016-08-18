#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif


// Defines
#define PIN 5
#define NUM 12


// Global variables
Adafruit_NeoPixel npPixels = Adafruit_NeoPixel(NUM, PIN, NEO_GRB + NEO_KHZ800);


// Setup: Initialize Pixels
void setup() {
  npPixels.begin();
  npPixels.setBrightness(50);
}


// Loop: Set Pixels' color
void loop() {
  for(int nI = 0; nI < NUM; nI++) {
    npPixels.setPixelColor(nI, pixels.Color(0, 255, 255));
  }
  
  npPixels.show();
}

