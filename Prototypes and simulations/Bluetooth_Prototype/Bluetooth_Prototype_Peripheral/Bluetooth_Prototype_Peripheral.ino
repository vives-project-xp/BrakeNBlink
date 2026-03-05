#include <ArduinoBLE.h>
#include <Arduino_BMI270_BMM150.h>

const char* deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
const char* deviceServiceCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214";

BLEService customService(deviceServiceUuid); 
BLEByteCharacteristic dataCharacteristic(deviceServiceCharacteristicUuid, BLERead | BLEWrite);
bool blinkLinker = false;
bool blinkRechter = false;

unsigned long lastBlinkTime = 0;
const int blinkInterval = 500;
bool ledToggleState = false;
const int LinkerLed = 2;
const int RechterLed = 3;
const int RemLed = 4;

float bx, by, bz;
float gyroThreshold = 10.0;
bool hasLeaned = false; 

void setup() {
  Serial.begin(115200);
  pinMode(LinkerLed, OUTPUT);
  pinMode(RechterLed, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW); 

  // IMU starten
  while (!Serial);   
    if (!IMU.begin()) {
    Serial.println("IMU init failed!"); while (1);
  }
  delay(150);

  // Bluetooth connectie starten
  if (!BLE.begin()) {
    Serial.println("- Starting Bluetooth® Low Energy module failed!");
    while (1);
  }
  BLE.setLocalName("Nano 33 BLE Peripheral");
  BLE.setAdvertisedService(customService);
  customService.addCharacteristic(dataCharacteristic);
  BLE.addService(customService);
  
  dataCharacteristic.writeValue(0);
  BLE.advertise();

  Serial.println("Bluetooth Peripheral Ready. Waiting for connection...");
}

void loop() {
  pinMode(RemLed, OUTPUT);
  float ax, ay, az;

  BLEDevice central = BLE.central();

  if (central) {
    Serial.print("* Connected to central: ");
    Serial.println(central.address());

    while (central.connected()) {
      while (central.connected()) {
          // Remlicht
          if (IMU.accelerationAvailable()) {
            IMU.readAcceleration(ax, ay, az);
            if (ax < -0.20) {
              digitalWrite(RemLed, HIGH);
            } else {
              digitalWrite(RemLed, LOW);
            }

            delay(10); 
          } 

          delay(100);
          // Blinker automatisch uit
          if (IMU.accelerationAvailable()) {
            IMU.readAcceleration(bx, by, bz);
            float leanAngle = abs(atan2(by, bz) * 180.0 / PI);
            if (blinkLinker || blinkRechter) {
              if (leanAngle > 10.0) { 
                hasLeaned = true;
              }
              if (hasLeaned && leanAngle < 2.0) {
                blinkLinker = false;
                blinkRechter = false;
                digitalWrite(LinkerLed, LOW);
                digitalWrite(RechterLed, LOW);
                hasLeaned = false;
                Serial.println("Turn complete: Level detected.");
              }
            }
          }

        if (dataCharacteristic.written()) {
          handleIncomingData(dataCharacteristic.value());
        }
        // Knipperen
        if (millis() - lastBlinkTime >= blinkInterval) {
          lastBlinkTime = millis();
          ledToggleState = !ledToggleState;

          if (blinkLinker) {
            digitalWrite(LinkerLed, ledToggleState ? LOW : HIGH);
          }
    
          if (blinkRechter) {
            digitalWrite(RechterLed, ledToggleState ? LOW : HIGH);
          }
        }
      }
      if (dataCharacteristic.written()) {
        byte receivedValue = dataCharacteristic.value();
        handleIncomingData(receivedValue);
      }
    }
    
    Serial.println("* Disconnected from central");
  }
}
// Gebruikt de ontvangen data van de central Arduino om de LEDs te togglen
void handleIncomingData(byte value) {
  switch (value) {
    case 1:
      if (blinkLinker) {
        blinkLinker = false;
        digitalWrite(LinkerLed, LOW);
      } else {
        blinkLinker = true;
        blinkRechter = false;
        digitalWrite(RechterLed, LOW);
      }
      break;

    case 3:
      if (blinkRechter) {
        blinkRechter = false;
        digitalWrite(RechterLed, LOW);
      } else {
        blinkRechter = true;
        blinkLinker = false;
        digitalWrite(LinkerLed, LOW);
      }
      break;
  }
}