/**
* Copyright 2016 Michael Heijmans
*
* A simple sketch for controlling the jumping prop trigger
*
* Author::    Michael Heijmans  (parabuzzle@gmail.com)
* Copyright:: Copyright (c) 2016 Michael Heijmans
* License::   MIT
*/

const int sensorPin     = 3;
const int relayPin      = 2;

const int waitBeforeRun = 500;
const int waitForReset  = 18000; //prop runs for 15 seconds and the circuit reset is another 2 seconds

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
    delay(waitBeforeRun);
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
