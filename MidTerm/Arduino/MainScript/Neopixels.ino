
void startPixels() {

  pixels1.begin();
  pixels2.begin();

  pixels1.setBrightness(40);
  pixels2.setBrightness(40);

  pixels1.show(); // Initialize all pixels to 'off'
  pixels2.show();

}



////////////////////////////////////////////////////////////////////////////////////////


void fadeStrip(Adafruit_NeoPixel pixels, int NUMPIXELS, int stripDivision, int r1, int g1, int b1, int r2, int g2, int b2) {
  int steps = NUMPIXELS;
    for (int i = 0; i < 24; i++) {
      // Sets the pixels to the color adjusted in the fade
      pixels.setPixelColor(i, r1, 255, i*4);
 
  }
    for (int i =25; i < 48; i++) {
      // Sets the pixels to the color adjusted in the fade
      pixels.setPixelColor(i, r2, i*4, 0);
  }
  pixels.show();
}


////////////////////////////////////////////////////////////////////////////////////


// Make a dot travel the strip
void lightPulse(Adafruit_NeoPixel pixels, int r, int g, int b,  uint8_t wait) {
  for (uint16_t i = 0; i < pixels.numPixels(); i++) {
    pixels.setPixelColor(i, pixels.Color(r, g, b ));
    pixels.show();
    delay(wait);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////

void CylonBounce(Adafruit_NeoPixel pixels, int red, int green, int blue, int EyeSize, int leadTrail, int endTrail, int SpeedDelay, int ReturnDelay) {

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
    for (int j = 1; j <= EyeSize; j++) {
      //pixels.setPixelColor(i+j, 255 - i, 0, i);
      pixels.setPixelColor(i + j, 0, 0, 255);
    }
    // Sets the leading trail
    for (int k = leadTrail; k > -1; k--) {
      pixels.setPixelColor(i - EyeSize - k, 255 - i, 0, i);
    }

    pixels.show();
    delay(SpeedDelay);
  }

  delay(ReturnDelay);
}

////////////////////////////////////////////////////////////////////////////////////////////

// Fill the dots in a sequence one by one
void colorWipe(Adafruit_NeoPixel pixels, uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < pixels.numPixels(); i++) {
    pixels.setPixelColor(i, c);
    pixels.show();
    delay(wait);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////

// Make a dot travel the strip
void colorDot(Adafruit_NeoPixel pixels, uint32_t c, int tail, int wait ) {
  for (uint16_t i = 0; i < pixels.numPixels(); i++) {
    pixels.setPixelColor(i, c);

    pixels.setPixelColor((i - tail), 0);

    pixels.show();
    delay(wait);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////

// Make a dot travel the strip
void colorHour(Adafruit_NeoPixel pixels, uint32_t c, int tail, int wait ) {
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

////////////////////////////////////////////////////////////////////////////////////////////

// Make a dot travel the strip
void colorDotMinuteTrail(Adafruit_NeoPixel pixels, uint32_t c, int tail, int wait ) {
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

////////////////////////////////////////////////////////////////////////////////////////////

// Make a dot travel the strip
void colorPulsingTrail(Adafruit_NeoPixel pixels, int r, int g, int b, int tail, uint8_t wait ) {
  for (uint16_t i = 0; i < pixels.numPixels(); i++) {
    pixels.setPixelColor(i, pixels.Color(r, g, b));
    for (int j = 0; j < i - tail; j++) {
      pixels.setPixelColor(j, pixels.Color(r - (i * 10), g - (i * 10), b - (i * 10)));
    }
    pixels.show();
    delay(wait);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////

//* makes a differnte rainbow in the middle of the strip
void rainbowDual(Adafruit_NeoPixel pixels, int tail, uint8_t wait ) {
  uint16_t i, j;
  for (j = 0; j < 256; j++) {
    for (i = 0; i < pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel(pixels, (i + j)));
      pixels.setPixelColor((i - tail), Wheel(pixels, j));
    }
    pixels.show();
    delay(wait);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////

void rainbow(Adafruit_NeoPixel pixels, uint8_t wait ) {
  uint16_t i, j;
  for (j = 0; j < 256; j++) {
    for (i = 0; i < pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel(pixels, (i + j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(Adafruit_NeoPixel pixels, uint8_t wait ) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel(pixels, ((i * 256 / pixels.numPixels()) + j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(Adafruit_NeoPixel pixels, byte WheelPos) {
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
