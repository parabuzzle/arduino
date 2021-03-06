/**
* Copyright 2016 Rotting Orchards Haunted Consulting
*
* A simple sketch for signaling when the drop panel should be dropped
*
* Author::    Michael Heijmans  (parabuzzle@gmail.com)
* Copyright:: Copyright (c) 2016 Rotting Orchards Haunted Consulting
* License::   MIT
*/

/**
*  Sensor
*
*  WHITE  - Vcc
*  YELLOW - GND
*  GREEN  - Sense
*/
const int sensorPin     = 3;
const int sensorPwrPin  = 2;
const int ledPin        = 4;

const int resetTime     = 5000;

int sensorState = 0;
int logState    = 0;

void setupSerialLogging() {
  Serial.begin(9600);
  Serial.println("--- Start Serial Monitor SEND_RCVE ---");
  Serial.println();
}

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(sensorPwrPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  digitalWrite(sensorPwrPin, HIGH);
  setupSerialLogging();
}

void loop() {
  sensorState = digitalRead(sensorPin);

  if (sensorState == HIGH) {
    if ( logState == 0 ) {
      Serial.println("Sensor sees something");
      logState = 1;
    }
    digitalWrite(ledPin, HIGH);
    delay(resetTime);
  } else {
    digitalWrite(ledPin, LOW);
    if ( logState == 1 ) {
      Serial.println("Nothing seen, going to sleep");
      logState = 0;
    }
  }
}
