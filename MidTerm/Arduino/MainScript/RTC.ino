void rtcGetTime() {
  rtc.begin();
  unsigned long epoch;
  int hours = 0;
  int numberOfTries = 0, maxTries = 10;

  do {
    epoch = WiFi.getTime();
    numberOfTries++;
    delay(10);
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
}

long unsigned currentTimeToMillis() {
  //rtcGetTime();
  // Current hour * 60 minutes per hour * 60 seconds per minute * 1000 milliseconds per minute.
  long unsigned hoursInMillis = rtc.getHours() * 60 * 60 * 1000;
  // Current hour * 60 seconds per minute * 1000 milliseconds per minute.
  long unsigned minutesInMillis = rtc.getMinutes() * 60 * 1000;
  // Current hour * 1000 milliseconds per minute.
  long unsigned secondsInMillis = rtc.getSeconds() * 1000;
  long unsigned currentTimeInMillis = hoursInMillis + minutesInMillis + secondsInMillis;
  Serial.println("Current Time in milllis");
  Serial.println(currentTimeInMillis);
  return currentTimeInMillis;
}

long unsigned timeToMillis(String time) {

  rtcGetTime();
  // Time enters in a HH:MM:SS format, and exits as amount of milliseconds which have passed since midnight, or 00:00:00
  //Convert hours to number
  String hours = time.substring(0, 2);
  int hoursInt = hours.toInt();
  //Convert minutes to number
  String minutes = time.substring(3, 5);
  int minutesInt = minutes.toInt();
  //Convert seconds to number
  String seconds = time.substring(0, 2);
  int secondsInt = seconds.toInt();

  // Current hour * 60 minutes per hour * 60 seconds per minute * 1000 milliseconds per minute.
  long unsigned hoursInMillis = hoursInt * 60 * 60 * 1000;
  // Current hour * 60 seconds per minute * 1000 milliseconds per minute.
  long unsigned minutesInMillis = minutesInt * 60 * 1000;
  // Current hour * 1000 milliseconds per minute.
  long unsigned secondsInMillis = secondsInt * 1000;
  long unsigned TimeInMillis = hoursInMillis + minutesInMillis + secondsInMillis;
  return TimeInMillis;
}

void printTime()
{
  Serial.print("TIME:");

  print2digits(rtc.getHours());
  Serial.print(":");
  print2digits(rtc.getMinutes());
  Serial.print(":");
  print2digits(rtc.getSeconds());

  Serial.println(" ");
}


void printDate()
{
  Serial.print("DATE:");

  Serial.print(rtc.getDay());
  Serial.print("/");
  Serial.print(rtc.getMonth());
  Serial.print("/");
  Serial.print(rtc.getYear());

  Serial.println(" ");
}

void print2digits(int number) {
  if (number < 10) {
    Serial.print("0");
  }
  Serial.print(number);
}

// get currentTime String
String currentDateString() {
  String dateString = String(rtc.getYear()) + "/" + String(rtc.getMonth()) + "/" + String(rtc.getDay());
  return dateString;
}
// get currentTime String
String currentTimeString() {
  String timeString = String(rtc.getHours()) + ":" + String(rtc.getMinutes()) + ":" + String(rtc.getSeconds());
  return timeString;
}
