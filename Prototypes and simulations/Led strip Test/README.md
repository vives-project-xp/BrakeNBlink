#include <Adafruit_NeoPixel.h>
 
#define LED_PIN     2

#define LED_COUNT   4

#define BRIGHTNESS  30
 
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);
 
uint32_t colors[7];
 
void setup() {

  strip.begin();

  strip.setBrightness(BRIGHTNESS);
 
  colors[0] = strip.Color(255,0,0);     // red

  colors[1] = strip.Color(255,120,0);   // orange

  colors[2] = strip.Color(255,255,0);   // yellow

  colors[3] = strip.Color(0,255,0);     // green

  colors[4] = strip.Color(0,0,255);     // blue

  colors[5] = strip.Color(255,105,180); // pink

  colors[6] = strip.Color(128,0,128);   // purple

}
 
void loop() {
 
  for(int c = 0; c < 7; c++) {
 
    for(int i = 0; i < LED_COUNT; i++) {

      strip.setPixelColor(i, colors[c]);

    }
 
    strip.show();

    delay(500);

  }
 
} 
 