

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
  lightPulse(pixels1, 0, 0, 255, 20);

  apiHttpRequest(myDataObject);
  Serial.println("dawnMillis :");
Serial.println(dawnMillis);
  //configureHorizon(-4);

  //ReadSD();

  lightPulse(pixels2, sunriseR, sunriseG, sunriseB, 20);

  lightPulse(pixels1, duskR, duskG, duskB, 20);


}
