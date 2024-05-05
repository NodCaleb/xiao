#include <FastLED.h>
#define NUM_LEDS 22
#define STRIP_WIDTH 11
#define LED_PIN 10
#define DELAY_TIME 10
CRGB leds[NUM_LEDS];
int step = 0;

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2811, LED_PIN, RGB>(leds, NUM_LEDS);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < NUM_LEDS; i++){
    if (i >= step && i < step + STRIP_WIDTH || step > NUM_LEDS - STRIP_WIDTH && (i >= step || i < step + STRIP_WIDTH - NUM_LEDS)) leds[i] = CHSV(164, 255, 255);
    else leds[i] = CHSV(164, 255, 0);
  }
  FastLED.show();
  
  step++;
  if (step == NUM_LEDS) step = 0;
  delay(DELAY_TIME);
}
