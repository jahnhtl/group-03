/*========================================================================== //
  Author      : Handson Technology //
  Project     : Arduino Uno //
  Description : L298N Motor Driver //
  Source-Code : L298N_Motor.ino //
  Program: Control 2 DC motors using L298N H Bridge Driver
  //========================================================================== */

/*========================================================================== //
  Author      : Handson Technology //
  Project     : Arduino Uno //
  Description : L298N Motor Driver //
  Source-Code : L298N_Motor.ino //
  Program: Control 2 DC motors using L298N H Bridge Driver
  //========================================================================== */

// Definitions Arduino pins connected to input H Bridge
int startButtonPin = 2;  // Pin für den Start-Taster
int stopButtonPin = 3;   // Pin für den Stop-Taster

const int sensorPinRechts = A5; // Right sensor
const int sensorPinLinks = A3;  // Left sensor
const int sensorPinVorne = A0;  // Front sensor

int IN1 = 5;
int IN2 = 6;
int IN3 = 9;
int IN4 = 11;

bool isStarted = false;

//void stopMotors(); // Function prototype

void setup() {
  pinMode(startButtonPin, INPUT_PULLUP);
  pinMode(stopButtonPin, INPUT_PULLUP);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);
  Serial.println("HALLO");
}

void loop() {


    int sensorValueRechts = analogRead(sensorPinRechts);
    int sensorValueLinks = analogRead(sensorPinLinks);
    int sensorValueVorne = analogRead(sensorPinVorne);
    
  if (digitalRead(startButtonPin) == LOW) {
    Serial.println("Start-Taster gedrückt!");
    isStarted = true; // Setze den Startstatus auf true, wenn der Start-Button gedrückt wird
  }

  if (digitalRead(stopButtonPin) == LOW) {
    Serial.println("Stop-Taster gedrückt!");
    stopMotors(); // Stoppe die Motoren, wenn der Stop-Button gedrückt wird
    isStarted = false; // Setze den Startstatus auf false
  }

  if (isStarted) {


    float distanceRechts = 5100.0 / (sensorValueRechts - 30.0);
    float distanceLinks = 5100.0 / (sensorValueLinks - 30.0);
    float distanceVorne = 10650.08 * pow(sensorValueVorne, -0.935) - 10;

    Serial.print(" Abstand Sensor rechts: ");
    Serial.print(distanceRechts);
    Serial.print(" cm ");
    Serial.print(" Abstand Sensor links: ");
    Serial.print(distanceLinks);
    Serial.print(" cm ");
    Serial.print(" Abstand Sensor vorne: ");
    Serial.print(distanceVorne);
    Serial.print(" cm \n ");



/*    forward();

    if (distanceRechts > 55) {
      do {
        rechts();
      }
      while (distanceRechts < 25 && distanceLinks < 25);
    }
    else if (distanceLinks > 55) {
      do {
        links();
      }
      while (distanceRechts < 25 && distanceLinks < 25);
    }
    else
      do {
        forward();
      }
      while (distanceVorne < 30);
  }*/
}
}



void forward() {
  analogWrite(IN1, 0);
  analogWrite(IN2, 180);
  analogWrite(IN3, 180);
  analogWrite(IN4, 0);
}

void stopMotors() {
  analogWrite(IN1, 0);
  analogWrite(IN2, 0);
  analogWrite(IN3, 0);
  analogWrite(IN4, 0);
}

void rechts() {
  analogWrite(IN1, 0);
  analogWrite(IN2, 180);
  analogWrite(IN3, 90);
  analogWrite(IN4, 0);
}

void links() {
  analogWrite(IN1, 0);
  analogWrite(IN2, 90);
  analogWrite(IN3, 180);
  analogWrite(IN4, 0);
}
