#include <ArduinoBLE.h>

const int buttonPin = 2;
const int buttonPin2 = 3;
const char* deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
const char* deviceServiceCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214";
bool led1IsOn = false;
bool led2IsOn = false;
unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;
unsigned long debounceDelay = 150;
int lastButtonState = HIGH;
int lastButtonState2 = HIGH;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP); // Button to GND

  
  if (!BLE.begin()) {
    Serial.println("- BLE failed!");
    while (1);
  }
  
  BLE.scanForUuid(deviceServiceUuid);
  Serial.println("Scanning for Peripheral...");
}

void loop() {
  BLEDevice peripheral = BLE.available();

  if (peripheral) {
    if (peripheral.localName() == "Nano 33 BLE Peripheral") {
      BLE.stopScan();
      controlPeripheral(peripheral);
      BLE.scanForUuid(deviceServiceUuid); // Resume scanning after disconnect
    }
  }
}

void controlPeripheral(BLEDevice peripheral) {
  if (!peripheral.connect()) return;
  if (!peripheral.discoverAttributes()) {
    peripheral.disconnect();
    return;
  }

  BLECharacteristic dataChar = peripheral.characteristic(deviceServiceCharacteristicUuid);
  
  while (peripheral.connected()) {
    // --- Handle Button 1 Toggle ---
    int reading1 = digitalRead(buttonPin);

    // Check if button is pressed AND if enough time has passed (Debounce)
    if (reading1 == LOW && (millis() - lastDebounceTime1 > debounceDelay)) {
  
      led1IsOn = !led1IsOn; // Flip the switch
  
     if (led1IsOn) {
     Serial.println("Button 1 Toggled: Sending 1 (LED ON)");
     dataChar.writeValue((byte)1);
      } else {
      Serial.println("Button 1 Toggled: Sending 2 (LED OFF)");
     dataChar.writeValue((byte)2);
     }
  
      lastDebounceTime1 = millis(); // Reset the timer
    }

    // --- Handle Button 2 Toggle ---
    int reading2 = digitalRead(buttonPin2);

    if (reading2 == LOW && (millis() - lastDebounceTime2 > debounceDelay)) {
  
      led2IsOn = !led2IsOn; // Flip the switch
  
      if (led2IsOn) {
        Serial.println("Button 2 Toggled: Sending 3 (LED ON)");
        dataChar.writeValue((byte)3);
      } else {
        Serial.println("Button 2 Toggled: Sending 4 (LED OFF)");
        dataChar.writeValue((byte)4);
      }
  
      lastDebounceTime2 = millis();
    }
  }
}