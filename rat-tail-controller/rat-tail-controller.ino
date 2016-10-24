// pin info

/**
*  Sensor
*  GREEN  - Vcc
*  PURPLE - GND
*  BLUE   - Sense
*/
const int sensorPin     = 3;

/**
*  Relay
*  RED    - 12v (when active)
*  ORANGE - GND
*/
const int relayPin      = 2;

const int maxTailWhips  = 5;


// variables will change:
int sensorState = 0;
int logState    = 0;
int tailWhips   = 0;

void setupSerialLogging() {
  Serial.begin(9600);
  Serial.println("--- Start Serial Monitor SEND_RCVE ---");
  Serial.println();
}

void tailWhipRoutine() {
  digitalWrite(relayPin, HIGH);
  delay(500);
  digitalWrite(relayPin, LOW);
  delay(200);

  digitalWrite(relayPin, HIGH);
  delay(700);
  digitalWrite(relayPin, LOW);
  delay(300);

  digitalWrite(relayPin, HIGH);
  delay(200);
  digitalWrite(relayPin, LOW);
}

void setup() {
  pinMode(relayPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  setupSerialLogging();
}

void loop() {
  // read the state of the sensor value:
  sensorState = digitalRead(sensorPin);

  // check if the sensor is active
  // if it is, the sensorState is HIGH:
  if (sensorState == HIGH) {
    if ( logState == 0 ) {
      Serial.println("Went High!");
      logState = 1;
    }

    tailWhips = 0;
    while( tailWhips < maxTailWhips ) {
      tailWhipRoutine();
      tailWhips = tailWhips + 1;
    }

  } else {
    digitalWrite(relayPin, LOW);
    if ( logState == 1 ) {
      Serial.println("Went Low!");
      logState = 0;
    }
  }

}
