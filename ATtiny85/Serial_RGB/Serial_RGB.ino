#include <RecvOnlySoftSerial.h>
#include <Adafruit_NeoPixel.h>


#ifdef __AVR__ 
  #include <avr/power.h>
#endif


// Defines
#define LEDS_PIN       0
#define LEDS_PER_RING  12
#define RINGS          5
#define NUM_LEDS       (LEDS_PER_RING * RINGS)
#define RX_PIN         2
#define BUFFER_SIZE    16
#define BAUD           9600


// Global variables
Adafruit_NeoPixel npPixels = Adafruit_NeoPixel(NUM_LEDS, LEDS_PIN, NEO_GRB + NEO_KHZ800);
RecvOnlySoftSerial roSoftSerial(RX_PIN);

char cBuffer[BUFFER_SIZE];
unsigned int unBufferIndex = 0;

unsigned int unActiveRing = 0;
bool bReady = false;


void setup() {
  npPixels.begin();
  
  pinMode(RX_PIN, INPUT);
  roSoftSerial.begin(BAUD);

  npPixels.setBrightness(35);
  
  for(int i = 0; i < NUM_LEDS; ++i) {
    npPixels.setPixelColor(i, npPixels.Color(255, 255, 255));
  }

  npPixels.show();
}


void loop() {
  //while(roSoftSerial.available() <= 0) {}
  if(roSoftSerial.available() > 0) {
    char c = roSoftSerial.read();

    if(c == 32 || (c >= 48 && c <= 122)) {
      if(unBufferIndex < BUFFER_SIZE) {
        cBuffer[unBufferIndex] = c;
        cBuffer[unBufferIndex + 1] = 0;
        
        unBufferIndex++;
      }
    } else if(c == 13) {
      unsigned int unInteger, unR, unG, unB;
      
      if(sscanf(cBuffer, "r%u", &unInteger) == 1) { // ring selection
        unActiveRing = unInteger;
      } else if(sscanf(cBuffer, "l%u %u %u %u", &unInteger, &unR, &unG, &unB) == 4) { // led setting
        npPixels.setPixelColor(unActiveRing * 12 + unInteger, npPixels.Color(unR * 10, unG * 10, unB * 10));
      } else if(cBuffer[0] == 'c') { // commit
        npPixels.show();
      }
      
      unBufferIndex = 0;
    }
  }
}

