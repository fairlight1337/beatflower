#include <RecvOnlySoftSerial.h>
#include <Adafruit_NeoPixel.h>


#ifdef __AVR__ 
  #include <avr/power.h>
#endif


// Defines
#define LEDS_PIN       1
#define LEDS_PER_RING  12
#define RINGS          5
#define NUM_LEDS       (LEDS_PER_RING * RINGS)
#define RX_PIN         3
#define BUFFER_SIZE    64


// Global variables
Adafruit_NeoPixel npPixels = Adafruit_NeoPixel(NUM_LEDS, LEDS_PIN, NEO_GRB + NEO_KHZ800);
RecvOnlySoftSerial roSoftSerial(RX_PIN);

char cBuffer[BUFFER_SIZE];
unsigned int unBufferIndex = 0;

unsigned int unActiveRing = 0;


void setup() {
  npPixels.begin();
  
  pinMode(RX_PIN, INPUT);
  roSoftSerial.begin(9600);
}


void loop() {
  if(roSoftSerial.available()) {
    char c = roSoftSerial.read();
    
    if(c == 13) {
      int nInteger, nR, nG, nB;
      
      if(sscanf(cBuffer, "brightness(%d)", &nInteger) != EOF) {
        npPixels.setBrightness(nInteger);
      } else if(sscanf(cBuffer, "ring(%d)", &nInteger) != EOF) {
        unActiveRing = nInteger;
      } else if(sscanf(cBuffer, "led(%d, %d, %d, %d)", &nInteger, &nR, &nG, &nB) != EOF) {
        npPixels.setPixelColor(unActiveRing * 12 + nInteger, npPixels.Color(nR, nG, nB));
      } else if(sscanf(cBuffer, "show()") != EOF) {
        npPixels.show();
      } else if(sscanf(cBuffer, "clear()") != EOF) {
        for(unsigned int unI = 0; unI < NUM_LEDS; ++unI) {
          npPixels.setPixelColor(unI, npPixels.Color(0, 0, 0));
        }
        
        npPixels.show();
      }
      
      unBufferIndex = 0;
    } else {
      if(!(unBufferIndex >= BUFFER_SIZE - 1)) {
        cBuffer[unBufferIndex] = c;
        unBufferIndex++;
      }
    }
  }
}

