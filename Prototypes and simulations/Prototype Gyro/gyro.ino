  #include <Arduino_BMI270_BMM150.h>
  float gyroThreshold = 10.0;
  bool blinkerOn = false;
  bool hasLeaned = false; 
  const int led1 = 3; 
  const int led2 = 4;
  const int button1 = 2; 
  const int button2 = 5;
  bool led1State = false; 
  bool led2State = false;
  bool lastButton1 = HIGH; 
  bool lastButton2 = HIGH;

void setup() {

  pinMode(led1, OUTPUT); 
  pinMode(led2, OUTPUT);
  pinMode(button1, INPUT_PULLUP); 
  pinMode(button2, INPUT_PULLUP); 
  Serial.begin(115200);
  while (!Serial);
  if (!IMU.begin()) {
    Serial.println("IMU init failed!"); while (1);
  }
  delay(150);
}

void loop() {
    bool currentButton1 = digitalRead(button1); 
    bool currentButton2 = digitalRead(button2);
    float ax, ay, az;

// --- Toggle LED 1 --- 
if (lastButton1 == HIGH && currentButton1 == LOW) 
{ 
  led1State = !led1State; 
  Serial.println("System Initialized!");
  // wissel aan/uit 
  delay(200); 
  // simpele debounce 
} 
lastButton1 = currentButton1;

// --- Toggle LED 2 --- 
if (lastButton2 == HIGH && currentButton2 == LOW) 
  { 
  led2State = !led2State; 
  delay(200); 
  Serial.println("System Initialized!");
  } 
  lastButton2 = currentButton2;

 if (led1State) {
 
    digitalWrite(led1, LOW);  // LED ON
    delay(500);
    digitalWrite(led1, HIGH); // LED OFF
    delay(500);
  } else {
    digitalWrite(led1, LOW); // Ensure LED stays OFF
  }
 if (led2State) {
 
    digitalWrite(led2, LOW);  // LED ON
    delay(500);
    digitalWrite(led2, HIGH); // LED OFF
    delay(500);
  } else {
    digitalWrite(led2, LOW); // Ensure LED stays OFF
  }

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(ax, ay, az);

    // Calculate lean angle in degrees
    // (Ensure Y is your left/right axis and Z is vertical)
    float leanAngle = abs(atan2(ay, az) * 180.0 / PI);

    if (led1State) {
      // Step 1: Detect that the turn has actually started
      if (leanAngle > 3.0) { 
        hasLeaned = true;
      }

      // Step 2: If we have leaned and are now back to upright (< 3 degrees)
      if (hasLeaned && leanAngle < 1.0) {
        digitalWrite(led1, LOW); // Turn off blinker
        led1State = false;
        hasLeaned = false;
        Serial.println("Turn complete: Level detected.");
      }
    }
  }
}
