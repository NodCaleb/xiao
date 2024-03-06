#include <TimerTC3.h>
#include<Wire.h>
const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
int led = D10;

int secondsTicks = 0;
int accsTicks = 0;
int ledMillis = 0;
bool readAccelerometer = false;
bool sweepDetected = false;
bool stopDetected = false;

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

  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (readAccelerometer){
    readAccelerometer = false;
    readAccelerometerData();
    
    if (abs(GyX) > 25000 || abs(GyY) > 25000 || abs(GyZ) > 25000) sweepDetected = true;
    if (sweepDetected && abs(GyX) < 500 && abs(GyY) < 500 && abs(GyZ) < 500) stopDetected = true;

    if (sweepDetected && stopDetected){
      sweepDetected = false;
      stopDetected = false;
      ledMillis = 2000;
    }

  }

  if (ledMillis > 0){
    digitalWrite(led, HIGH); 
  }
  else{
    digitalWrite(led, LOW); 
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
  if (accsTicks == 10){
    accsTicks = 0;
    readAccelerometer = true;
  }

  if (ledMillis > 0) ledMillis--;
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

