#include <ArduinoBLE.h>
#include <Arduino_BMI270_BMM150.h>

const char* deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
const char* deviceServiceCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214";

BLEService customService(deviceServiceUuid); 
BLEByteCharacteristic dataCharacteristic(deviceServiceCharacteristicUuid, BLERead | BLEWrite);
bool blinkLed1 = false;
bool blinkLed2 = false;

unsigned long lastBlinkTime = 0;
const int blinkInterval = 500;
bool ledToggleState = false;
const int led1 = 2;
const int led2 = 3;
const int led3 = 4;
const int led4 = 5;

float bx, by, bz;
float gyroThreshold = 10.0;
bool hasLeaned = false; 

void setup() {
  Serial.begin(115200);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  while (!Serial);   
    if (!IMU.begin()) {
    Serial.println("IMU init failed!"); while (1);
  }
  delay(150);
 
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
  
  dataCharacteristic.writeValue(0);
  BLE.advertise();

  Serial.println("Bluetooth Peripheral Ready. Waiting for connection...");
}

void loop() {
  pinMode(led4, OUTPUT);
  float ax, ay, az;
  BLEDevice central = BLE.central();
  if (central) {
    Serial.print("* Connected to central: ");
    Serial.println(central.address());

    while (central.connected()) {
      while (central.connected()) {
          if (IMU.accelerationAvailable()) {
            IMU.readAcceleration(ax, ay, az);
            if (ax < -0.20) {
              digitalWrite(led4, HIGH);
            } else {
              digitalWrite(led4, LOW);
            }

            delay(10); 
          } 

          delay(100);

          if (IMU.accelerationAvailable()) {
            IMU.readAcceleration(bx, by, bz);
            float leanAngle = abs(atan2(by, bz) * 180.0 / PI);
            if (blinkLed1 || blinkLed2) {
              if (leanAngle > 10.0) { 
                hasLeaned = true;
              }
              if (hasLeaned && leanAngle < 2.0) {
                blinkLed1 = false;
                blinkLed2 = false;
                digitalWrite(led1, LOW);
                digitalWrite(led2, LOW);
                hasLeaned = false;
                Serial.println("Turn complete: Level detected.");
              }
            }
          }

        if (dataCharacteristic.written()) {
          handleIncomingData(dataCharacteristic.value());
        }

        if (millis() - lastBlinkTime >= blinkInterval) {
          lastBlinkTime = millis();
          ledToggleState = !ledToggleState;

          if (blinkLed1) {
            digitalWrite(led1, ledToggleState ? LOW : HIGH);
          }
    
          if (blinkLed2) {
            digitalWrite(led2, ledToggleState ? LOW : HIGH);
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

void handleIncomingData(byte value) {
  switch (value) {
    case 1:
      blinkLed1 = true;  
      blinkLed2 = false; 
      digitalWrite(led2, LOW);
      break; 

    case 2:
      blinkLed1 = false; 
      digitalWrite(led1, LOW); 
      break;

    case 3:
      blinkLed2 = true;  
      blinkLed1 = false; 
      digitalWrite(led1, LOW);
      break; 

    case 4:
      blinkLed2 = false; 
      digitalWrite(led2, LOW); 
      break;
  }
}