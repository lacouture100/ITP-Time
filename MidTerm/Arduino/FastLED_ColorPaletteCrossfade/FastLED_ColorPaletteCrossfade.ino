#include <FastLED.h>

#define LED_PIN     3
#define LED_PIN2     5
#define NUM_LEDS    144
#define BRIGHTNESS  96
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];
CRGB leds2[NUM_LEDS];

#define UPDATES_PER_SECOND 100

// This example shows how to cross-fade between different color palettes
// using the function nblendPaletteTowardPalette.
//
// The basic idea is that you always have a "current palette" that you're
// pulling colors from with ColorFromPalette, and you have a "target palette"
// which is the 'next' palette that you want to get to.
//
// After that, implementation is relatively simple: just periodically call
//   nblendPaletteTowardPalette( currentPalette, targetPalette);
// If the current palette is not yet equal to the target palette, this
// function will make a few small changes to the current palette to make
// it slightly more like the target.  Over time, the current palette will
// come to be equal to the target.
// There's no need to test the current and target for equality; it's safe
// to keep calling nblendPaletteTowardPalette even after current reaches target.
// For faster blending, call nblendPaletteTowardPalette twice per loop.


CRGBPalette16 currentPalette( CRGB::Black);
CRGBPalette16 currentPalette2( CRGB::Black);
CRGBPalette16 targetPalette( CRGBPalette16(
                               CHSV(180, 255, 255),
                               CHSV(192, 255, 255),
                               CHSV(192, 255, 255),
                               CHSV(0, 255, 255),
                               /**/
                               CHSV(0, 255, 255),
                               CHSV(0, 255, 255),
                               CHSV(0, 255, 255),
                               CHSV(0, 255, 255),
                               /**/
                               CHSV(0, 255, 255),
                               CHSV(0, 255, 255),
                               CHSV(0, 180, 255),
                               CHSV(0, 180, 255),
                               /**/
                               CHSV(0, 255, 255),
                               CHSV(192, 255, 255),
                               CHSV(192, 255, 255),
                               CHSV(180, 255, 255)) );
CRGBPalette16 targetPalette2(  CRGBPalette16(
                                 CHSV(180, 255, 255),
                                 CHSV(0, 255, 255),
                                 CHSV(0, 255, 255),
                                 CHSV(0, 255, 255),
                                 /**/
                                 CHSV(0, 255, 255),
                                 CHSV(0, 255, 255),
                                 CHSV(0, 255, 255),
                                 CHSV(0, 255, 255),
                                 /**/
                                 CHSV(0, 255, 255),
                                 CHSV(0, 255, 255),
                                 CHSV(0, 180, 255),
                                 CHSV(0, 180, 255),
                                 /**/
                                 CHSV(0, 255, 255),
                                 CHSV(0, 255, 255),
                                 CHSV(0, 255, 255),
                                 CHSV(180, 255, 255)));


int timeCounter = 0;

unsigned long startMillis;
unsigned long startLEDMillis;
unsigned long currentMillis;
const unsigned long period = 1000;

bool paletteMsg_1 = true;
bool paletteMsg_2 = true;
bool paletteMsg_3 = true;
bool paletteMsg_4 = true;
bool paletteMsg_5 = true;
bool paletteMsg_6 = true;
bool paletteMsg_7 = true;
bool paletteMsg_8 = true;
bool paletteMsg_9 = true;

