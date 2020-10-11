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
#include "arduino_secrets.h"


///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS ;    // your network password (use for WPA, or use as key for WEP)
int status = WL_IDLE_STATUS;     // the WiFi radio's status

// Specify IP address or hostname
char server[] = "horizonte-api.herokuapp.com" ;//"192.168.1.152";
int port = 3000;

// Declare our WiFiNINA client
WiFiClient client;

// last time you connected to the server, in milliseconds
unsigned long lastConnectionTime = 0;
// delay between updates, in milliseconds
const unsigned long postingInterval = 10L * 1000L;
// Make a request every ten seconds
bool repeatRequest = false;


//////////////////////////////////////////////// NEOPIXEL ////////////////////////////////////////////////////////

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 4
#define NUMPIXELS 144
#define PIXELTYPE NEO_GRB + NEO_KHZ800

// Declare our first neopixel strip
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, PIXELTYPE);


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




int ind1; // , locations
int ind2;

char charArray[700];
String dataString;
const byte numChars = 32;
char receivedChars[numChars];   // an array to store the received data

boolean newData = false;
void setup() {

  // Initialize serial port:
  Serial.begin(9600);

  // attempt to connect to WiFi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);

    // wait 5 seconds for connection:
    delay(5000);
  }

  // you're connected now, so print out the data:
  Serial.println("You're connected to the network");
  //printWiFiData();

  rtc.begin();

  unsigned long epoch;
  int numberOfTries = 0, maxTries = 6;

  do {

    epoch = WiFi.getTime();
    numberOfTries++;

  }

  while ((epoch == 0) && (numberOfTries < maxTries));

  if (numberOfTries == maxTries) {
    //Cannot reach server
    Serial.print("NTP unreachable!!");

    while (1);
  }
  // Time received
  else {

    Serial.print("Epoch received: ");
    Serial.println(epoch);
    //set the epoc for the rtc
    rtc.setEpoch(epoch);

    Serial.println();

  }

  // If connect to server,send the GET request to our server.
  if (client.connect(server, 80)) {
    Serial.println("connected to Horizonte API");
    // Make a HTTP request:
    //client.println adds a /r/n/ at the end.
    client.println("GET /sun HTTP/1.1");
    client.println("Host: horizonte-api.herokuapp.com");
    client.println("Connection: close");
    client.println();
  }


  pixels.begin();
  pixels.setBrightness(40);
  pixels.show(); // Initialize all pixels to 'off'
}

void loop() {


  //Turn on the lights to indicate a connection
  //lightPulse(255, 0, 0, 20);

  // if you get a connection, report back via serial:
 while (client.available()) {
  char c = client.read();
  Serial.print(c);
  /*append(charArray, c);*/
 }

  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting from server.");
    client.stop();

    // do nothing forevermore:
    while (true);
  }
  //See the JSON stream
  /*ReadLoggingStream loggingStream(client, Serial);
    deserializeJson(doc, client);
    DeserializationError error = deserializeJson(doc, c);
    if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    return;
    }
    const char* sunset = doc["sunset"][0];*/
  /*
    //Zoomcat https://forum.arduino.cc/index.php?topic=387175.0
    Serial.print(c);
    ind1 = readString.indexOf('time:"');
    ind2 = readString.indexOf('', ind1+1);
    sunset = readString.substring(ind1+1, ind2+1);
*/
}

void recvWithStartEndMarkers(WiFiClient client) {
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '{';
  char endMarker = '}';
  char rc;

  while (client.available() > 0 && newData == false) {
    rc = client.read();

    if (recvInProgress == true) {
      if (rc != endMarker) {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      }
      else {
        receivedChars[ndx] = '\0'; // terminate the string
        recvInProgress = false;
        ndx = 0;
        newData = true;
      }
    }

    else if (rc == startMarker) {
      recvInProgress = true;
    }
  }
}

void showNewData() {
  if (newData == true) {
    Serial.print("This just in ... ");
    Serial.println(receivedChars);
    newData = false;
  }
}

void append(char* s, char c) {
  int len = strlen(s);
  s[len] = c;
  s[len + 1] = '\0';
}
// https://forum.arduino.cc/index.php?topic=553372.0
void charToString(char S[], String &D)
{

  String rc(S);
  D = rc;

}

// this method makes a HTTP connection to the server:
void httpRequest() {
  // close any connection before send a new request.
  // This will free the socket on the Nina module
  client.stop();

  // if there's a successful connection:
  if (client.connect(server, port)) {
    Serial.println("connected to server");
    // Make a HTTP request:
    client.println("GET /sun HTTP/1.1");
    client.println("Host: 192.168.1.152");
    client.println("Connection: close");
    client.println();

    // note the time that the connection was made:
    lastConnectionTime = millis();
  } else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
  }
}


void printWiFiData() {
  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP address : ");
  Serial.println(ip);

  Serial.print("Subnet mask: ");
  Serial.println((IPAddress)WiFi.subnetMask());

  Serial.print("Gateway IP : ");
  Serial.println((IPAddress)WiFi.gatewayIP());

}


// Make a dot travel the strip
void lightPulse(int r, int g, int b,  uint8_t wait) {
  for (uint16_t i = 0; i < pixels.numPixels(); i++) {
    pixels.setPixelColor(i, pixels.Color(r - (i * 10), g - (i * 10), b - (i * 10)));
    pixels.show();
    delay(wait);
  }
}


void configureHorizon(char startSunrise, char startNightTime, char currentTime) {
  /* int current = convertToMinutes(currentTime);
    int start = convertToMinutes(startSunrise);
    int end = convertToMinutes(startNightTime);


    int mainLed = map(current, start, end, 0 , pixels.numPixels());
    Serial.print(mainLed);*/
}


void print2digits(int number) {
  if (number < 10) {
    Serial.print("0");
  }
  Serial.print(number);
}

// receives time in a "HH:MM"" format
void convertToMinutes(char time[]) {

}

void printTime()
{
  Serial.println("TIME:");
  Serial.println("GMT:" + GMT);

  Serial.println();

  print2digits(rtc.getHours());
  Serial.print(":");
  print2digits(rtc.getMinutes());
  Serial.print(":");
  print2digits(rtc.getSeconds());

  Serial.println(" ");

}

void printDate()
{
  Serial.println("DATE:");
  Serial.println();

  Serial.print(rtc.getDay());
  Serial.print("/");
  Serial.print(rtc.getMonth());
  Serial.print("/");
  Serial.print(rtc.getYear());

  Serial.println(" ");
}
