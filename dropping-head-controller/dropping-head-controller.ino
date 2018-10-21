/**
* Copyright 2016 Rotting Orchards Haunted Consulting
*
* A simple sketch for controlling dropping head pneumatic prop
*
* Author::    Michael Heijmans  (parabuzzle@gmail.com)
* Copyright:: Copyright (c) 2016 Rotting Orchards Haunted Consulting
* License::   MIT
*/

const int sensorPin       = 3;
const int relayPin        = 2;

const int resetTime       = 10000;
const int waitBeforeDrop  = 100;
const int waitBeforeReset = 3000;

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

void waitForReset() {
  delay(resetTime);
}

void dropRoutine() {
  delay(waitBeforeDrop);
  digitalWrite(relayPin, HIGH);
  delay(waitBeforeReset);
  digitalWrite(relayPin, LOW);
  waitForReset();
}

void loop() {
  sensorState = digitalRead(sensorPin);

  if (sensorState == HIGH) {
    if ( logState == 0 ) {
      Serial.println("Sensor sees something");
      logState = 1;
    }
    Serial.println("Running dropRoutine");
    dropRoutine();
  } else {
    digitalWrite(relayPin, LOW);
    if ( logState == 1 ) {
      Serial.println("Nothing seen, going to sleep");
      logState = 0;
    }
  }
}
