JSONVar apiHttpRequest(JSONVar myDataObject) {
  // assemble the path for the GET message:
  String path = "/sun";

  // send the GET request
  Serial.println("making GET request");
  httpclient.get(path);

  // read the status code and body of the response
  int statusCode = httpclient.responseStatusCode();
  String response = httpclient.responseBody();
  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);

  //Write the Data to the SD Card
  //writeToSD(response);
  
  
  // parse the string into a JSONVar object:
  myDataObject = JSON.parse(response);
  // myDataObject.keys() can be used to get an array
  // of all the keys in the object
  JSONVar keys = myDataObject.keys();

  //Set the time variables
  sunrise = myDataObject["sunrise"];
  night = myDataObject["night"];

  //Set the events
  //dawn, sunrise, sunriseEnd, goldenHourEnd, solarNoon, goldenHour, sunsetStart, sunset, dusk, night

  dawnMillis = myDataObject["dawn"]["time"]["ms"];
  sunriseMillis = myDataObject["sunrise"]["time"]["ms"];
  sunriseEndMillis = myDataObject["sunriseEnd"]["time"]["ms"];
  goldenHourEndMillis = myDataObject["goldenHourEnd"]["time"]["ms"];
  solarNoonMillis = myDataObject["solarNoon"]["time"]["ms"];
  goldenHourMillis = myDataObject["goldenHour"]["time"]["ms"];
  sunsetStartMillis = myDataObject["sunsetStart"]["time"]["ms"];
  sunsetMillis = myDataObject["sunset"]["time"]["ms"];
  duskMillis = myDataObject["dusk"]["time"]["ms"];
  nightMillis = myDataObject["night"]["time"]["ms"];
  

  // Set the color for each event
  dawnR = myDataObject["dawn"]["color1"]["r"];
  dawnG = myDataObject["dawn"]["color1"]["g"];
  dawnB = myDataObject["dawn"]["color1"]["b"];

  sunriseR = myDataObject["sunrise"]["color1"]["r"];
  sunriseG = myDataObject["sunrise"]["color1"]["g"];
  sunriseB = myDataObject["sunrise"]["color1"]["b"];

  sunriseEndR = myDataObject["sunriseEnd"]["color1"]["r"];
  sunriseEndG = myDataObject["sunriseEnd"]["color1"]["g"];
  sunriseEndB = myDataObject["sunriseEnd"]["color1"]["b"];

  goldenHourEndR = myDataObject["goldenHourEnd"]["color1"]["r"];
  goldenHourEndG = myDataObject["goldenHourEnd"]["color1"]["g"];
  goldenHourEndB = myDataObject["goldenHourEnd"]["color1"]["b"];

  solarNoonR = myDataObject["solarNoon"]["color1"]["r"];
  solarNoonG = myDataObject["solarNoon"]["color1"]["g"];
  solarNoonB = myDataObject["solarNoon"]["color1"]["b"];

  goldenHourR = myDataObject["goldenHour"]["color1"]["r"];
  goldenHourG = myDataObject["goldenHour"]["color1"]["g"];
  goldenHourB = myDataObject["goldenHour"]["color1"]["b"];

  sunsetStartR = myDataObject["sunsetStart"]["color1"]["r"];
  sunsetStartG = myDataObject["sunsetStart"]["color1"]["g"];
  sunsetStartB = myDataObject["sunsetStart"]["color1"]["b"];

  sunsetR = myDataObject["sunset"]["color1"]["r"];
  sunsetG = myDataObject["sunset"]["color1"]["g"];
  sunsetB = myDataObject["sunset"]["color1"]["b"];

  duskR = myDataObject["dusk"]["color1"]["r"];
  duskG = myDataObject["dusk"]["color1"]["g"];
  duskB = myDataObject["dusk"]["color1"]["b"];

  nightR = myDataObject["night"]["color1"]["r"];
  nightG = myDataObject["night"]["color1"]["g"];
  nightB = myDataObject["night"]["color1"]["b"];

  // read over the object, one key at a time:
  for (int i = 0; i < keys.length(); i++) {
    JSONVar value = myDataObject[keys[i]];
    // what's the key:
    Serial.println("Keys in the request");
    Serial.print(keys[i]);
    Serial.print("\t");
    // and what's the value of the key:
    Serial.print(value);
    // and what's the type of the value:
    Serial.print("\ttype: ");
    Serial.println(JSON.typeof(value));

    //setTimeData(myDataObject);
    return  myDataObject;
  }
}
