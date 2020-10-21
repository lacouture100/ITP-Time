

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


// No need for preset WiFi here.
//char ssid[] = SECRET_SSID;        // your network SSID (name)
//char pass[] = SECRET_PASS ;    // your network password (use for WPA, or use as key for WEP)
int status = WL_IDLE_STATUS;     // the WiFi radio's status


// Specify IP address or hostname
char server[] = "horizonte-api.herokuapp.com" ; // Horizonte clock API website
int port = 80;

// Declare our WiFiNINA client - GET the requests
WiFiClient client;
HttpClient httpclient = HttpClient(client, server, port);

// Declare our server for the AP point
WiFiServer APserver(80);

//Set Access point name and password
char APssid[] = "horizonteWeb";        // your network SSID (name)
char APpass[] = "yourTime";    // your network password (use for WPA, or use as key for WEP)


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

// Initial Palettes
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

//Debug messages for each sun time
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

// Loading pattern values
uint8_t hue = 0;
uint8_t sat = 255;
uint8_t val = 0;
boolean fadeDirection = 1;

//////////////////////////////////////////////// ArduinoJSON ////////////////////////////////////////////////////////

#include <ArduinoJson.h>

StaticJsonDocument<200> doc;
//char json[] = "";

//////////////////////////////////////////////// RTC ////////////////////////////////////////////////////////

#include <RTCZero.h>
RTCZero rtc;
//const int GMT = -4; //change this to adapt it to your time zone


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
bool gotCredentials = false;
boolean newData = false;

long currentTimeOfDay = 0;



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

  // start the web server on port 80
  APserver.begin();

  // you're connected now, so print out the status
  printWiFiStatus();

  //Start the SD Card
  //startSDCard();

  //Start the neopixels
  startPixels();
}

void loop() {
  ///////////////////  ACCESS POINT  /////////////////////

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

  // Read the SD card to see when was the latest data
  //ReadSD();

  // If we have no credentials saved
  if (gotCredentials == false) {
    // Load the Access Point
    LoadAPClientPage(APclient);
    // If we have no data, proceed to make the request
    if (APdataString != "") {
      processDataRequest(APdataString);
      // If we get the data, process and obtain our credentials
      if (ssidString != "" && passString != "" && latString != "" && longString != "" && GMTString != "") {
        gotCredentials = true;
      }
    }
  }

  ////////////  HTTP GET REQUEST TO HORIZONTE API ////////////

  // If we have credentials, atttempt WiFi connection to make the time data request
  if (gotCredentials) {

    // attempt to connect to WiFi network:
    while ( status != WL_CONNECTED ) {
      Serial.print("Attempting to connect to WPA SSID: ");
      Serial.println(ssidString);

      // Connect to WPA/WPA2 network:
      char ssidChar[ssidString.length()];
      char passChar[passString.length()];
      ssidString.toCharArray(ssidChar, ssidString.length() + 1);
      passString.toCharArray(passChar, passString.length() + 1);
      Serial.println("ssidChar: ");
      Serial.print(ssidChar);
      Serial.println("passChar: ");
      Serial.print(passChar);

      // Start the connection
      status = WiFi.begin(ssidChar, passChar);

      // wait 5 seconds for connection:
      delay(5000);
    }

    // you're connected now, so print out the data:
    Serial.println("You're connected to the network: ");
    Serial.println(ssidString);

    // Check we are connected to the server
    if (client.connect(server, 80)) {
      Serial.println("connected to Horizonte API");
    }
    
    // While there is no data for our time, make a request for Data to our sever
    while (!dawnMillis) {
      apiSunTimesRequest(myDataObject);
    }
    if (currentTimeOfDay == 0) {
      // If it is midnight, or our time has not been set, make a request to the server to update our time.
      apiCurrentTimeRequest();

    }

    // Set the incoming time-of-day value as our epoch
    rtc.setEpoch(currentTimeOfDay);
    currentTimeToMillis();

    //printTime();
    //printDate();

  }

  // Set the lights to their appropriate color
  if (currentTimeOfDay != 0) {
    runLights(currentTimeOfDay , dawnMillis, sunriseMillis, sunriseEndMillis, goldenHourEndMillis, solarNoonMillis, goldenHourMillis, sunsetStartMillis, sunsetMillis, nightMillis);
  }
  if (currentTimeOfDay >= 86400000) {
    currentTimeOfDay = 0;
  }
    Serial.println("Finished Initial Loop!");
}
