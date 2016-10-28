/**
* Copyright 2016 Michael Heijmans
*
* A simple sketch for controlling dropping head pneumatic prop
*
* Author::    Michael Heijmans  (parabuzzle@gmail.com)
* Copyright:: Copyright (c) 2016 Michael Heijmans
* License::   MIT
*/

const int sensorPin     = 3;
const int relayPin      = 2;

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

void dropRoutine() {
  delay(1000);
  digitalWrite(relayPin, HIGH);
  delay(3000);
  digitalWrite(relayPin, LOW);
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
