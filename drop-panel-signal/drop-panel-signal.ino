// set pin numbers:
const int sensorPin     = 3;
const int sensorPwrPin  = 2;
const int ledPin        = 4;


// variables will change:
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
  // read the state of the sensor value:
  sensorState = digitalRead(sensorPin);
  
  // check if the sensor is active
  // if it is, the sensorState is HIGH:
  if (sensorState == HIGH) {
    if ( logState == 0 ) {
      Serial.println("Went High!");
      logState = 1;
    }
    digitalWrite(ledPin, HIGH);
    delay(5000);
  } else {
    digitalWrite(ledPin, LOW);
    if ( logState == 1 ) {
      Serial.println("Went Low!");
      logState = 0;
    }
  }

}
