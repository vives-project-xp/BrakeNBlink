#include <Adafruit_NeoPixel.h>

#define PIN_A       2
#define PIN_B       3
#define NUMPIXELS  14 // Number of LEDs per strip

Adafruit_NeoPixel stripA(NUMPIXELS, PIN_A, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripB(NUMPIXELS, PIN_B, NEO_GRB + NEO_KHZ800);

unsigned long previousMillis = 0;
const long interval = 30000; 
int currentMode = 0;
const int totalModes = 3;

void setup() {
  stripA.begin();
  stripB.begin();
  stripA.setBrightness(100);
  stripB.setBrightness(100);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    currentMode = (currentMode + 1) % totalModes;
    stripA.clear();
    stripB.clear();
  }

  // Running the modes
  switch (currentMode) {
    case 0:
      // Both strips doing a rainbow
      dualRainbow(); 
      break;
    case 1:
      // Strip A is Red, Strip B is Blue
      solidDual(stripA.Color(255, 0, 0), stripB.Color(0, 0, 255));
      break;
    case 2:
      // Back and forth bouncing effect between strips
      pingPongEffect();
      break;
  }
}

// --- Multi-Strip Animation Functions ---

void dualRainbow() {
  static uint16_t j = 0;
  for(int i=0; i<NUMPIXELS; i++) {
    uint32_t col = Wheel(((i * 256 / NUMPIXELS) + j) & 255);
    stripA.setPixelColor(i, col);
    stripB.setPixelColor(i, col);
  }
  stripA.show();
  stripB.show();
  j++;
}

void solidDual(uint32_t colorA, uint32_t colorB) {
  for(int i=0; i<NUMPIXELS; i++) {
    stripA.setPixelColor(i, colorA);
    stripB.setPixelColor(i, colorB);
  }
  stripA.show();
  stripB.show();
}

void pingPongEffect() {
  static int pos = 0;
  static int direction = 1;
  static unsigned long lastUpdate = 0;

  if (millis() - lastUpdate > 30) {
    stripA.clear();
    stripB.clear();
    
    stripA.setPixelColor(pos, stripA.Color(255, 255, 255));
    stripB.setPixelColor(NUMPIXELS - 1 - pos, stripB.Color(255, 255, 255));
    
    stripA.show();
    stripB.show();
    
    pos += direction;
    if (pos <= 0 || pos >= NUMPIXELS - 1) direction *= -1;
    lastUpdate = millis();
  }
}

// Reuse the Wheel function from the previous response here...
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) return stripA.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return stripA.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return stripA.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}