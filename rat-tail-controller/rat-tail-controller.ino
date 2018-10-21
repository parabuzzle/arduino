/**
* Copyright 2016 Rotting Orchards Haunted Consulting
*
* A simple sketch for controlling the rat tails pneumatic prop
*
* Author::    Michael Heijmans  (parabuzzle@gmail.com)
* Copyright:: Copyright (c) 2016 Rotting Orchards Haunted Consulting
* License::   MIT
*/

/**
*  Sensor
*
*  GREEN  - Vcc
*  PURPLE - GND
*  BLUE   - Sense
*/
const int sensorPin     = 3;

/**
*  Relay
*
*  RED    - 12v (when active)
*  ORANGE - GND
*/
const int relayPin      = 2;

const int maxTailWhips  = 5;

int sensorState = 0;
int logState    = 0;
int tailWhips   = 0;

void setupSerialLogging() {
  Serial.begin(9600);
  Serial.println("--- Start Serial Monitor SEND_RCVE ---");
  Serial.println();
}

void setup() {
  pinMode(relayPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  setupSerialLogging();
  randomSeed(analogRead(0));
}å


void tailWhipRoutine() {
  digitalWrite(relayPin, HIGH);
  delay(random(100,400));
  digitalWrite(relayPin, LOW);
  delay(random(200, 500));

  digitalWrite(relayPin, HIGH);
  delay(random(100,400));
  digitalWrite(relayPin, LOW);
  delay(random(200, 500));

  digitalWrite(relayPin, HIGH);
  delay(random(100,400));
  digitalWrite(relayPin, LOW);
}

void loop() {
  sensorState = digitalRead(sensorPin);

  if (sensorState == HIGH) {
    if ( logState == 0 ) {
      Serial.println("Sensor sees something");
      logState = 1;
    }

    tailWhips = 0;
    Serial.println("Running tailWhipRoutine");
    while( tailWhips < maxTailWhips ) {
      tailWhipRoutine();
      tailWhips = tailWhips + 1;
    }

  } else {
    digitalWrite(relayPin, LOW);
    if ( logState == 1 ) {
      Serial.println("Nothing seen, going to sleep");
      logState = 0;
    }
  }
}
