/*
  WiFi AP mode

  This sketch creates an access point without internet
  that other devices can connect to. Once connected, 
  they can access a web server hosted on the board, and
  control an LED from the browser.
  
  Based on the WiFiNINA library.

  (c) 2020 K. Söderby for Arduino
*/

#include <WiFiNINA.h>

char ssid[] = "yourNetwork";        // your network SSID (name)
char pass[] = "yourPassword";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                // your network key Index number (needed only for WEP)

int led =  LED_BUILTIN;
int status = WL_IDLE_STATUS;
WiFiServer APserver(80);

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  Serial.println("Access Point Web Server");


  // print the network name (SSID);
  Serial.print("Creating access point named: ");
  Serial.println(ssid);

  // Create open network. Change this line if you want to create an WEP network:
  status = WiFi.beginAP(ssid, pass);
  if (status != WL_AP_LISTENING) {
    Serial.println("Creating access point failed");
    // don't continue
    while (true);
  }

  // wait 10 seconds for connection:
  delay(1000);

  // start the web server on port 80
  APserver.begin();

  Serial.print("Access Point Started! Hoorray!");
  // you're connected now, so print out the status
  printWiFiStatus();
}


void loop() {
  // compare the previous status to the current status
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

  WiFiClient client = APserver.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
         if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header /////////////////////////////////////////////////
            client.println("<!DOCTYPE html><html>");
            client.println("Content-type:text/html");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center; background: rgb(88,0,209);background: linear-gradient(90deg, rgba(88,0,209,1) 0%, rgba(221,12,12,1) 35%, rgba(255,167,0,1) 100%); }");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}");
            client.println(".inputDiv {display: flex; flex-direction:column;justify-content: space-evenly;}");
            client.println(".inputItem {display: flex;}</style></head>");

            // Web Page Heading
            client.println("<body><h1>Horizonte Web Control</h1>");

            //Send the JS
            client.println("<p id='demo'></p>");
            client.println("<p id='time'></p>");
            client.println("<p id='data'></p>");

            client.println("<div class=\"inputDiv\">");
            client.println("<div class=\"inputItem\"><form action=\"/get\">SSID: <input type=\"/text\" name=\"input1\"></div>");
            client.println("<div class=\"inputItem\"><form action=\"/get\">password: <input type=\"/text\" name=\"input2\"></div>");
            client.println("<div class=\"inputItem\"><form action=\"/get\">lat: <input type=\"/text\" name=\"input3\"></div>");
            client.println("<div class=\"inputItem\"><form action=\"/get\">long: <input type=\"/text\" name=\"input4\"</div>>");
            client.println("<div class=\"inputItem\"><input type=\"submit\" value=\"submit\"><form></div>");

            client.println("<script>let utcDate = new Date(Date.now()).toGMTString();</script>");
            client.println("<script>let cleanTime = utcDate.slice(17,25);</script>");
            client.println("<script>console.log(utcDate)</script>");
            client.println("<script>let gmt = utcDate.slice(30,34);</script>");
            client.println("<script>document.getElementById('data').innerHTML = `${cleanTime} + GMT: ${gmt}`</script>");


            // Close the http
            client.println("</body></html>");


            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          }
          else {      // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        }
        else if (c != '\r') {    // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(led, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(led, LOW);                // GET /L turns the LED off
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}


void startAPserver(WiFiServer server) {
  Serial.println("Access Point Web Server");


  // print the network name (SSID);
  Serial.print("Creating access point named: ");
  Serial.println(ssid);

  // Create open network. Change this line if you want to create an WEP network:
  status = WiFi.beginAP(ssid, pass);
  if (status != WL_AP_LISTENING) {
    Serial.println("Creating access point failed");
    // don't continue
    while (true);
  }

  // wait 10 seconds for connection:
  delay(1000);

  // start the web server on port 80
  server.begin();

  Serial.print("Access Point Started! Hoorray!");
  // you're connected now, so print out the status
  printWiFiStatus();

}

void APServerListen(WiFiServer server) {
  // compare the previous status to the current status
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

  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header /////////////////////////////////////////////////
            client.println("<!DOCTYPE html><html>");
            client.println("Content-type:text/html");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center; background: rgb(88,0,209);background: linear-gradient(90deg, rgba(88,0,209,1) 0%, rgba(221,12,12,1) 35%, rgba(255,167,0,1) 100%); }");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}");
            client.println(".inputDiv {display: flex; flex-direction:column;justify-content: space-evenly;}");
            client.println(".inputItem {display: flex;}</style></head>");

            // Web Page Heading
            client.println("<body><h1>Horizonte Web Control</h1>");

            //Send the JS
            client.println("<p id='demo'></p>");
            client.println("<p id='time'></p>");
            client.println("<p id='data'></p>");

            client.println("<div class=\"inputDiv\">");
            client.println("<div class=\"inputItem\"><form action=\"/get\">SSID: <input type=\"/text\" name=\"input1\"></div>");
            client.println("<div class=\"inputItem\"><form action=\"/get\">password: <input type=\"/text\" name=\"input2\"></div>");
            client.println("<div class=\"inputItem\"><form action=\"/get\">lat: <input type=\"/text\" name=\"input3\"></div>");
            client.println("<div class=\"inputItem\"><form action=\"/get\">long: <input type=\"/text\" name=\"input4\"</div>>");
            client.println("<div class=\"inputItem\"><input type=\"submit\" value=\"submit\"><form></div>");

            client.println("<script>let utcDate = new Date(Date.now()).toGMTString();</script>");
            client.println("<script>let cleanTime = utcDate.slice(17,25);</script>");
            client.println("<script>console.log(utcDate)</script>");
            client.println("<script>let gmt = utcDate.slice(30,34);</script>");
            client.println("<script>document.getElementById('data').innerHTML = `${cleanTime} + GMT: ${gmt}`</script>");


            // Close the http
            client.println("</body></html>");


            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          }
          else {      // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        }
        else if (c != '\r') {    // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}


void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);

}
