/**
* Copyright 2016 Michael Heijmans
*
* A simple sketch for signaling when the drop panel should be dropped
*
* Author::    Michael Heijmans  (parabuzzle@gmail.com)
* Copyright:: Copyright (c) 2016 Michael Heijmans
* License::   MIT
*/

const int relayPin  = 2;

const int fogTime   = 30000;
const int sleepTime = 60000;

int logState    = 0;

void setupSerialLogging() {
  Serial.begin(9600);
  Serial.println("--- Start Serial Monitor SEND_RCVE ---");
  Serial.println();
}

void setup() {
  pinMode(relayPin, OUTPUT);
  setupSerialLogging();
}

void runFog() {
  Serial.println("Running Fog");
  digitalWrite(relayPin, HIGH);
  delay(fogTime);
  digitalWrite(relayPin, LOW);
}

void loop() {
  runFog();
  Serial.println("Fog finished... sleeping");
  delay(sleepTime);
}
