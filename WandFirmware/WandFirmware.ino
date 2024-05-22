#include <TimerTC3.h>
#include<Wire.h>
#include <FastLED.h>

#define NUM_LEDS 30
#define STRIPE_PIN 10
#define FLASHLIGHT_PIN 9
#define ACCS_INTERVAL 10
#define STRIPE_INTERVAL 10
#define SWEEP_ACCELERATION 25000
#define BUTTON_PIN 1
#define LED_PIN 2
#define BUTTON_DEBOUNCE 100

const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

int secondsTicks = 0;
int accsTicks = 0;
int stripeTicks = 0;
int ledMillis = 0;
int buttonMillis = 0;
bool readAccelerometer = false;
bool sweepDetected = false;
bool stopDetected = false;
bool ledState = false;
int16_t xAcceleration = 0;
int16_t zAcceleration = 0;

CRGB leds[NUM_LEDS];

uint8_t fade[9] = { 255, 236, 192, 128, 64, 32, 16, 4, 1 };
uint8_t color = 0;
uint8_t sectorIndex = 0;
float vectorsRatio = 0.000;
int stripePosition = -10;
bool stripeEnabled = false;
bool stripeUpdateRequired = false;
static uint8_t brightness = 0;
float angle_step_tans[64] = {
  0.0000,
  0.0245,
  0.0491,
  0.0738,
  0.0985,
  0.1233,
  0.1483,
  0.1735,
  0.1989,
  0.2246,
  0.2505,
  0.2767,
  0.3033,
  0.3304,
  0.3578,
  0.3857,
  0.4142,
  0.4433,
  0.4730,
  0.5034,
  0.5345,
  0.5665,
  0.5994,
  0.6332,
  0.6682,
  0.7043,
  0.7417,
  0.7804,
  0.8207,
  0.8626,
  0.9063,
  0.9521,
  1.0000,
  1.0503,
  1.1033,
  1.1593,
  1.2185,
  1.2814,
  1.3483,
  1.4199,
  1.4966,
  1.5792,
  1.6684,
  1.7652,
  1.8709,
  1.9867,
  2.1143,
  2.2560,
  2.4142,
  2.5924,
  2.7948,
  3.0270,
  3.2966,
  3.6135,
  3.9922,
  4.4532,
  5.0273,
  5.7631,
  6.7415,
  8.1078,
  10.1532,
  13.5567,
  20.3555,
  40.7355
 };

void setup() {
  // put your setup code here, to run once:
  TimerTc3.initialize(1000);
  TimerTc3.attachInterrupt(millisTick);

  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  Serial.begin(9600);

  pinMode(FLASHLIGHT_PIN, OUTPUT);
  FastLED.addLeds<WS2811, STRIPE_PIN, RGB>(leds, NUM_LEDS);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonInterrupt, FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (readAccelerometer){
    readAccelerometer = false;
    readAccelerometerData();

    if (sqrt(sq(GyX) + sq(GyZ)) >= SWEEP_ACCELERATION){
      sweepDetected = true;
      xAcceleration = GyX;
      zAcceleration = GyZ;
    }

    if (sweepDetected && abs(GyX) < 500 && abs(GyZ) < 500) stopDetected = true;

    if (sweepDetected && stopDetected){
      sweepDetected = false;
      stopDetected = false;

      if (xAcceleration > 0 && zAcceleration > 0) sectorIndex = 0;
      else if (xAcceleration > 0 && zAcceleration < 0) sectorIndex = 1;
      else if (xAcceleration < 0 && zAcceleration < 0) sectorIndex = 2;
      else sectorIndex = 3;

      color = detectAngleStep(abs(xAcceleration), abs(zAcceleration)) + 64 * sectorIndex;
      stripePosition = -10;
      stripeEnabled = true;

      // Serial.print("Color: ");
      // Serial.println(color);
    }

  }

  if (stripeUpdateRequired){
    updateStripe();
    stripeUpdateRequired = false;
  }

}

void millisTick()
{
  
  secondsTicks++;
  if (secondsTicks == 1000){
    secondsTicks = 0;
    secondTick();
  }

  accsTicks++;
  if (accsTicks == ACCS_INTERVAL){
    accsTicks = 0;
    readAccelerometer = true;
  }

  stripeTicks++;
  if (stripeTicks == STRIPE_INTERVAL){
    stripeTicks = 0;
    if (stripeEnabled){
      shiftStripe();
    }
  }

  if (buttonMillis > 0) buttonMillis--;
}

void secondTick(){
  // Serial.print(".");
}

void readAccelerometerData(){
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
}

void updateStripe(){
  for (int i = 0; i < NUM_LEDS; i++) {
    if (abs(i - stripePosition) > 8) brightness = 0;
    else brightness = fade[abs(i - stripePosition)];
    leds[i] = CHSV(color, 255, brightness);
  }
  FastLED.show();
}

void shiftStripe(){
  if (stripePosition < NUM_LEDS + 10){
    stripePosition++;
    stripeUpdateRequired = true;
  }
  else{
    stripeEnabled = false;
  }
}

int detectAngleStep(int16_t x, int16_t z){
  if (z == 0) return 63;
  vectorsRatio = x/z;
  for (int i = 0; i < 64; i++){
    if (angle_step_tans[i] > vectorsRatio) return i;
  }
  return 63;
}

void switchLedDebounced(){
  if (buttonMillis == 0){
    buttonMillis = BUTTON_DEBOUNCE;
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
    Serial.println(ledState);
  }
}

void buttonInterrupt(){
  switchLedDebounced();
}
