
void startPixels() {


  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED_PIN2, COLOR_ORDER>(leds2, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  startMillis = millis();
  startLEDMillis = millis();

}
//30000, 60000, 90000, 120000, 150000, 180000, 210000, 240000, 270000
// 30000,

void runLights(long currentMillis, long dawn, long sunriseStart, long goldenHourEnd, long solarNoon, long goldenHour, long sunsetStart, long sunset, long dusk, long night) {

  ChangePalettePeriodically_bottom(startLEDMillis, currentMillis, dawn,  sunriseStart, goldenHourEnd,  solarNoon,  goldenHour,  sunsetStart, sunset, dusk,  night);
  ChangePalettePeriodically_top(startLEDMillis, currentMillis, dawn,  sunriseStart, goldenHourEnd,  solarNoon,  goldenHour,  sunsetStart, sunset, dusk,  night );



  // Crossfade current palette slowly toward the target palette
  //
  // Each time that nblendPaletteTowardPalette is called, small changes
  // are made to currentPalette to bring it closer to matching targetPalette.
  // You can control how many changes are made in each call:
  //   - the default of 24 is a good balance
  //   - meaningful values are 1-48.  1=veeeeeeeery slow, 48=quickest
  //   - "0" means do not change the currentPalette at all; freeze
  //if (currentMillis % 4 == 0) {
  uint8_t maxChanges = 1;
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


void loadingPixelPattern(){
  
  if (fadeDirection == 1) {  //fade up
    EVERY_N_MILLISECONDS(3){
      fill_solid( leds, NUM_LEDS, CHSV(hue,sat,val) );
      fill_solid( leds2, NUM_LEDS, CHSV(hue,sat,val) );
      val = val + 1;
      if (val == 255) {
      }
    }
  }

  if (fadeDirection == 0) {  //fade down
    EVERY_N_MILLISECONDS(9){
      fill_solid( leds, NUM_LEDS, CHSV(hue,sat,val) );
      fill_solid( leds2, NUM_LEDS, CHSV(hue,sat,val) );
      val = val - 1;
      if (val == 0) {
        fadeDirection = !fadeDirection;  //reverse direction
      }
    }
  }
  
  FastLED.show();

  EVERY_N_MILLISECONDS(90){  //cycle around the color wheel over time
    hue++;
  }
  
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



/*

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



*/
