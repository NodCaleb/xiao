#include <FastLED.h>
#define NUM_LEDS 3
#define LED_PIN 10
#define DELAY_TIME 50  // Delay between color changes (in milliseconds)
CRGB leds[NUM_LEDS];
int led = D10;

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2811, LED_PIN, RGB>(leds, NUM_LEDS);
}

void loop() {
  static uint8_t hue = 0;  // Hue value for color shifting
  // Set all LEDs to the current hue
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(hue, 255, 255);
  }
  FastLED.show();  // Update the LED strip
  delay(DELAY_TIME);  // Delay between color changes
  // Shift the hue for the next frame
  hue++;
}