void setup() {
  delay( 500 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED_PIN2, COLOR_ORDER>(leds2, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  startMillis = millis();
  startLEDMillis = millis();
}


void loop()
{
  currentMillis = millis();  //get the current time
  if (currentMillis - startMillis >= period) {
    startMillis = currentMillis;
    Serial.println(timeCounter);
    timeCounter += 1;
  }
 


  // Here we set currentMillis to the now() time.
  ChangePalettePeriodically_bottom(startLEDMillis, currentMillis, 50000, 75000, 100000, 135000, 350000, 600000, 650000, 675000, 725000  );
    ChangePalettePeriodically_top(startLEDMillis, currentMillis,  50000, 75000, 100000, 135000, 350000, 600000, 650000, 675000, 725000 );

  //ChangePalettePeriodically_top(startLEDMillis, currentMillis, 50000, 75000, 100000, 135000, 350000, 600000, 650000, 675000, 725000 );



  // Crossfade current palette slowly toward the target palette
  //
  // Each time that nblendPaletteTowardPalette is called, small changes
  // are made to currentPalette to bring it closer to matching targetPalette.
  // You can control how many changes are made in each call:
  //   - the default of 24 is a good balance
  //   - meaningful values are 1-48.  1=veeeeeeeery slow, 48=quickest
  //   - "0" means do not change the currentPalette at all; freeze
  //(currentMillis % 4 == 0) {
  uint8_t maxChanges = 4;
  nblendPaletteTowardPalette( currentPalette, targetPalette, maxChanges);
  nblendPaletteTowardPalette( currentPalette2, targetPalette2, maxChanges);
  // }


  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */


  FillLEDsFromPaletteColors(startIndex);
  FillLEDsFromPaletteColors2(startIndex);
  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);
}

void FillLEDsFromPaletteColors(  uint8_t colorIndex)
{
  uint8_t brightness = 255;

  for ( int i = 0; i < NUM_LEDS; i++) {
    uint8_t paletteIndex = map(i, 0, NUM_LEDS - 1, 0, 240); //index is now based on pixel number
    leds[i] = ColorFromPalette( currentPalette, paletteIndex  , brightness);
    //colorIndex += 1;
  }
}

void FillLEDsFromPaletteColors2( uint8_t colorIndex)
{
  uint8_t brightness = 255;

  for ( int i = 0; i < NUM_LEDS; i++) {
    uint8_t paletteIndex = map(i, 0, NUM_LEDS - 1, 0, 240); //index is now based on pixel number
    leds2[i] = ColorFromPalette( currentPalette2, paletteIndex , brightness);

    //colorIndex += 1;
  }
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ChangePalettePeriodically_top(unsigned long startMillis,
                                   unsigned long currentMillis,
                                   long interval1,
                                   long interval2,
                                   long interval3,
                                   long interval4,
                                   long interval5,
                                   long interval6,
                                   long interval7,
                                   long interval8,
                                   long interval9
                                  ) {



  if (paletteMsg_1) {
    paletteMsg_1 = false;
  }
  if ( currentMillis - startMillis <= interval1)  {
    if (paletteMsg_1 && (currentMillis - startMillis <  1000)) {
      Serial.println("First Palette activated - DAWN");
      //Turn off debug msg
      paletteMsg_1 = false;
    }

    targetPalette2 =  CRGBPalette16( CHSV(180, 255, 255),
                                     CHSV(0, 255, 255),
                                     CHSV(0, 255, 255),
                                     CHSV(0, 255, 255),
                                     /**/
                                     CHSV(0, 255, 255),
                                     CHSV(0, 255, 255),
                                     CHSV(0, 255, 255),
                                     CHSV(0, 255, 255),
                                     /**/
                                     CHSV(0, 255, 255),
                                     CHSV(0, 255, 255),
                                     CHSV(0, 255, 255),
                                     CHSV(0, 255, 255),
                                     /**/
                                     CHSV(0, 255, 255),
                                     CHSV(0, 255, 255),
                                     CHSV(0, 255, 255),
                                     CHSV(180, 255, 255));
  }
  if ( currentMillis - startMillis > interval1 && currentMillis - startMillis <= interval2)  {
    if (paletteMsg_2 && (currentMillis - startMillis <  interval1 + 1000)) {
      Serial.println("Second Palette activated - SUNRISE START");      //Turn off debug msg
      paletteMsg_2 = false;
    }

    targetPalette2 = CRGBPalette16( CHSV(180, 255, 255),
                                    CHSV(180, 255, 255),
                                    CHSV(0, 255, 255),
                                    CHSV(0, 255, 255),
                                    /**/
                                    CHSV(0, 255, 255),
                                    CHSV(0, 255, 255),
                                    CHSV(64, 255, 255),
                                    CHSV(64, 255, 255),
                                    /**/
                                    CHSV(64, 255, 255),
                                    CHSV(64, 255, 255),
                                    CHSV(0, 255, 255),
                                    CHSV(0, 255, 255),
                                    /**/
                                    CHSV(0, 255, 255),
                                    CHSV(0, 255, 255),
                                    CHSV(180, 255, 255),
                                    CHSV(180, 255, 255));
  }
  if (currentMillis - startMillis > interval2 && currentMillis - startMillis <= interval3)  {
    if (paletteMsg_3 && (currentMillis - startMillis <  interval2 + 1000)) {
      Serial.println("Third Palette activated - GOLDEN HOUR END");
      paletteMsg_3 = false;
    }
    targetPalette2 =  CRGBPalette16( CHSV(160, 255, 255),
                                     CHSV(160, 255, 255),
                                     CHSV(160, 255, 255),
                                     CHSV(160, 255, 255),
                                     /**/
                                     CHSV(160, 255, 255),
                                     CHSV(160, 255, 255),
                                     CHSV(64, 255, 255),
                                     CHSV(64, 255, 255),
                                     /**/
                                     CHSV(64, 255, 255),
                                     CHSV(64, 255, 255),
                                     CHSV(160, 255, 255),
                                     CHSV(160, 255, 255),
                                     /**/
                                     CHSV(160, 255, 255),
                                     CHSV(160, 255, 255),
                                     CHSV(160, 255, 255),
                                     CHSV(160, 255, 255));
  }
  if ( currentMillis - startMillis > interval3 && currentMillis - startMillis <= interval4)  {
    if (paletteMsg_4 && (currentMillis - startMillis <  interval3 + 1000)) {
      Serial.println("Fourth Palette activated  - SOLAR NOON");
      paletteMsg_4 = false;
    }
    targetPalette2 = CRGBPalette16( CHSV(160, 255, 255),
                                    CHSV(160, 255, 255),
                                    CHSV(160, 255, 255),
                                    CHSV(160, 255, 255),
                                    /**/
                                    CHSV(160, 255, 255),
                                    CHSV(160, 255, 255),
                                    CHSV(160, 255, 255),
                                    CHSV(160, 255, 255),
                                    /**/
                                    CHSV(160, 255, 255),
                                    CHSV(160, 255, 255),
                                    CHSV(160, 255, 255),
                                    CHSV(160, 255, 255),
                                    /**/
                                    CHSV(160, 255, 255),
                                    CHSV(160, 255, 255),
                                    CHSV(160, 255, 255),
                                    CHSV(160, 255, 255));
  }
  if ( currentMillis - startMillis > interval4 && currentMillis - startMillis <= interval5)  {
    if (paletteMsg_5 && (currentMillis - startMillis <  interval4 + 1000)) {
      Serial.println("Fifth Palette activated - GOLDEN HOUR");
      paletteMsg_5 = false;
    }

    targetPalette2 =  CRGBPalette16( CHSV(32, 255, 255),
                                     CHSV(32, 255, 255),
                                     CHSV(32, 255, 255),
                                     CHSV(32, 255, 255),
                                     /**/
                                     CHSV(32, 255, 255),
                                     CHSV(32, 255, 255),
                                     CHSV(64, 255, 255),
                                     CHSV(64, 255, 255),
                                     /**/
                                     CHSV(64, 255, 255),
                                     CHSV(64, 255, 255),
                                     CHSV(32, 255, 255),
                                     CHSV(32, 255, 255),
                                     /**/
                                     CHSV(32, 255, 255),
                                     CHSV(32, 255, 255),
                                     CHSV(32, 255, 255),
                                     CHSV(32, 255, 255));
  }
  if ( currentMillis - startMillis > interval5 && currentMillis - startMillis <= interval6)  {
    if (paletteMsg_6 && (currentMillis - startMillis <  interval5 + 1000)) {
      Serial.println("Sixth Palette activated - SUNSET START ");
      paletteMsg_6 = false;
    }

    targetPalette2 =  CRGBPalette16( CHSV(32, 255, 255),
                                     CHSV(32, 255, 255),
                                     CHSV(32, 255, 255),
                                     CHSV(32, 255, 255),
                                     /**/
                                     CHSV(32, 255, 255),
                                     CHSV(32, 255, 255),
                                     CHSV(64, 255, 255),
                                     CHSV(64, 255, 255),
                                     /**/
                                     CHSV(64, 255, 255),
                                     CHSV(64, 255, 255),
                                     CHSV(32, 255, 255),
                                     CHSV(32, 255, 255),
                                     /**/
                                     CHSV(32, 255, 255),
                                     CHSV(32, 255, 255),
                                     CHSV(32, 255, 255),
                                     CHSV(32, 255, 255));
  }
  if ( currentMillis - startMillis > interval6 && currentMillis - startMillis <= interval7)  {
    if (paletteMsg_7 && (currentMillis - startMillis <  interval6 + 1000)) {
      Serial.println("Seventh Palette activated - SUNSET");
      paletteMsg_7 = false;
    }

    targetPalette2 =  CRGBPalette16( CHSV(180, 255, 255),
                                     CHSV(180, 255, 255),
                                     CHSV(0, 255, 255),
                                     CHSV(0, 255, 255),
                                     /**/
                                     CHSV(0, 255, 255),
                                     CHSV(0, 255, 255),
                                     CHSV(0, 255, 255),
                                     CHSV(0, 255, 255),
                                     /**/
                                     CHSV(0, 255, 255),
                                     CHSV(0, 255, 255),
                                     CHSV(0, 255, 255),
                                     CHSV(0, 255, 255),
                                     /**/
                                     CHSV(0, 255, 255),
                                     CHSV(0, 255, 255),
                                     CHSV(180, 255, 255),
                                     CHSV(180, 255, 255));
  }
  if ( currentMillis - startMillis > interval7 && currentMillis - startMillis <= interval8)  {
    if (paletteMsg_8 && (currentMillis - startMillis <  interval7 + 1000)) {
      Serial.println("Eigth Palette activated - DUSK");
      paletteMsg_8 = false;
    }

    targetPalette2 =  CRGBPalette16( CHSV(180, 200, 255),
                                     CHSV(180, 200, 255),
                                     CHSV(180, 200, 255),
                                     CHSV(180, 200, 255),
                                     /**/
                                     CHSV(180, 200, 255),
                                     CHSV(180, 200, 255),
                                     CHSV(180, 200, 255),
                                     CHSV(180, 200, 255),
                                     /**/
                                     CHSV(180, 200, 255),
                                     CHSV(180, 200, 255),
                                     CHSV(180, 200, 255),
                                     CHSV(180, 200, 255),
                                     /**/
                                     CHSV(180, 200, 255),
                                     CHSV(180, 200, 255),
                                     CHSV(180, 200, 255),
                                     CHSV(180, 200, 255));
  }
  if ( currentMillis - startMillis > interval8 && currentMillis - startMillis <= interval8)  {
    if (paletteMsg_9 && (currentMillis - startMillis <  interval8 + 1000)) {
      Serial.println("Sixth Palette activated - NIGHT");
      paletteMsg_9 = false;
    }

    targetPalette2 =  CRGBPalette16( CHSV(180, 200, 255),
                                     CHSV(180, 200, 255),
                                     CHSV(180, 200, 255),
                                     CHSV(180, 200, 255),
                                     /**/
                                     CHSV(180, 200, 255),
                                     CHSV(180, 200, 255),
                                     CHSV(180, 200, 255),
                                     CHSV(180, 200, 255),
                                     /**/
                                     CHSV(180, 200, 255),
                                     CHSV(180, 200, 255),
                                     CHSV(180, 200, 255),
                                     CHSV(180, 200, 255),
                                     /**/
                                     CHSV(180, 200, 255),
                                     CHSV(180, 200, 255),
                                     CHSV(180, 200, 255),
                                     CHSV(180, 200, 255));
    currentMillis = millis();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ChangePalettePeriodically_bottom(unsigned long startMillis,
                                      unsigned long currentMillis,
                                      long interval1,
                                      long interval2,
                                      long interval3,
                                      long interval4,
                                      long interval5,
                                      long interval6,
                                      long interval7,
                                      long interval8,
                                      long interval9
                                     ) {



  if (paletteMsg_1) {
    paletteMsg_1 = false;
  }
  if ( currentMillis - startMillis <= interval1)  {
    if (paletteMsg_1 && (currentMillis - startMillis <  1000)) {
      Serial.println("First Palette activated - DAWN");
      //Turn off debug msg
      paletteMsg_1 = false;
    }

    targetPalette =  CRGBPalette16( CHSV(180, 255, 255),
                                    CHSV(180, 255, 255),
                                    CHSV(180, 255, 255),
                                    CHSV(180, 255, 255),
                                    /**/
                                    CHSV(180, 255, 255),
                                    CHSV(180, 255, 255),
                                    CHSV(180, 255, 255),
                                    CHSV(0, 255, 255),
                                    /**/
                                    CHSV(0, 255, 255),
                                    CHSV(180, 255, 255),
                                    CHSV(180, 255, 255),
                                    CHSV(180, 255, 255),
                                    /**/
                                    CHSV(180, 255, 255),
                                    CHSV(180, 255, 255),
                                    CHSV(180, 255, 255),
                                    CHSV(180, 255, 255));
  }
  if ( currentMillis - startMillis > interval1 && currentMillis - startMillis <= interval2)  {
    if (paletteMsg_2 && (currentMillis - startMillis <  interval1 + 1000)) {
      Serial.println("Second Palette activated - SUNRISE START");      //Turn off debug msg
      paletteMsg_2 = false;
    }

    targetPalette = CRGBPalette16( CHSV(0, 255, 255),
                                   CHSV(0, 255, 255),
                                   CHSV(0, 255, 255),
                                   CHSV(0, 255, 255),
                                   /**/
                                   CHSV(0, 255, 255),
                                   CHSV(0, 255, 255),
                                   CHSV(0, 255, 255),
                                   CHSV(0, 255, 255),
                                   /**/
                                   CHSV(0, 255, 255),
                                   CHSV(0, 255, 255),
                                   CHSV(0, 255, 255),
                                   CHSV(0, 255, 255),
                                   /**/
                                   CHSV(0, 255, 255),
                                   CHSV(0, 255, 255),
                                   CHSV(0, 255, 255),
                                   CHSV(0, 255, 255));
  }
  if (currentMillis - startMillis > interval2 && currentMillis - startMillis <= interval3)  {
    if (paletteMsg_3 && (currentMillis - startMillis <  interval2 + 1000)) {
      Serial.println("Third Palette activated - GOLDEN HOUR END");
      paletteMsg_3 = false;
    }
    targetPalette =  CRGBPalette16( CHSV(0, 0, 255),
                                    CHSV(0, 0, 255),
                                    CHSV(32, 255, 255),
                                    CHSV(32, 255, 255),
                                    /**/
                                    CHSV(32, 255, 255),
                                    CHSV(32, 255, 255),
                                    CHSV(32, 255, 255),
                                    CHSV(64, 255, 255),

                                    CHSV(64, 255, 255),
                                    CHSV(32, 255, 255),
                                    CHSV(32, 255, 255),
                                    CHSV(32, 255, 255),
                                    /**/
                                    CHSV(32, 255, 255),
                                    CHSV(32, 0, 255),
                                    CHSV(0, 0, 255),
                                    CHSV(0, 0, 255));
  }
  if ( currentMillis - startMillis > interval3 && currentMillis - startMillis <= interval4)  {
    if (paletteMsg_4 && (currentMillis - startMillis <  interval3 + 1000)) {
      Serial.println("Fourth Palette activated  - SOLAR NOON");
      paletteMsg_4 = false;
    }
    targetPalette = CRGBPalette16( CHSV(0, 0, 255),
                                   CHSV(0, 0, 255),
                                   CHSV(0, 0, 255),
                                   CHSV(0, 0, 255),
                                   /**/
                                   CHSV(0, 0, 255),
                                   CHSV(0, 0, 255),
                                   CHSV(0, 0, 255),
                                   CHSV(0, 0, 255),
                                   /**/
                                   CHSV(0, 0, 255),
                                   CHSV(0, 0, 255),
                                   CHSV(0, 0, 255),
                                   CHSV(0, 0, 255),
                                   /**/
                                   CHSV(0, 0, 255),
                                   CHSV(0, 0, 255),
                                   CHSV(0, 0, 255),
                                   CHSV(0, 0, 255));
  }
  if ( currentMillis - startMillis > interval4 && currentMillis - startMillis <= interval5)  {
    if (paletteMsg_5 && (currentMillis - startMillis <  interval4 + 1000)) {
      Serial.println("Fifth Palette activated - GOLDEN HOUR");
      paletteMsg_5 = false;
    }

    targetPalette =  CRGBPalette16( CHSV(32, 255, 255),
                                    CHSV(32, 255, 255),
                                    CHSV(32, 255, 255),
                                    CHSV(32, 255, 255),
                                    /**/
                                    CHSV(32, 255, 255),
                                    CHSV(32, 255, 255),
                                    CHSV(32, 255, 255),
                                    CHSV(64, 255, 255),
                                    /**/
                                    CHSV(64, 255, 255),
                                    CHSV(32, 255, 255),
                                    CHSV(32, 255, 255),
                                    CHSV(32, 255, 255),
                                    /**/
                                    CHSV(32, 255, 255),
                                    CHSV(32, 255, 255),
                                    CHSV(32, 255, 255),
                                    CHSV(32, 255, 255));
  }
  if ( currentMillis - startMillis > interval5 && currentMillis - startMillis <= interval6)  {
    if (paletteMsg_6 && (currentMillis - startMillis <  interval5 + 1000)) {
      Serial.println("Sixth Palette activated - SUNSET START ");
      paletteMsg_6 = false;
    }

    targetPalette =  CRGBPalette16( CHSV(0, 255, 255),
                                    CHSV(0, 255, 255),
                                    CHSV(0, 255, 255),
                                    CHSV(0, 255, 255),
                                    /**/
                                    CHSV(0, 255, 255),
                                    CHSV(32, 255, 255),
                                    CHSV(32, 255, 255),
                                    CHSV(64, 255, 255),
                                    /**/
                                    CHSV(64, 255, 255),
                                    CHSV(32, 255, 255),
                                    CHSV(32, 255, 255),
                                    CHSV(0, 255, 255),
                                    /**/
                                    CHSV(0, 255, 255),
                                    CHSV(0, 255, 255),
                                    CHSV(0, 255, 255),
                                    CHSV(0, 255, 255));
  }
  if ( currentMillis - startMillis > interval6 && currentMillis - startMillis <= interval7)  {
    if (paletteMsg_7 && (currentMillis - startMillis <  interval6 + 1000)) {
      Serial.println("Seventh Palette activated - SUNSET");
      paletteMsg_7 = false;
    }

    targetPalette =   CRGBPalette16( CHSV(0, 255, 255),
                                     CHSV(0, 255, 255),
                                     CHSV(0, 255, 255),
                                     CHSV(0, 255, 255),
                                     /**/
                                     CHSV(0, 255, 255),
                                     CHSV(32, 255, 255),
                                     CHSV(32, 255, 255),
                                     CHSV(64, 255, 255),
                                     /**/
                                     CHSV(64, 255, 255),
                                     CHSV(32, 255, 255),
                                     CHSV(32, 255, 255),
                                     CHSV(0, 255, 255),
                                     /**/
                                     CHSV(0, 255, 255),
                                     CHSV(0, 255, 255),
                                     CHSV(0, 255, 255),
                                     CHSV(0, 255, 255));
  }
  if ( currentMillis - startMillis > interval7 && currentMillis - startMillis <= interval8)  {
    if (paletteMsg_8 && (currentMillis - startMillis <  interval7 + 1000)) {
      Serial.println("Eigth Palette activated - DUSK");
      paletteMsg_8 = false;
    }

    targetPalette =  CRGBPalette16( CHSV(32, 255, 255),
                                    CHSV(32, 255, 255),
                                    CHSV(32, 255, 255),
                                    CHSV(32, 255, 255),
                                    /**/
                                    CHSV(32, 255, 255),
                                    CHSV(32, 255, 255),
                                    CHSV(32, 255, 255),
                                    CHSV(32, 255, 255),
                                    /**/
                                    CHSV(32, 255, 255),
                                    CHSV(32, 255, 255),
                                    CHSV(32, 255, 255),
                                    CHSV(32, 255, 255),
                                    /**/
                                    CHSV(32, 255, 255),
                                    CHSV(32, 255, 255),
                                    CHSV(32, 255, 255),
                                    CHSV(32, 255, 255));
  }
  if ( currentMillis - startMillis > interval8)  {
    if (paletteMsg_9 && (currentMillis - startMillis <  interval8 + 1000)) {
      Serial.println("Ninth Palette activated - NIGHT");
      paletteMsg_9 = false;
    }
    targetPalette =  CRGBPalette16();
  
    targetPalette =  CRGBPalette16( CHSV(180, 100, 20),
                                    CHSV(180, 100, 20),
                                    CHSV(180, 100, 20),
                                    CHSV(180, 100, 20),
                                    //
                                    CHSV(180, 100, 20),
                                    CHSV(180, 100, 20),
                                    CHSV(180, 100, 20),
                                    CHSV(180, 100, 20),
                                    //
                                    CHSV(180, 100, 20),
                                    CHSV(180, 100, 20),
                                    CHSV(180, 100, 20),
                                    CHSV(180, 100, 20),
                                    //
                                    CHSV(180, 100, 20),
                                    CHSV(180, 100, 20),
                                    CHSV(180, 100, 20),
                                    CHSV(180, 100, 20));
        
    
  }
}
