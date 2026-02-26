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
const int connectionLed = 4;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(connectionLed, OUTPUT);
  digitalWrite(connectionLed, LOW);

  // bluetooth starten
  if (!BLE.begin()) {
    Serial.println("- BLE failed!");
    while (1);
  }
  
  BLE.scanForUuid(deviceServiceUuid);
  Serial.println("Scanning for Peripheral...");
}
// meer bluetooth
void loop() {
  BLEDevice peripheral = BLE.available();

  if (peripheral) {
    if (peripheral.localName() == "Nano 33 BLE Peripheral") {
      BLE.stopScan();
      controlPeripheral(peripheral);
      BLE.scanForUuid(deviceServiceUuid);
    }
  }
}
// meer bluetooth
void controlPeripheral(BLEDevice peripheral) {
  if (!peripheral.connect()) return;

  digitalWrite(connectionLed, HIGH);
  if (!peripheral.discoverAttributes()) {
    peripheral.disconnect();
    return;
  }

  BLECharacteristic dataChar = peripheral.characteristic(deviceServiceCharacteristicUuid);

  // Signalen van drukknoppen sturen naar peripheral Arduino als bytes
  while (peripheral.connected()) {
    int reading1 = digitalRead(buttonPin);
    int reading2 = digitalRead(buttonPin2);


    if (reading1 == LOW && (millis() - lastDebounceTime1 > debounceDelay)) {
      dataChar.writeValue((byte)1); 
      lastDebounceTime1 = millis();
    }


    if (reading2 == LOW && (millis() - lastDebounceTime2 > debounceDelay)) {
      dataChar.writeValue((byte)3); 
      lastDebounceTime2 = millis();
    }
  }
}