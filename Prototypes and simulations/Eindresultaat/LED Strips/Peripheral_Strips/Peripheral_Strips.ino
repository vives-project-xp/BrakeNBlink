#include <ArduinoBLE.h>
#include <Arduino_BMI270_BMM150.h>
#include <Adafruit_NeoPixel.h>

// --- LED STRIP CONFIG ---
#define PIN_LEFT    2
#define PIN_RIGHT   3
#define PIN_BRAKE   4
#define NUM_LEDS    16 // Adjust this to the number of LEDs in EACH strip

Adafruit_NeoPixel stripL(NUM_LEDS, PIN_LEFT,  NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripR(NUM_LEDS, PIN_RIGHT, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripB(NUM_LEDS, PIN_BRAKE, NEO_GRB + NEO_KHZ800);

uint32_t orange = stripL.Color(255, 60, 0);
uint32_t red    = stripL.Color(255, 0, 0);
uint32_t black  = stripL.Color(0, 0, 0);
// ------------------------

const char* deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
const char* deviceServiceCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214";

BLEService customService(deviceServiceUuid); 
BLEByteCharacteristic dataCharacteristic(deviceServiceCharacteristicUuid, BLERead | BLEWrite);

bool blinkLinker = false;
bool blinkRechter = false;
unsigned long lastBlinkTime = 0;
const int blinkInterval = 500;
bool ledToggleState = false;
unsigned long redStartTime = 0;
const long duration = 1000;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  
  // Initialize all 3 strips
  stripL.begin(); stripR.begin(); stripB.begin();
  stripL.show();  stripR.show();  stripB.show();

  if (!IMU.begin()) { Serial.println("IMU fail!"); while (1); }
  if (!BLE.begin()) { Serial.println("BLE fail!"); while (1); }

  BLE.setLocalName("Nano 33 BLE Peripheral");
  BLE.setAdvertisedService(customService);
  customService.addCharacteristic(dataCharacteristic);
  BLE.addService(customService);
  dataCharacteristic.writeValue(0);
  BLE.advertise();
}

void loop() {
  float ax, ay, az, bx, by, bz;
  BLEDevice central = BLE.central();

  if (central) {
    while (central.connected()) {

      unsigned long currentTime = millis();
      digitalWrite(LED_BUILTIN, HIGH);

        // 1. BRAKE LIGHT (Strip on Pin 4)
      if (IMU.accelerationAvailable()) {
        IMU.readAcceleration(ax, ay, az);
        if (ax < -0.3) {
          redStartTime = currentTime;
        }
      }

      if (redStartTime > 0 && (currentTime - redStartTime < duration)) {
        fillStrip(stripB, red);
      } else {
        fillStrip(stripB, black);
      }

      // 2. BLINKING (Strips on Pin 2 and 3)
      if (millis() - lastBlinkTime >= blinkInterval) {
        lastBlinkTime = millis();
        ledToggleState = !ledToggleState;

        if (blinkLinker) {
          fillStrip(stripL, ledToggleState ? orange : black);
          fillStrip(stripR, black); // Ensure other side is off
        } 
        else if (blinkRechter) {
          fillStrip(stripR, ledToggleState ? orange : black);
          fillStrip(stripL, black);
        }
        else {
          fillStrip(stripL, black);
          fillStrip(stripR, black);
        }
      }

      if (dataCharacteristic.written()) {
        handleIncomingData(dataCharacteristic.value());
      }
    }
  }
  blinkRechter = false;
  blinkLinker = false;
  digitalWrite(LED_BUILTIN, LOW);
}

// Helper to fill an entire strip with one color and show it
void fillStrip(Adafruit_NeoPixel &s, uint32_t color) {
  for(int i=0; i<NUM_LEDS; i++) {
    s.setPixelColor(i, color);
  }
  s.show();
}

void handleIncomingData(byte value) {
  switch (value) {
    case 1: blinkLinker = !blinkLinker; if (blinkLinker) blinkRechter = false; break;
    case 3: blinkRechter = !blinkRechter; if (blinkRechter) blinkLinker = false; break;
  }
}