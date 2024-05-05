#include <FastLED.h>
#define NUM_LEDS 22
#define STRIP_WIDTH 11
#define LED_PIN 10
#define DELAY_TIME 30
CRGB leds[NUM_LEDS];
int step = 0;
// uint8_t fade[11] = { 255, 255, 236, 192, 128, 64, 32, 16, 4, 1, 1 };
uint8_t fade[11] = { 255, 255, 255, 255, 236, 192, 128, 64, 32, 16, 4 };
int directDelta;
int loopDelta;
int color = 80;
bool colorForward = true;

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2811, LED_PIN, RGB>(leds, NUM_LEDS);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < NUM_LEDS; i++){
    // if (i >= step && i < step + STRIP_WIDTH || step > NUM_LEDS - STRIP_WIDTH && (i >= step || i < step + STRIP_WIDTH - NUM_LEDS)) leds[i] = CHSV(164, 255, 255);
    // else leds[i] = CHSV(164, 255, 0);

    leds[i] = CHSV(color, 255, fade[circleDelta(step, i)]);

  }
  FastLED.show();
  
  step++;
  if (step == NUM_LEDS) step = 0;

  if (colorForward) color++;
  else color--;

  if (color == 80 || color == 120) colorForward = !colorForward;

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
