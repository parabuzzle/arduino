/**
* Copyright 2016 Michael Heijmans
*
* A simple sketch for controlling the trigger for an electric firecracker
*
* Author::    Michael Heijmans  (parabuzzle@gmail.com)
* Copyright:: Copyright (c) 2016 Michael Heijmans
* License::   MIT
*/

/**
*  Sensor
*
*  RED   - Vcc
*  GRAY  - GND
*  WHITE - Sense
*/
const int sensorPin    = 3;

const int relayPin     = 2;

const int runTime      = 2000;
const int waitForReset = 11000;

int sensorState = 0;
int logState    = 0;

void setupSerialLogging() {
  Serial.begin(9600);
  Serial.println("--- Start Serial Monitor SEND_RCVE ---");
  Serial.println();
}

void setup() {
  pinMode(relayPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  setupSerialLogging();
}

void loop() {
  sensorState = digitalRead(sensorPin);

  if (sensorState == HIGH) {
    if ( logState == 0 ) {
      Serial.println("Sensor sees something");
      logState = 1;
    }
    digitalWrite(relayPin, HIGH);
    delay(runTime);
    digitalWrite(relayPin, LOW);
    delay(waitForReset);
  } else {
    digitalWrite(relayPin, LOW);
    if ( logState == 1 ) {
      Serial.println("Nothing seen, going to sleep");
      logState = 0;
    }
  }

}
