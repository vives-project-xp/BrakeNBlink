#include <ArduinoBLE.h>
#include <Adafruit_NeoPixel.h>

const int buttonPin = 2;
const int buttonPin2 = 3;
#define PIN_LEFT    4
#define PIN_RIGHT   5
#define NUM_LEDS    16 // Adjust this to the number of LEDs in EACH strip

Adafruit_NeoPixel stripL(NUM_LEDS, PIN_LEFT,  NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripR(NUM_LEDS, PIN_RIGHT, NEO_GRB + NEO_KHZ800);

uint32_t orange = stripL.Color(255, 60, 0);
uint32_t red    = stripL.Color(255, 0, 0);
uint32_t black  = stripL.Color(0, 0, 0);

const char* deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
const char* deviceServiceCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214";
bool led1IsOn = false;
bool led2IsOn = false;
unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;
unsigned long debounceDelay = 150;
int lastButtonState = HIGH;
int lastButtonState2 = HIGH;
const int connectionLed = 5;
bool blinkLinker = false;
bool blinkRechter = false;
unsigned long lastBlinkTime = 0;
const int blinkInterval = 500;
bool ledToggleState = false;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(connectionLed, OUTPUT);
  digitalWrite(connectionLed, LOW);
  stripL.begin(); stripR.begin();
  stripL.show();  stripR.show();

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

    int reading1 = digitalRead(buttonPin);
    int reading2 = digitalRead(buttonPin2);


    if (reading1 == LOW && (millis() - lastDebounceTime1 > debounceDelay)) {
      dataChar.writeValue((byte)1);
      blinkLinker = !blinkLinker; if (blinkLinker) blinkRechter = false;
      lastDebounceTime1 = millis();
    }


    if (reading2 == LOW && (millis() - lastDebounceTime2 > debounceDelay)) {
      dataChar.writeValue((byte)3); 
      blinkRechter = !blinkRechter; if (blinkRechter) blinkLinker = false;
      lastDebounceTime2 = millis();
    }
  }
}

void fillStrip(Adafruit_NeoPixel &s, uint32_t color) {
  for(int i=0; i<NUM_LEDS; i++) {
    s.setPixelColor(i, color);
  }
  s.show();
}