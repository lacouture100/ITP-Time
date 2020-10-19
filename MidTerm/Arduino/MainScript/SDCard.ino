void startSDCard() {
  Serial.print("Initializing SD card...");
  if (!SD.begin(4)) {
    Serial.println("SD Card initialization failed!");
  }
  Serial.println("SD Card initialization done.");
}


void writeToSD(String data) {
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("data.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing API data to data.txt...");
    myFile.print(currentDateString());
    myFile.print("-");
    myFile.print(currentTimeString());
    myFile.print("_");
    myFile.println(data);
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening data.txt");
  }

}

void ReadSD() {
  // re-open the file for reading:
  myFile = SD.open("data.txt");
  if (myFile) {
    Serial.println("data.txt contains :");
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      //Serial.write(myFile.read());
      Serial.println("LASTLINE: ");
      printLastLine(myFile);
    }
  }
}

void printLastLine(File myFile) {
  myFile.seek(0);
  char cr;
  unsigned int lineCounter = 0;
  for (unsigned int i = 0; i < (myFile.size()); i++) {
    cr = myFile.read();
    if (cr == '\n') {
      lineCounter++;
    }
  }
  printLineNumber(lineCounter);
}



void printLineNumber(unsigned int lineNumber) {
  myFile.seek(0);
  char cr;

  for (unsigned int i = 0; i < (lineNumber - 1);) {
    cr = myFile.read();
    if (cr == '\n') {
      i++;
    }
  }

  //Now we are at the right line
  while (true) {
    cr = myFile.read();
    Serial.write(cr);
    if (cr == '\n') {
      break;
    }
  }
  //a for loop with a read limit might be a good idea
}
