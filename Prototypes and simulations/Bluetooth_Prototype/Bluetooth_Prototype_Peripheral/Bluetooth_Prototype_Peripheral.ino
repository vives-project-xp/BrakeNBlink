#include <ArduinoBLE.h>

const char* deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
const char* deviceServiceCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214";

BLEService customService(deviceServiceUuid); 
BLEByteCharacteristic dataCharacteristic(deviceServiceCharacteristicUuid, BLERead | BLEWrite);
bool blinkLed1 = false;
bool blinkLed2 = false;

unsigned long lastBlinkTime = 0;
const int blinkInterval = 500; // Blink speed in milliseconds
bool ledToggleState = false;
const int led1 = 2;
const int led2 = 3;
const int led3 = 4;

void setup() {
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  while (!Serial);   
  
  // Initialize onboard LEDs
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW); 

  if (!BLE.begin()) {
    Serial.println("- Starting Bluetooth® Low Energy module failed!");
    while (1);
  }

  BLE.setLocalName("Nano 33 BLE Peripheral");
  BLE.setAdvertisedService(customService);
  customService.addCharacteristic(dataCharacteristic);
  BLE.addService(customService);
  
  dataCharacteristic.writeValue(0); // Set initial value to 0
  BLE.advertise();

  Serial.println("Bluetooth Peripheral Ready. Waiting for connection...");
}

void loop() {
  BLEDevice central = BLE.central();
  if (central) {
    Serial.print("* Connected to central: ");
    Serial.println(central.address());

    while (central.connected()) {
      while (central.connected()) {
        // 1. Check for new Bluetooth data
        if (dataCharacteristic.written()) {
          handleIncomingData(dataCharacteristic.value());
        }

        // 2. The Blinking Timer (Non-blocking)
        if (millis() - lastBlinkTime >= blinkInterval) {
          lastBlinkTime = millis();
          ledToggleState = !ledToggleState; // Flip the blink state

          // If LED 1 is supposed to blink, apply the toggle
          if (blinkLed1) {
            digitalWrite(led1, ledToggleState ? LOW : HIGH);
          }
    
          // If LED 2 is supposed to blink, apply the toggle
          if (blinkLed2) {
            digitalWrite(led2, ledToggleState ? LOW : HIGH);
          }
        }
      }
      // Check if the central device wrote a new value
      if (dataCharacteristic.written()) {
        byte receivedValue = dataCharacteristic.value();
        handleIncomingData(receivedValue);
      }
    }
    
    Serial.println("* Disconnected from central");
  }
}

void handleIncomingData(byte value) {
  switch (value) {
    case 1: blinkLed1 = true;  break; 
    case 2: blinkLed1 = false; digitalWrite(led1, LOW); break; // Off (Active-Low)
    case 3: blinkLed2 = true;  break; 
    case 4: blinkLed2 = false; digitalWrite(led2, LOW); break; // Off (Active-Low)
  }
}