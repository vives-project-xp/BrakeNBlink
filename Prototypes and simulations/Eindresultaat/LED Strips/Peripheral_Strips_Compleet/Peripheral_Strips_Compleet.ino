#include <ArduinoBLE.h>
#include <Arduino_BMI270_BMM150.h>
#include <Adafruit_NeoPixel.h>

#define PIN_LEFT    2
#define PIN_RIGHT   3
#define PIN_BRAKE   4
#define NUM_LEDS    12

Adafruit_NeoPixel stripL(NUM_LEDS, PIN_LEFT,  NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripR(NUM_LEDS, PIN_RIGHT, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripB(NUM_LEDS, PIN_BRAKE, NEO_GRB + NEO_KHZ800);

uint32_t orange = stripL.Color(255, 60, 0);
uint32_t red    = stripL.Color(255, 0, 0);
uint32_t black  = stripL.Color(0, 0, 0);

unsigned long brakeConditionStarted = 0;
unsigned long redStartTime = 0;
const long duration = 1000;
const int brakeDelay = 100;

bool blinkLinker = false;
bool blinkRechter = false;
unsigned long lastBlinkTime = 0;
const int blinkInterval = 700;
bool ledToggleState = false;

int audiIndex = 0;
unsigned long lastAudiStep = 0;
const int audiSpeed = 35;

uint32_t lastColorB = 0;
uint32_t lastColorL = 0;
uint32_t lastColorR = 0;

const char* deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
const char* deviceServiceCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214";

BLEService customService(deviceServiceUuid); 
BLEByteCharacteristic dataCharacteristic(deviceServiceCharacteristicUuid, BLERead | BLEWrite);

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  
  stripL.begin(); stripR.begin(); stripB.begin();
  stripL.show();  stripR.show();  stripB.show();

  //bluetooth
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
  float ax, ay, az;
  BLEDevice central = BLE.central();
  
  if (central) {
    // Logica tijdens verbonden
    while (central.connected()) {
      unsigned long currentTime = millis();
      digitalWrite(LED_BUILTIN, HIGH);

      // Remlicht
      if (IMU.accelerationAvailable()) {
        IMU.readAcceleration(ax, ay, az);

        if (ax < -0.3) {
          if (brakeConditionStarted == 0) {
            brakeConditionStarted = currentTime;
          }
          if (currentTime - brakeConditionStarted >= brakeDelay) {
            redStartTime = currentTime;
          }
        } else {
          brakeConditionStarted = 0;
        }
      }
      if (redStartTime > 0 && (currentTime - redStartTime < duration)) {
        updateStrip(stripB, red, lastColorB);
      } else {
        updateStrip(stripB, black, lastColorB);
        if (currentTime - redStartTime >= duration) redStartTime = 0;
      }

    // Audi logica
    if (blinkLinker || blinkRechter) {
      if (millis() - lastAudiStep >= audiSpeed) {
        lastAudiStep = millis();
        audiIndex++;
        if (audiIndex >= NUM_LEDS) audiIndex = 0;
      }
    } else {
      audiIndex = 0;
    }

    // Knipperlicht logica
    if (millis() - lastBlinkTime >= blinkInterval) {
    lastBlinkTime = millis();
    ledToggleState = !ledToggleState;

    if (ledToggleState) audiIndex = 0; 
    }

    if (blinkLinker) {
      updateAudiBlinker(stripL, true);
      updateAudiBlinker(stripR, false);
    } 
    else if (blinkRechter) {
      updateAudiBlinker(stripR, true);
      updateAudiBlinker(stripL, false);
    }
    else {
      updateAudiBlinker(stripL, false);
      updateAudiBlinker(stripR, false);
    }


      if (dataCharacteristic.written()) {
        handleIncomingData(dataCharacteristic.value());
      }
    }
  }
  
  // Reset als niet connected
  blinkRechter = false;
  blinkLinker = false;
  updateStrip(stripL, black, lastColorL);
  updateStrip(stripR, black, lastColorR);
  updateStrip(stripB, black, lastColorB);
  digitalWrite(LED_BUILTIN, LOW);
}

// Kleur functie
void updateStrip(Adafruit_NeoPixel &s, uint32_t newColor, uint32_t &lastStoredColor) {
  if (newColor != lastStoredColor) {
    for(int i=0; i<NUM_LEDS; i++) {
      s.setPixelColor(i, newColor);
    }
    s.show();
    lastStoredColor = newColor;
  }
}

// Audi functie
void updateAudiBlinker(Adafruit_NeoPixel &strip, bool active) {
  if (!active) {
    for(int i=0; i<NUM_LEDS; i++) strip.setPixelColor(i, black);
  } else {
    for(int i=0; i<NUM_LEDS; i++) {
      strip.setPixelColor(i, (i <= audiIndex) ? orange : black);
    }
  }
  strip.show();
}

// Drukknop signaal verwerken van central
void handleIncomingData(byte value) {
  switch (value) {
    case 1: blinkLinker = !blinkLinker; if (blinkLinker) blinkRechter = false; break;
    case 3: blinkRechter = !blinkRechter; if (blinkRechter) blinkLinker = false; break;
  }
}