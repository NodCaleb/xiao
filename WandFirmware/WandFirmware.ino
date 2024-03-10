#include <TimerTC3.h>
#include<Wire.h>
#include <FastLED.h>

#define NUM_LEDS 30
#define STRIPE_PIN 10
#define FLASHLIGHT_PIN 9
#define ACCS_INTERVAL 10
#define STRIPE_INTERVAL 10

const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

int secondsTicks = 0;
int accsTicks = 0;
int stripeTicks = 0;
int ledMillis = 0;
bool readAccelerometer = false;
bool sweepDetected = false;
bool stopDetected = false;

CRGB leds[NUM_LEDS];

uint8_t fade[9] = { 255, 236, 192, 128, 64, 32, 16, 4, 1 };
uint8_t colors[4] = { 10, 83, 96, 164 };
uint8_t colorIndex = 0;
int stripePosition = -10;
bool stripeEnabled = false;
bool stripeUpdateRequired = false;
static uint8_t brightness = 0;

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
}

void loop() {
  // put your main code here, to run repeatedly:
  if (readAccelerometer){
    readAccelerometer = false;
    readAccelerometerData();
    
    // if (abs(GyX) > 25000 || abs(GyY) > 25000 || abs(GyZ) > 25000) sweepDetected = true;

    if (GyX > 25000){
      sweepDetected = true;
      colorIndex = 0;
    }

    if (GyX < -25000){
      sweepDetected = true;
      colorIndex = 1;
    }

    if (GyZ > 25000){
      sweepDetected = true;
      colorIndex = 2;
    }

    if (GyZ < -25000){
      sweepDetected = true;
      colorIndex = 3;
    }

    if (sweepDetected && abs(GyX) < 500 && abs(GyZ) < 500) stopDetected = true;

    if (sweepDetected && stopDetected){
      sweepDetected = false;
      stopDetected = false;
      stripePosition = -10;
      stripeEnabled = true;
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

  // if (ledMillis > 0) ledMillis--;
  // else{
  //   ledMillis = 5000;
    
  //   stripePosition = -10;
  //   stripeEnabled = true;
  // }
}

void secondTick(){
  Serial.print(".");
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
    leds[i] = CHSV(colors[colorIndex], 255, brightness);
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
