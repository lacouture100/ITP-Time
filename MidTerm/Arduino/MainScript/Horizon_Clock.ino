

void configureHorizon(int GMT) {
  long GMTchangeInMillis = GMT * 60 * 60 * 1000;
  long totalDayTime = duskMillis - dawnMillis;
  //long currentTime = duskMillis;
  long currentTime = currentTimeToMillis();
  currentTime += GMTchangeInMillis;

  int numberOfPixels = 144;
  long millisPerPixel = round(totalDayTime / numberOfPixels);
  int currentPixel = round((currentTime - dawnMillis) / millisPerPixel);
  Serial.println("Total Day Time : ");
  Serial.println(totalDayTime);
  Serial.println("Current Day Time : ");
  Serial.println(currentTime);
  Serial.println("Current Pixel : ");
  Serial.println(currentPixel);
  Serial.println("Millis per pixel : ");
  Serial.println(millisPerPixel);


  /*
    int mainLed = map(current, start, end, 0 , pixels.numPixels());
    Serial.print(mainLed);*/
}
