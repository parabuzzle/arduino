/**
* Copyright 2018 Rotting Orchards
*
* Light Controller
*
* Author::    Michael Heijmans  (parabuzzle@gmail.com)
* Copyright:: Copyright (c) 2018 Rotting Orchards
* License::   MIT
*/

// define constants
#define triggerPin 2           // Input pin connected to the PicoBoo for triggering light shift
#define resetButtonPin 3       // Button to reset the light
#define relay1Pin 4            // Output pin to activate the first outlet
#define relay2Pin 5            // Output pin to activate the second outlet
#define lightsOffTime 4000     // Time all lights should be off during transition (in milliseconds)
#define SECTION_FIRST 0        // Set a constant for the first section
#define SECTION_SECOND 1       // Set a constant for the second section

// define mutables
int triggerState = 0;
int buttonState = 0;
int logState = 0;

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

// Light Transition Function
void transition(int section) {
  Serial.println("turn off all lights");
  off(relay1Pin);
  off(relay2Pin);
  if (section == SECTION_SECOND){
    Serial.println('waiting' + lightsOffTime + 'ms before turnning on second relay');
    Serial.println("activate second relay");
    on(relay2Pin);
  } else {
    Serial.println("activate first relay");
    on(relay1Pin);
  }
}

// Arduino setup routine
void setup() {
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);
  pinMode(triggerPin, INPUT);
  pinMode(resetButtonPin, INPUT);
  setupSerialLogging();
}

// Arduino main loop
void loop() {

  triggerState = digitalRead(triggerPin);
  buttonState = digitalRead(resetButtonPin);

  // Handle trigger state
  if (triggerState == HIGH) {
    
    if ( logState == 0 ) {
      Serial.println("Transition to sectond section triggered");
      logState = 1;
    }
    
    transition(SECTION_SECOND);
    
  } else {
    
    if ( logState == 1 ) {
      Serial.println("nothing changed... waiting for input");
      logState = 0;
    }
    
  }

  // Handle button state
  if (buttonState == HIGH) {
    if ( logState == 0 ) {
      Serial.println("Transition to first section triggered");
      logState = 1;
    }
    
    transition(SECTION_FIRST);
    
  } else {
    
    if ( logState == 1 ) {
      Serial.println("nothing changed... waiting for input");
      logState = 0;
    }
  }
}
