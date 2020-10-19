

/*

  This script controls the Horizonte Clock developed by Alvaro Lacouture.

  Circuit:
    Board with NINA module (Arduino MKR WiFi 1010), 2 X NeoPixels 144 RGBW strip, Micro SD-Card Reader HW-125)

  created 11 October 2020
  by Alvaro Lacouture(lacouture100@gmail.com)
*/
//////////////////////////////////////////////// DEBUG ////////////////////////////////////////////////////////

char separator[] = "------------------------------------------------------------";

//////////////////////////////////////////////// WIFI ////////////////////////////////////////////////////////

#include <SPI.h>
#include <WiFiNINA.h>
#include <StreamUtils.h>
#include <ArduinoHttpClient.h>

#include "arduino_secrets.h"


///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS ;    // your network password (use for WPA, or use as key for WEP)
int status = WL_IDLE_STATUS;     // the WiFi radio's status


// Specify IP address or hostname
char server[] = "horizonte-api.herokuapp.com" ;//"192.168.1.152";
int port = 80;

// Declare our WiFiNINA client - GET the requests
WiFiClient client;
HttpClient httpclient = HttpClient(client, server, port);

// Declare our server for the AP point
WiFiServer APserver(80);
char APssid[] = "HorizonClockAP";        // your network SSID (name)
char APpass[] = "yeahbaby";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                // your network key Index number (needed only for WEP)

// last time you connected to the server, in milliseconds
unsigned long lastConnectionTime = 0;
// delay between updates, in milliseconds
const unsigned long postingInterval = 10L * 1000L;
// Make a request every ten seconds
bool repeatRequest = false;

bool isAPActive = false;

unsigned int textLineCounter = 0;


//////////////////////////////////////////////// NEOPIXEL ////////////////////////////////////////////////////////
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



int minuteDelay = 60000;
int hourDelay = 3600000;
int count = 0;

//////////////////////////////////////////////// ArduinoJSON ////////////////////////////////////////////////////////

#include <ArduinoJson.h>

StaticJsonDocument<200> doc;
//char json[] = "";

//////////////////////////////////////////////// RTC ////////////////////////////////////////////////////////

#include <RTCZero.h>
RTCZero rtc;
const int GMT = -4; //change this to adapt it to your time zone


//////////////////////////////////////////////// SDCard ////////////////////////////////////////////////////////

#include <SPI.h>
#include <SD.h>

File myFile;


////////////////////////////////////////////// ArduinoJSON ////////////////////////////////////////////////////
#include <Arduino_JSON.h>

JSONVar myDataObject;

JSONVar sunrise;
JSONVar night;

//dawn, sunrise, sunriseEnd, goldenHourEnd, solarNoon, goldenHour, sunsetStart, sunset, dusk, night
int dawnR, dawnG, dawnB;
int sunriseR, sunriseG, sunriseB;
int sunriseEndR, sunriseEndG, sunriseEndB;
int goldenHourEndR, goldenHourEndG, goldenHourEndB;
int solarNoonR, solarNoonG, solarNoonB;
int goldenHourR, goldenHourG, goldenHourB;
int sunsetStartR, sunsetStartG, sunsetStartB;
int sunsetR, sunsetG, sunsetB;
int duskR, duskG, duskB;
int nightR, nightG, nightB;
long dawnMillis, sunriseMillis, sunriseEndMillis, goldenHourEndMillis, solarNoonMillis, goldenHourMillis, sunsetStartMillis, sunsetMillis, duskMillis, nightMillis;


//////////////////////////////////////////////    Math    ////////////////////////////////////////////////////

#include <math.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ind1; // , locations
int ind2;

String APdataString = "";
String ssidString = "";

String  passString = "";

String  latString = "";
String  longString = "";
String  GMTString = "";
boolean newData = false;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {

  // Initialize serial port:
  Serial.begin(9600);

  Serial.println("Access Point Web Server");


  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }
/*
  // print the network name (SSID);
  Serial.print("Creating access point named: ");
  Serial.println(APssid);

  // Create open network. Change this line if you want to create an WEP network:
  status = WiFi.beginAP(APssid, APpass);
  if (status != WL_AP_LISTENING) {
    Serial.println("Creating access point failed");
    // don't continue
    while (true);
  }

  // wait 10 seconds for connection:
  delay(1000);
*/
  // start the web server on port 80
  //APserver.begin();

  // you're connected now, so print out the status
  printWiFiStatus();

  
    // attempt to connect to WiFi network:
    while ( status != WL_CONNECTED ) {
      Serial.print("Attempting to connect to WPA SSID: ");
      Serial.println(ssid);
      // Connect to WPA/WPA2 network:
      status = WiFi.begin(ssid, pass);

      // wait 5 seconds for connection:
      delay(5000);
    }
 
  // you're connected now, so print out the data:
  Serial.println("You're connected to the network");

  
  rtcGetTime();
  //printTime();
  //printDate();
  //startSDCard();

  /*// If connect to server,send the GET request to our server.
    if (client.connect(server, 80)) {
    Serial.println("connected to Horizonte API");
    //
    }
  */
  startPixels();
}

void loop() {
/*
  if (status != WiFi.status()) {
    // it has changed update the variable
    status = WiFi.status();

    if (status == WL_AP_CONNECTED) {
      // a device has connected to the AP
      Serial.println("Device connected to AP");
    } else {
      // a device has disconnected from the AP, and we are back in listening mode
      Serial.println("Device disconnected from AP");
    }
  }

  WiFiClient APclient = APserver.available();   // listen for incoming clients

  // if you get a client,
  


  if (APdataString != "") {
    processDataRequest(APdataString);

  } else {
    LoadAPClientPage(APclient);
  }

  */

  //Turn on the lights to indicate a connection
  //lightPulse(pixels1, 0, 0, 255, 20);
  while(!dawnMillis){
     apiHttpRequest(myDataObject);
  }
 
  Serial.println("dawnMillis :");
  Serial.println(dawnMillis);


  runLights(currentTimeToMillis() , dawnMillis, sunriseMillis, sunriseEndMillis, goldenHourEndMillis, solarNoonMillis, goldenHourMillis, sunsetStartMillis, sunsetMillis, nightMillis);
  
  //configureHorizon(-4);

  //ReadSD();

  //lightPulse(pixels2, sunriseR, sunriseG, sunriseB, 20);

  //lightPulse(pixels1, duskR, duskG, duskB, 20);


}
