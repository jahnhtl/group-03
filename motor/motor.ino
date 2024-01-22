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
const int sensorPinLinks = A2;  // Left sensor
const int sensorPinVorne = A0;  // Front sensor

int IN1 = 5;
int IN2 = 6;
int IN3 = 9;
int IN4 = 11;

bool isStarted = false; 

void stopMotors(); // Function prototype

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
  if (digitalRead(startButtonPin) == LOW) {
    Serial.println("Start-Taster gedrückt!");
    isStarted = true; // Setze den Startstatus auf true, wenn der Start-Button gedrückt wird
    //delay(500); // Entprellzeit
  }

  if (digitalRead(stopButtonPin) == LOW) {
    Serial.println("Stop-Taster gedrückt!");
    stopMotors(); // Stoppe die Motoren, wenn der Stop-Button gedrückt wird
    isStarted = false; // Setze den Startstatus auf false
    //delay(500); // Entprellzeit
  }

  if (isStarted) {
    sensorRechts(); // Right sensor auslesen
    sensorLinks();  // Left sensor auslesen
    sensorVorne();  // Front sensor auslesen
  }
}

void stopMotors() {
  analogWrite(IN1, 0);
  analogWrite(IN2, 0);
  analogWrite(IN3, 0);
  analogWrite(IN4, 0);
}

void forward() {
  analogWrite(IN1, 0);
  analogWrite(IN2, 180);
  analogWrite(IN3, 180);
  analogWrite(IN4, 0);
}

void rechtsBiegen() {
  analogWrite(IN1, 0);
  analogWrite(IN2, 90);
  analogWrite(IN3, 180);
  analogWrite(IN4, 0);
}

void linksBiegen() {
  analogWrite(IN1, 0);
  analogWrite(IN2, 180);
  analogWrite(IN3, 90);
  analogWrite(IN4, 0);
}




void sensorRechts() {
  int sensorValueRechts = analogRead(sensorPinRechts);
  float distanceRechts = 5100.0 / (sensorValueRechts - 30.0);
  

  Serial.print(" Abstand Sensor rechts: ");
  Serial.print(distanceRechts);
  Serial.print(" cm ");

  if (distanceRechts > 32) {
    rechtsBiegen();
  }
  else {
    forward();
  }
}

void sensorLinks() {
  int sensorValueLinks = analogRead(sensorPinLinks);
  //Serial.print("Sensorwert links: ");
  //Serial.println(sensorValueLinks);

  float distanceLinks = 5100.0 / (sensorValueLinks - 30.0);
  //float distanceLinks = sensorValueLinks;

  Serial.print(" Abstand Sensor links: ");
  Serial.print(distanceLinks);
  Serial.print(" cm ");

  if (distanceLinks > 40) {
    linksBiegen();
  }
  else {
    forward();
  }
}

void sensorVorne() {
  int sensorValueVorne = analogRead(sensorPinVorne);

  
  float distanceVorne = 10650.08 * pow(sensorValueVorne,-0.935) - 10;
 
  

  Serial.print(" Abstand Sensor vorne: ");
  Serial.print(distanceVorne);
  Serial.print(" cm \n ");

  if (sensorValueVorne <= 22) {
    stopMotors();
  }
  else {
    forward();
  }

}


/*
// Definitions Arduino pins connected to input H Bridge
int startButtonPin = 2;  // Pin für den Start-Taster
int stopButtonPin = 3;   // Pin für den Stop-Taster

const int sensorPin = A5; // Analog pin the sensor is connected to
const int sensorPinV = A0;

int IN1 = 5;
int IN2 = 6;
int IN3 = 9;
int IN4 = 11;

bool isStarted = false; 

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
  if (digitalRead(startButtonPin) == LOW) {
    Serial.println("Start-Taster gedrückt!");
    isStarted = true; // Setze den Startstatus auf true, wenn der Start-Button gedrückt wird
    delay(500); // Entprellzeit
  }

  if (digitalRead(stopButtonPin) == LOW) {
    Serial.println("Stop-Taster gedrückt!");
    stopMotors(); // Stoppe die Motoren, wenn der Stop-Button gedrückt wird
    isStarted = false; // Setze den Startstatus auf false
    delay(500); // Entprellzeit
  }

  if (isStarted) {
    sensor(); // Wenn gestartet, führe die Sensorprüfung und Motorsteuerung aus
  }
}

// Funktion zum Drehen der Motoren im Uhrzeigersinn
void forward() {
  analogWrite(IN1, 0);
  analogWrite(IN2, 255);
  analogWrite(IN3, 255);
  analogWrite(IN4, 0);
}

// Funktion zum Stoppen der Motoren
void stopMotors() {
  analogWrite(IN1, 0);
  analogWrite(IN2, 0);
  analogWrite(IN3, 0);
  analogWrite(IN4, 0);
}

void rechtsBiegen() {
  analogWrite(IN1, 0);
  analogWrite(IN2, 100);
  analogWrite(IN3, 255);
  analogWrite(IN4, 0);
}
 
void sensor() {
  int sensorValue = analogRead(sensorPin); // Lese den analogen Sensor

  float distance = 5100.0 / (sensorValue - 30.0);
  if (distance <= 80 && distance >= 0) {
    Serial.print("Abstand: ");
    Serial.print(distance);
    Serial.println(" cm");
  } else {
    Serial.println("Außerhalb der Reichweite!");
  }
  
  Serial.print("Sensorwert: ");
  Serial.println(sensorValue);

  if (sensorValue >= 280 && sensorValue <= 660) {
    forward();
  } else {
    rechtsBiegen();
  }

  delay(250); // Eine kurze Verzögerung für Stabilität
}

void sensorvorne(){
  int sensorValue2 = analogRead(sensorPinV);
  float distance = 5100 / (sensorValue2 - 30);
  
  Serial.print("Abstand Sensor vorne: ");
  Serial.print(distance);
  Serial.println(" cm");

  if(sensorValue2<=500){
    stopMotors();
  }
 }
 */
/*
//Definitions Arduino pins connected to input H Bridge
int startButtonPin = 2;  // Pin für den Start-Taster
int stopButtonPin = 3;   // Pin für den Stop-Taster

const int sensorPin = A5; // Analog pin the sensor is connected to

int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;


void setup() {
  pinMode(startButtonPin, INPUT_PULLUP);
  pinMode(stopButtonPin, INPUT_PULLUP);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // Überwache den Start-Taster
  if (digitalRead(startButtonPin) == LOW) {
    // Start-Aktion hier ausführen
    Serial.println("Start-Taster gedrückt!");
     sensortest();
    delay(500);  // Entprellzeit
    
  }

  // Überwache den Stop-Taster
  if (digitalRead(stopButtonPin) == LOW) {
    // Stop-Aktion hier ausführen
    Serial.println("Stop-Taster gedrückt!");
    stopMotors();  // Beispiel: Motoren stoppen
    delay(500);  // Entprellzeit
  }

}

// Funktion zum Drehen der Motoren im Uhrzeigersinn
void forward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// Funktion zum Stoppen der Motoren
void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void rechtsBiegen() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
  }

void sensortest() { 
  int sensorValue = analogRead(sensorPin); // Read the analog sensor 
  Serial.println( sensorValue);
  if (sensorValue >= 600 && sensorValue <= 700)
  {
    forward();  // Beispiel: Motoren stoppen
  }
    else {
    rechtsBiegen();
    }

}
*/
