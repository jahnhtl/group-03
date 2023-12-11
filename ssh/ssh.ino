const int sensorPin = A0; // Analog pin the sensor is connected to

void setup() {
  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  int sensorValue = analogRead(sensorPin); // Read the analog sensor value
  float distance = 5100.0 / (sensorValue - 30.0);
  Serial.println( sensorValue);
  delay(500); // Wait for a moment
}
