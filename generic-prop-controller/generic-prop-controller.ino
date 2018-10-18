/**
* Copyright 2018 Michael Heijmans
*
* Generic single sensor prop controller
*
* Author::    Michael Heijmans  (parabuzzle@gmail.com)
* Copyright:: Copyright (c) 2018 Rotting Orchards
* License::   MIT
*/


// define constants
#define sensorPin 3            // Input pin connected to PIR sensor
#define relayPin 2             // Output pin to activate the Relay
#define animationDelay 0       // Time to wait (in milliseconds) after sensor is active and before animation begins
#define activationPeriod 5000  // Time to keep the relay active in milliseconds
#define waitForReset 5000      // Time to wait after routine is complete before starting it all over again

// define mutables
int sensorState = 0;
int logState    = 0;

// setup our console logging
void setupSerialLogging() {
  Serial.begin(9600);
  Serial.println("--- Start Serial Logging ---");
  Serial.println("Rotting Orchards Simple Prop Controller");
  Serial.println("https://www.rottingorchards.com");
  Serial.println("------");
  Serial.println(""); // new line to make it look nice :) 
}

// A function to turn a pin on
// because typing digitalWrite is
// too much effort
void on(int pin){
  digitalWrite(pin, HIGH);  
}

// A function to turn a pin off
// because typing digitalWrite is
// too much effort
void off(int pin){
  digitalWrite(pin, LOW);  
}

// Animation Function
void animate() {
  Serial.println('waiting ' + animationDelay + 'ms before animating');
  delay(animationDelay);
  Serial.println('activating relay for ' + activationPeriod + 'ms');
  on(relayPin);
  delay(activationPeriod);
  Serial.println("deactivating relay");
  off(relayPin);
}

// Arduino setup routine
void setup() {
  pinMode(relayPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  setupSerialLogging();
}

// Arduino main loop
void loop() {
  // Check for current sensor state
  sensorState = digitalRead(sensorPin);

  if (sensorState == HIGH) {
    
    if ( logState == 0 ) {
      Serial.println("Sensor sees something");
      logState = 1;
    }
    
    animate();

    Serial.println('waiting' + waitForReset + 'ms before resetting');
    delay(waitForReset);
    
  } else {
    
    off(relayPin);
    if ( logState == 1 ) {
      Serial.println("Nothing seen, going to sleep");
      logState = 0;
    }
    
  }
}
