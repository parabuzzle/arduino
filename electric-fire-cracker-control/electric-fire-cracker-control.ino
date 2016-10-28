// Pin Info
const int relayPin      = 2;

/**
*  Sensor
*  RED   - Vcc
*  GRAY  - GND
*  WHITE - Sense
*/
const int sensorPin     = 3;

// variables will change:
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
  // read the state of the sensor value:
  sensorState = digitalRead(sensorPin);

  // check if the sensor is active
  // if it is, the sensorState is HIGH:
  if (sensorState == HIGH) {
    if ( logState == 0 ) {
      Serial.println("Went High!");
      logState = 1;
    }
    digitalWrite(relayPin, HIGH);
    delay(2000);
    digitalWrite(relayPin, LOW);
    delay(11000);
  } else {
    digitalWrite(relayPin, LOW);
    if ( logState == 1 ) {
      Serial.println("Went Low!");
      logState = 0;
    }
  }

}
