
void startAPserver(WiFiServer server) {
  Serial.println("Access Point Web Server");


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
  server.begin();

  Serial.print("Access Point Started! Hoorray!");
  // you're connected now, so print out the status
  printWiFiStatus();
  isAPActive = true;
}

void LoadAPClientPage(WiFiClient APclient) {
  Serial.println("new client");           // print a message out the serial port
  String currentLine = ""; // make a String to hold incoming data from the client
  while (APclient.connected()) {            // loop while the client's connected
    if (APclient.available()) {             // if there's bytes to read from the client,
      char c = APclient.read();

      Serial.write(c);                    // print it out the serial monitor
      if (c == '\n') {                    // if the byte is a newline character

        // if the current line is blank, you got two newline characters in a row.
        // that's the end of the client HTTP request, so send a response:
        if (currentLine.length() == 0) {
          // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
          // and a content-type so the client knows what's coming, then a blank line:
          APclient.println("HTTP/1.1 200 OK");
          APclient.println("Content-type:text/html");
          APclient.println();

          // HTTP Content
          APclient.println("<!DOCTYPE html><html>");
          APclient.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
          APclient.println("<link rel=\"icon\" href=\"data:,\">");

          // CSS

          APclient.println("<style>html { font-family: Helvetica; margin: 0px auto; text-align: center; background: rgb(88,0,209);color: rgb(255,255,255); background:linear-gradient( rgba(88,0,209,1) , rgba(221,12,12,1), rgba(255,167,0,1)); }");
          APclient.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
          APclient.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
          APclient.println(".inputDiv {display: flex; flex-direction:column;align-items: center;justify-content:space-evenly;}");
          APclient.println(".submitButton {background-color: #555555;}");
          APclient.println(".inputItem {display: flex;justify-content:space-evenly;}</style></head>");


          // HTML & JS
          APclient.println("<body><h1>Horizonte</h1>");
          APclient.println("<body><h3>Web Control UI</h3>");

          //Send the JS
          APclient.println("<p id='demo'></p>");
          APclient.println("<p id='time'></p>");
          APclient.println("<p id='data'></p>");

          APclient.println("<div class=\"inputDiv\">");
          APclient.println("<div class=\"inputItem\"><form action=\"/get\">SSID: <input type=\"/text\" name=\"input1\"></div>");
          APclient.println("<div class=\"inputItem\"><form action=\"/get\">password: <input type=\"/text\" name=\"input2\"></div>");
          APclient.println("<div class=\"inputItem\"><form action=\"/get\">lat: <input type=\"/text\" name=\"input3\"></div>");
          APclient.println("<div class=\"inputItem\"><form action=\"/get\">long: <input type=\"/text\" name=\"input4\"></div>");
          APclient.println("<div class=\"inputItem\"><form action=\"/get\">GMT <input type=\"/text\" name=\"input5\"></div>");
          APclient.println("<div class=\"submitButton\"><input type=\"submit\" value=\"submit\"><form></div>");






          //Render the time on screen
          APclient.println("<script>function currentGMTTimeInMillis(){const utcDate = new Date(Date.now()); const utcDateInMillis = Date.now();const timezoneOffset = utcDate.getTimezoneOffset();const GMTchangeInMillis = (timezoneOffset * -1) * 60 * 1000;const currentTimeInMillis = utcDateInMillis + GMTchangeInMillis;return currentTimeInMillis;}const myDate = new Date(currentGMTTimeInMillis()).toGMTString();console.log(currentGMTTimeInMillis()); console.log(myDate);</script>");
          APclient.println("<script>document.getElementById('data').innerHTML = `Time is :${myDate}`</script>");


          // Close the http
          APclient.println("</body></html>");


          // The HTTP response ends with another blank line:
          APclient.println();
          // break out of the while loop:
          break;
        }
        else {      // if you got a newline, then clear currentLine:
          currentLine = "";
        }
      }
      else if (c != '\n') {
        APdataString += c;//
      }
      else if (c != '\r') {    // if you got anything else but a carriage return character,
        currentLine += c;      // add it to the end of the currentLine
      }

    }
  }
  // close the connection:

  Serial.println("currentLine: ");
  Serial.println(APdataString);


  APclient.stop();
  Serial.println("client disconnected");
}

void processDataRequest(String readString) {

  //find start of servo command string (#)
  int ind1_start = readString.indexOf('=');
  int ind1_end = readString.indexOf('&');

  int ind2_start = readString.indexOf('=', ind1_start + 1);
  int ind2_end = readString.indexOf('&', ind1_end + 1);

  int ind3_start = readString.indexOf('=', ind2_start + 1);
  int  ind3_end = readString.indexOf('&', ind2_end + 1);

  int ind4_start = readString.indexOf('=', ind3_start + 1);
  int  ind4_end = readString.indexOf('&', ind3_end + 1);

  int ind5_start = readString.indexOf('=', ind4_start + 1);
   int ind5_end_1 = readString.indexOf('\n'); 
  int ind5_end = readString.indexOf('\n', ind5_end_1 + 1);

  //capture the values in the response string
  ssidString = readString.substring(ind1_start + 1, ind1_end);
  Serial.println(ssidString);
  passString = readString.substring(ind2_start + 1, ind2_end);
  Serial.println(passString);
  latString = readString.substring(ind3_start + 1, ind3_end);
  Serial.println(latString);
  longString = readString.substring(ind4_start + 1, ind4_end);
  Serial.println(longString);
  GMTString = readString.substring(ind5_start + 1, ind5_end);
  Serial.println(GMTString);


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
