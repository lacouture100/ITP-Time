/*
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
  <head>
  <title>ESP Input Form</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
  .button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;
  text-decoration: none; font-size: 30px; margin: 2px; cursor: pointe}
  client.println(".button2 {background-color: #555555;}
  </style>
  </head>;
  
  <body>
  <form action="/get">
    Network Name: <input type="text" name="ssid">
    <input type="submit" value="Submit">
  </form><br>
  <form action="/get">
    Password: <input type="text" name="password">
    <input type="submit" value="Submit">
  </form><br>
  <form action="/get">
    input3: <input type="text" name="input3">
    <input type="submit" value="Submit">
  </form>
</body></html>)rawliteral";

void APloadPage(WiFiClient client) {

  // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
  // and a content-type so the client knows what's coming, then a blank line:
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println();

  // the content of the HTTP response follows the header /////////////////////////////////////////////////
  client.println("<!DOCTYPE html><html>");
  client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  client.println("<link rel=\"icon\" href=\"data:,\">");

  // CSS to style the on/off buttons
  // Feel free to change the background-color and font-size attributes to fit your preferences
  client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
  client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
  client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
  client.println(".button2 {background-color: #555555;}</style></head>");

  // Web Page Heading
  client.println("<body><h1>ESP32 Web Server</h1>");

  //Send the JS
    client.println("<button id='button'></button>");
  client.println("<button id='button2'></button>");
  client.println("<p id='demo'></p>");
  client.println("<p id='time'></p>");
  client.println("<script>document.getElementById('demo').innerHTML = 'Hello JavaScript!'</script>");
  client.println("<script>document.getElementById('demo').innerHTML = `${Date.now()}`</script>");


              // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/H\">here</a> turn the LED on<br>");
            client.print("Click <a href=\"/L\">here</a> turn the LED off<br>");

            

  // Close the http
  client.println("</body></html>");
}*/
