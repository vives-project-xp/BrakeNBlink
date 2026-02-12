const int led1 = 3; 
const int led2 = 4;
const int button1 = 2; 
const int button2 = 5;
bool led1State = false; 
bool led2State = false;
bool lastButton1 = HIGH; 
bool lastButton2 = HIGH;

void setup() 
{ 
 pinMode(led1, OUTPUT); 
 pinMode(led2, OUTPUT);
 pinMode(button1, INPUT_PULLUP); 
 pinMode(button2, INPUT_PULLUP); 
}

void loop() 
{ 
  bool currentButton1 = digitalRead(button1); 
  bool currentButton2 = digitalRead(button2);

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

}
