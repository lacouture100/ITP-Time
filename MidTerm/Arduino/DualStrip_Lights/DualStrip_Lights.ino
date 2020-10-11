#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN1 5
#define PIN2 3
#define NUMPIXELS1 144
#define NUMPIXELS2 144

#define PIXELTYPE NEO_GRB + NEO_KHZ800

Adafruit_NeoPixel pixels1 = Adafruit_NeoPixel(NUMPIXELS1, PIN1, PIXELTYPE);
Adafruit_NeoPixel pixels2 = Adafruit_NeoPixel(NUMPIXELS2, PIN2, PIXELTYPE);

#include <Ramp.h>
int lastValue;                                // global variable
rampInt myRamp;
rampInt myRamp2;

void setup() {

  pixels1.begin();
  pixels2.begin();

  pixels1.setBrightness(40);
  pixels2.setBrightness(40);

  pixels1.show(); // Initialize all pixels to 'off'
  pixels2.show();

  myRamp.go(255);
  myRamp2.go(0);
  myRamp.go(0, 200, LINEAR, LOOPFORWARD);
  myRamp2.go(255, 200, LINEAR, LOOPFORWARD);
}

void loop() {
  int rampVal = myRamp.update();
  int rampVal2 = myRamp2.update();
  //colorWipe(pixels1.Color(0, 0, 255), 20, pixels1);
  //colorWipe(pixels2.Color(0, 255, 0), 20, pixels2);

  //colorPulsingTrail(255, 0, 0,30,20);
  //  rainbowExp(72,2000);
  // colorHour(pixels.Color(255, 0, 0),2,200);
  // rainbowCycle(20);
  // CylonBounce(255, 0, 0, 3, 5, 5, 30, 500);


  colorHour(pixels1, pixels1.Color(0, 0, 255), 3, 1000 );
  colorHour(pixels2, pixels2.Color(255, 0, 0), 3, 1000 );
}



void horizonClock(int startTime,int totalDayTime){

}



/*
 * void colorHour(Adafruit_NeoPixel pixels, uint32_t c, int tail, int wait ) {
  int impact = 3;
  for (uint16_t i = 0; i < pixels.numPixels(); i++) {
    pixels.setPixelColor(i, c);

    if (i % 6 == 0) {
      pixels.setPixelColor(i, pixels.Color(0, 255, 0));
    } else {
    }

    //pixels.setPixelColor((i-tail), 0);

    pixels.show();
    delay(wait);
  }
}

*/
