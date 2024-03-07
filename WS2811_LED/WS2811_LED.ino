#include <FastLED.h>
#define NUM_LEDS 60
#define LED_PIN 10
#define DELAY_TIME 10  // Delay between color changes (in milliseconds)
CRGB leds[NUM_LEDS];

uint8_t fade[9] = { 255, 236, 192, 128, 64, 32, 16, 4, 1 };
uint8_t colors[4] = { 10, 83, 96, 164 };

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2811, LED_PIN, RGB>(leds, NUM_LEDS);
}

void loop() {
  static uint8_t hue = 164;  // Hue value for color shifting 10 - green 83 - yellow 96 - red 164 - blue
  static uint8_t brightness = 0;

  // for (int j = 0; j < NUM_LEDS; j++) {

  //   if (abs(20 - j) > 8) brightness = 0;
  //   else brightness = fade[abs(20 - j)];

  //   leds[j] = CHSV(hue, 255, brightness);
  // }
  // FastLED.show(); 

  for (int k = 0; k < 4; k++){
    for (int i = -10; i < NUM_LEDS + 10; i++) {
      for (int j = 0; j < NUM_LEDS; j++) {

        if (abs(i - j) > 8) brightness = 0;
        else brightness = fade[abs(i - j)];

        leds[j] = CHSV(colors[k], 255, brightness);
      }
      FastLED.show();  // Update the LED strip
      delay(DELAY_TIME);  // Delay between color changes
    }
  } 
  
  
  // Shift the hue for the next frame
  //hue++;
}
