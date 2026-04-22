#include <Adafruit_NeoPixel.h>
#include <Arduino_BMI270_BMM150.h>

#define PIN_A       2
#define PIN_B       3
#define NUMPIXELS  16 // Number of LEDs per strip

Adafruit_NeoPixel stripA(NUMPIXELS, PIN_A, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripB(NUMPIXELS, PIN_B, NEO_GRB + NEO_KHZ800);

unsigned long previousMillis = 0;
const long interval = 5000; 
int currentMode = 0;
const int totalModes = 8;

void setup() {
  stripA.begin();
  stripB.begin();
  stripA.setBrightness(100);
  stripB.setBrightness(100);
  if (!IMU.begin()) { Serial.println("IMU fail!"); while (1); }
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
      dualRainbow(); 
      break;
    case 1:
      solidDual(stripA.Color(255, 0, 0), stripB.Color(0, 0, 255));
      break;
    case 2:
      pingPongEffect(20);
      break;
    case 3:
      travelingPingPong(stripA.Color(0, 255, 255), 20);
      break;
    case 4:
      breatheEffect(0,255,0,20);
      break;
    case 5:
      randomSparkle(stripA.Color(0,0,255),60);
      break;
    case 6:
      discoSparkle(20);
      break;
    case 7:
      imuSpeedMeter();
      break;
  }
}


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

void pingPongEffect(int speed) {
  static int pos = 0;
  static int direction = 1;
  static unsigned long lastUpdate = 0;

  if (millis() - lastUpdate > speed) {
    lastUpdate = millis();
    stripA.clear();
    stripB.clear();
    
    for (int i = 0; i < 2; i++) {
      int indexA = (NUMPIXELS - 1) - (pos - i);
      int indexB = (NUMPIXELS - 1) - (pos - i); 

      if (indexA >= 0 && indexA < NUMPIXELS) {
        stripA.setPixelColor(indexA, stripA.Color(255, 0, 0)); 
      }
      
      if (indexB >= 0 && indexB < NUMPIXELS) {
        stripB.setPixelColor(indexB, stripB.Color(0, 255, 0)); 
      }
    }
    
    stripA.show();
    stripB.show();
    
    pos += direction;
    
    if (pos <= 0 || pos >= NUMPIXELS) {
      direction *= -1;
    }
  }
}

// Change 'int speed' to a lower number for FASTER, higher for SLOWER
void travelingPingPong(uint32_t color, int speed) {
  static int pos = 0;
  static int direction = 1;
  static unsigned long lastUpdate = 0;
  int totalLEDs = NUMPIXELS * 2;

  // We use the 'speed' variable here instead of the hardcoded 40
  if (millis() - lastUpdate > speed) { 
    lastUpdate = millis();

    stripA.clear();
    stripB.clear();

    for (int i = 0; i < 2; i++) {
      int activeLED = pos - i;
      
      if (activeLED >= 0 && activeLED < totalLEDs) {
        if (activeLED < NUMPIXELS) {
          // Strip A: REVERSED (Starts at end, moves to start)
          int reverseA = (NUMPIXELS - 1) - activeLED;
          stripA.setPixelColor(reverseA, color);
        } else {
          // Strip B: FORWARD (Starts at start, moves to end)
          int forwardB = activeLED - NUMPIXELS;
          stripB.setPixelColor(forwardB, color);
        }
      }
    }

    stripA.show();
    stripB.show();

    pos += direction;

    if (pos <= 0 || pos >= totalLEDs) {
      direction *= -1;
    }
  }
}

void breatheEffect(uint8_t r, uint8_t g, uint8_t b, int speed) {
  static unsigned long lastUpdate = 0;
  static int brightness = 0;
  static int direction = 1;

  if (millis() - lastUpdate > speed) {
    lastUpdate = millis();

    // Use math to create a smooth brightness curve
    float intensity = (sin(millis() / 500.0) + 1) * 127; 
    uint32_t color = stripA.Color((r * intensity) / 255, (g * intensity) / 255, (b * intensity) / 255);

    for (int i = 0; i < NUMPIXELS; i++) {
      stripA.setPixelColor(i, color);
      stripB.setPixelColor(i, color);
    }
    stripA.show();
    stripB.show();
  }
}

void randomSparkle(uint32_t color, int speed) {
  static unsigned long lastUpdate = 0;

  // Use the 'speed' variable (e.g., 100) to control the interval
  if (millis() - lastUpdate > speed) {
    lastUpdate = millis();

    // OPTIONAL: Dim existing LEDs slightly to create a "fading" trail
    // If you want them to just pop on and off, use stripA.clear() instead.
    for(int i=0; i<NUMPIXELS; i++) {
        stripA.setPixelColor(i, 0); // Clear Strip A
        stripB.setPixelColor(i, 0); // Clear Strip B
    }

    // Pick a random LED index (0 to NUMPIXELS-1)
    int randomLED_A = random(NUMPIXELS);
    int randomLED_B = random(NUMPIXELS);

    // Light them up!
    stripA.setPixelColor(randomLED_A, color);
    stripB.setPixelColor(randomLED_B, color);

    stripA.show();
    stripB.show();
  }
}

void discoSparkle(int speed) {
  static unsigned long lastUpdate = 0;

  if (millis() - lastUpdate > speed) {
    lastUpdate = millis();

    // Create a random color
    uint32_t randomColor = stripA.Color(random(255), random(255), random(255));

    int randomLED_A = random(NUMPIXELS);
    int randomLED_B = random(NUMPIXELS);

    stripA.setPixelColor(randomLED_A, randomColor);
    stripB.setPixelColor(randomLED_B, randomColor);

    stripA.show();
    stripB.show();
  }
}

void imuSpeedMeter() {
  static float smoothAccel = 1.0;
  float currentAccel = getAcceleration();
  
  // Simple low-pass filter to make the lights less "jittery"
  smoothAccel = (smoothAccel * 0.9) + (currentAccel * 0.1);

  // Map the acceleration to the number of LEDs
  // 1.0 is sitting still, 2.0+ is moving/shaking
  int numLedsToLight = map(smoothAccel * 100, 100, 250, 0, NUMPIXELS);
  numLedsToLight = constrain(numLedsToLight, 0, NUMPIXELS);

  stripA.clear();
  stripB.clear();

  for (int i = 0; i < numLedsToLight; i++) {
    // Color changes from Green to Red as it fills up
    uint32_t color = Wheel(map(i, 0, NUMPIXELS, 85, 0)); 
    stripA.setPixelColor(i, color);
    stripB.setPixelColor(i, color);
  }

  stripA.show();
  stripB.show();
}

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

float getAcceleration() {
  float ax, ay, az;
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(ax, ay, az);
    // Calculate total magnitude of acceleration
    return sqrt(ax * ax + ay * ay + az * az);
  }
  return 1.0; // Default gravity is ~1G
}