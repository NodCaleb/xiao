#include <FastLED.h>
#define NUM_LEDS 22
#define STRIP_WIDTH 11
#define LED_PIN 10
#define DELAY_TIME 50
CRGB leds[NUM_LEDS];
int step = 0;
uint8_t fade[NUM_LEDS] = { 63,	79,	95,	111,	127,	175,	207,	239,	239,	255,	255,	255,	255,	239,	239,	207,	175,	127,	111,	95,	79,	63 };
uint8_t colors[NUM_LEDS] = { 83,	84,	85,	86,	87,	90,	92,	94,	94,	95,	95,	95,	95,	94,	94,	92,	90,	87,	86,	85,	84,	83 };
int directDelta;
int loopDelta;
int ledPropertiesIndex = 0;

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2811, LED_PIN, RGB>(leds, NUM_LEDS);
}

void loop() {
  for (int i = 0; i < NUM_LEDS; i++){

    ledPropertiesIndex = abs(step - i);
    leds[i] = CHSV(colors[ledPropertiesIndex], 255, fade[ledPropertiesIndex]);

  }
  FastLED.show();
  
  step++;
  if (step == NUM_LEDS) step = 0;

  delay(DELAY_TIME);
}

int circleDelta(int index0, int index1){
  if (index0 < index1){
    directDelta = index1 - index0;
    loopDelta = NUM_LEDS - index1 + index0;
  }
  else{
    directDelta = index0 - index1;
    loopDelta = NUM_LEDS - index0 + index1;
  }

  if (directDelta < loopDelta) return directDelta;
  return loopDelta;
}
