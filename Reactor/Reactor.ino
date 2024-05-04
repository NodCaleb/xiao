#include <FastLED.h>
#define NUM_LEDS 3
#define LED_PIN 10
CRGB leds[NUM_LEDS];

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2811, LED_PIN, RGB>(leds, NUM_LEDS);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < NUM_LEDS; i++){
    leds[i] = CHSV(164, 255, 255);
  }
  FastLED.show();
}
