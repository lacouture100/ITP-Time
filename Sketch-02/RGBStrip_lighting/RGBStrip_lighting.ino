#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 4
#define NUMPIXELS 144
#define PIXELTYPE NEO_GRB + NEO_KHZ800

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, PIXELTYPE);

#include <Ramp.h>
int lastValue;                                // global variable
rampInt myRamp;
rampInt myRamp2;

void setup() {

  pixels.begin();
  pixels.setBrightness(40);
  pixels.show(); // Initialize all pixels to 'off'


    myRamp.go(255);           
    myRamp2.go(0);           
  myRamp.go(0, 200, LINEAR, LOOPFORWARD);  
  myRamp2.go(255, 200, LINEAR, LOOPFORWARD);
}

void loop() {
   int rampVal = myRamp.update();
   int rampVal2 = myRamp2.update();
  colorWipe(pixels.Color(rampVal, rampVal2, rampVal2),20);
  //colorPulsingTrail(255, 0, 0,30,20);
 
//  rainbowExp(72,2000);
 // colorHour(pixels.Color(255, 0, 0),2,200);
 // rainbowCycle(20);
 // CylonBounce(255, 0, 0, 3, 5, 5, 30, 500);
}

/*void GradientBounce(int red1, int green1, int blue1,int red2, int green2, int blue2, int EyeSize, int leadTrail,int endTrail, int SpeedDelay){
  for(int i = 0; i < pixels.numPixels(); i++) {
          pixels.fill(0,0,0);

    // Sets the last trail
    for(int k=i-endTrail;k<i;k++){
      pixels.setPixelColor(k, red-(i*2), 0, i);
        }

    // Sets the main dot
    for(int j = 1; j <= EyeSize; j++) {
      pixels.setPixelColor(i+j, red, green, blue);
    }
    // Sets the leading trail
    for(int k=0;k<leadTrail;k++){
      pixels.setPixelColor(i+EyeSize+k, red-i*(k/2), 0,i/2*k);
    }
    ;
    pixels.show();
    delay(SpeedDelay);
  }
  }

*/
void CylonBounce(int red, int green, int blue, int EyeSize, int leadTrail, int endTrail, int SpeedDelay, int ReturnDelay) {

  for (int i = 0; i < pixels.numPixels(); i++) {
    pixels.fill(0, 0, 0);

    // Sets the last trail
    for (int k = 0; k <= endTrail; k++) {
      pixels.setPixelColor(i - k, 255 - i, 0, i);
    }
    // Sets the main dot
    for (int j = 1; j <= EyeSize; j++) {
      pixels.setPixelColor(i + j, 255 - i, green, i);
    }
    // Sets the leading trail
    for (int k = 0; k < leadTrail; k++) {
      pixels.setPixelColor(i + EyeSize + k, 255 - i, 0, i);
    }

    pixels.show();
    delay(SpeedDelay);
  }

  delay(ReturnDelay);

  for (int i = pixels.numPixels() - EyeSize - 2; i > 0; i--) {
    // Sets the last trail
    for (int k = endTrail; k >= 0; k--) {
      pixels.setPixelColor(i + k, 255 - i, 0, i);
    }
      // Sets the main dot
       for(int j = 1; j <= EyeSize; j++) {
        //pixels.setPixelColor(i+j, 255 - i, 0, i);
       pixels.setPixelColor(i+j, 0,0,255);
    }
      // Sets the leading trail
      for (int k = leadTrail; k > -1; k--) {
        pixels.setPixelColor(i - EyeSize - k, 255 - i,0, i);
      }

      pixels.show();
      delay(SpeedDelay);
    }

    delay(ReturnDelay);
  }


  // Fill the dots in a sequence one by one
  void colorWipe(uint32_t c, uint8_t wait) {
    for (uint16_t i = 0; i < pixels.numPixels(); i++) {
      pixels.setPixelColor(i, c);
      pixels.show();
      delay(wait);
    }
  }

  // Make a dot travel the strip
  void colorDot(uint32_t c, int tail, int wait) {
    for (uint16_t i = 0; i < pixels.numPixels(); i++) {
      pixels.setPixelColor(i, c);

      pixels.setPixelColor((i - tail), 0);

      pixels.show();
      delay(wait);
    }
  }

  // Make a dot travel the strip
  void colorHour(uint32_t c, int tail, int wait) {
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


  // Make a dot travel the strip
  void colorDotMinuteTrail(uint32_t c, int tail, int wait) {
    int impact = 3;
    for (uint16_t i = 0; i < pixels.numPixels(); i++) {
      pixels.setPixelColor(i, c);
      pixels.setPixelColor(72, c);
      if (i == 72) {
        pixels.fill(pixels.Color(0, 255, 0));

      } else {
      }

      pixels.setPixelColor((i - tail), 0);

      pixels.show();
      delay(wait);
    }
  }


  // Make a dot travel the strip
  void colorPulsingTrail(int r, int g, int b, int tail, uint8_t wait) {
    for (uint16_t i = 0; i < pixels.numPixels(); i++) {
      pixels.setPixelColor(i, pixels.Color(r, g, b));
      for (int j = 0; j < i - tail; j++) {
        pixels.setPixelColor(j, pixels.Color(r - (i * 10), g - (i * 10), b - (i * 10)));
      }
      pixels.show();
      delay(wait);
    }
  }


  //* makes a differnte rainbow in the middle of the strip
  void rainbowDual(int tail, uint8_t wait) {
    uint16_t i, j;
    for (j = 0; j < 256; j++) {
      for (i = 0; i < pixels.numPixels(); i++) {
        pixels.setPixelColor(i, Wheel((i + j)));
        pixels.setPixelColor((i - tail), Wheel(j));
      }
      pixels.show();
      delay(wait);
    }
  }

  void rainbow(uint8_t wait) {
    uint16_t i, j;
    for (j = 0; j < 256; j++) {
      for (i = 0; i < pixels.numPixels(); i++) {
        pixels.setPixelColor(i, Wheel((i + j) & 255));
      }
      pixels.show();
      delay(wait);
    }
  }


  // Slightly different, this makes the rainbow equally distributed throughout
  void rainbowCycle(uint8_t wait) {
    uint16_t i, j;

    for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
      for (i = 0; i < pixels.numPixels(); i++) {
        pixels.setPixelColor(i, Wheel(((i * 256 / pixels.numPixels()) + j) & 255));
      }
      pixels.show();
      delay(wait);
    }
  }


  // Input a value 0 to 255 to get a color value.
  // The colours are a transition r - g - b - back to r.
  uint32_t Wheel(byte WheelPos) {
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85) {
      //The lower the number, the more red it is
      // When it gets higher, Blue starts going upwards and Red goes down
      // When Wheelpos is 0, (255,0,0), when it's 85, (0,0,255)
      //RED TO BLUE
      return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    }
    if (WheelPos < 170) {
      WheelPos -= 85;
      //BLUE TO GREEN
      //0, (0,0,255) // 170, (0,255,0)
      return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
    //GREEN TO RED
    WheelPos -= 170;
    return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
