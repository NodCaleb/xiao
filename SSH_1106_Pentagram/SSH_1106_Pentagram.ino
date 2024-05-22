#include<Arduino.h>
#include<U8g2lib.h>//Use U8g2 library

// Determine whether to use SPI or I2C protocol
// #ifdef U8X8_HAVE_HW_SPI
// #include<SPI.h>
// #endif
// #ifdef U8X8_HAVE_HW_I2C
#include<Wire.h>
// #endif

float sin_values[360] = {
  0.0000,
  0.0175,
  0.0349,
  0.0523,
  0.0698,
  0.0872,
  0.1045,
  0.1219,
  0.1392,
  0.1564,
  0.1736,
  0.1908,
  0.2079,
  0.2250,
  0.2419,
  0.2588,
  0.2756,
  0.2924,
  0.3090,
  0.3256,
  0.3420,
  0.3584,
  0.3746,
  0.3907,
  0.4067,
  0.4226,
  0.4384,
  0.4540,
  0.4695,
  0.4848,
  0.5000,
  0.5150,
  0.5299,
  0.5446,
  0.5592,
  0.5736,
  0.5878,
  0.6018,
  0.6157,
  0.6293,
  0.6428,
  0.6561,
  0.6691,
  0.6820,
  0.6947,
  0.7071,
  0.7193,
  0.7314,
  0.7431,
  0.7547,
  0.7660,
  0.7771,
  0.7880,
  0.7986,
  0.8090,
  0.8192,
  0.8290,
  0.8387,
  0.8480,
  0.8572,
  0.8660,
  0.8746,
  0.8829,
  0.8910,
  0.8988,
  0.9063,
  0.9135,
  0.9205,
  0.9272,
  0.9336,
  0.9397,
  0.9455,
  0.9511,
  0.9563,
  0.9613,
  0.9659,
  0.9703,
  0.9744,
  0.9781,
  0.9816,
  0.9848,
  0.9877,
  0.9903,
  0.9925,
  0.9945,
  0.9962,
  0.9976,
  0.9986,
  0.9994,
  0.9998,
  1.0000,
  0.9998,
  0.9994,
  0.9986,
  0.9976,
  0.9962,
  0.9945,
  0.9925,
  0.9903,
  0.9877,
  0.9848,
  0.9816,
  0.9781,
  0.9744,
  0.9703,
  0.9659,
  0.9613,
  0.9563,
  0.9511,
  0.9455,
  0.9397,
  0.9336,
  0.9272,
  0.9205,
  0.9135,
  0.9063,
  0.8988,
  0.8910,
  0.8829,
  0.8746,
  0.8660,
  0.8572,
  0.8480,
  0.8387,
  0.8290,
  0.8192,
  0.8090,
  0.7986,
  0.7880,
  0.7771,
  0.7660,
  0.7547,
  0.7431,
  0.7314,
  0.7193,
  0.7071,
  0.6947,
  0.6820,
  0.6691,
  0.6561,
  0.6428,
  0.6293,
  0.6157,
  0.6018,
  0.5878,
  0.5736,
  0.5592,
  0.5446,
  0.5299,
  0.5150,
  0.5000,
  0.4848,
  0.4695,
  0.4540,
  0.4384,
  0.4226,
  0.4067,
  0.3907,
  0.3746,
  0.3584,
  0.3420,
  0.3256,
  0.3090,
  0.2924,
  0.2756,
  0.2588,
  0.2419,
  0.2250,
  0.2079,
  0.1908,
  0.1736,
  0.1564,
  0.1392,
  0.1219,
  0.1045,
  0.0872,
  0.0698,
  0.0523,
  0.0349,
  0.0175,
  0.0000,
  -0.0175,
  -0.0349,
  -0.0523,
  -0.0698,
  -0.0872,
  -0.1045,
  -0.1219,
  -0.1392,
  -0.1564,
  -0.1736,
  -0.1908,
  -0.2079,
  -0.2250,
  -0.2419,
  -0.2588,
  -0.2756,
  -0.2924,
  -0.3090,
  -0.3256,
  -0.3420,
  -0.3584,
  -0.3746,
  -0.3907,
  -0.4067,
  -0.4226,
  -0.4384,
  -0.4540,
  -0.4695,
  -0.4848,
  -0.5000,
  -0.5150,
  -0.5299,
  -0.5446,
  -0.5592,
  -0.5736,
  -0.5878,
  -0.6018,
  -0.6157,
  -0.6293,
  -0.6428,
  -0.6561,
  -0.6691,
  -0.6820,
  -0.6947,
  -0.7071,
  -0.7193,
  -0.7314,
  -0.7431,
  -0.7547,
  -0.7660,
  -0.7771,
  -0.7880,
  -0.7986,
  -0.8090,
  -0.8192,
  -0.8290,
  -0.8387,
  -0.8480,
  -0.8572,
  -0.8660,
  -0.8746,
  -0.8829,
  -0.8910,
  -0.8988,
  -0.9063,
  -0.9135,
  -0.9205,
  -0.9272,
  -0.9336,
  -0.9397,
  -0.9455,
  -0.9511,
  -0.9563,
  -0.9613,
  -0.9659,
  -0.9703,
  -0.9744,
  -0.9781,
  -0.9816,
  -0.9848,
  -0.9877,
  -0.9903,
  -0.9925,
  -0.9945,
  -0.9962,
  -0.9976,
  -0.9986,
  -0.9994,
  -0.9998,
  -1.0000,
  -0.9998,
  -0.9994,
  -0.9986,
  -0.9976,
  -0.9962,
  -0.9945,
  -0.9925,
  -0.9903,
  -0.9877,
  -0.9848,
  -0.9816,
  -0.9781,
  -0.9744,
  -0.9703,
  -0.9659,
  -0.9613,
  -0.9563,
  -0.9511,
  -0.9455,
  -0.9397,
  -0.9336,
  -0.9272,
  -0.9205,
  -0.9135,
  -0.9063,
  -0.8988,
  -0.8910,
  -0.8829,
  -0.8746,
  -0.8660,
  -0.8572,
  -0.8480,
  -0.8387,
  -0.8290,
  -0.8192,
  -0.8090,
  -0.7986,
  -0.7880,
  -0.7771,
  -0.7660,
  -0.7547,
  -0.7431,
  -0.7314,
  -0.7193,
  -0.7071,
  -0.6947,
  -0.6820,
  -0.6691,
  -0.6561,
  -0.6428,
  -0.6293,
  -0.6157,
  -0.6018,
  -0.5878,
  -0.5736,
  -0.5592,
  -0.5446,
  -0.5299,
  -0.5150,
  -0.5000,
  -0.4848,
  -0.4695,
  -0.4540,
  -0.4384,
  -0.4226,
  -0.4067,
  -0.3907,
  -0.3746,
  -0.3584,
  -0.3420,
  -0.3256,
  -0.3090,
  -0.2924,
  -0.2756,
  -0.2588,
  -0.2419,
  -0.2250,
  -0.2079,
  -0.1908,
  -0.1736,
  -0.1564,
  -0.1392,
  -0.1219,
  -0.1045,
  -0.0872,
  -0.0698,
  -0.0523,
  -0.0349,
  -0.0175
 };

float cos_values[360] = {
  1.0000,
  0.9998,
  0.9994,
  0.9986,
  0.9976,
  0.9962,
  0.9945,
  0.9925,
  0.9903,
  0.9877,
  0.9848,
  0.9816,
  0.9781,
  0.9744,
  0.9703,
  0.9659,
  0.9613,
  0.9563,
  0.9511,
  0.9455,
  0.9397,
  0.9336,
  0.9272,
  0.9205,
  0.9135,
  0.9063,
  0.8988,
  0.8910,
  0.8829,
  0.8746,
  0.8660,
  0.8572,
  0.8480,
  0.8387,
  0.8290,
  0.8192,
  0.8090,
  0.7986,
  0.7880,
  0.7771,
  0.7660,
  0.7547,
  0.7431,
  0.7314,
  0.7193,
  0.7071,
  0.6947,
  0.6820,
  0.6691,
  0.6561,
  0.6428,
  0.6293,
  0.6157,
  0.6018,
  0.5878,
  0.5736,
  0.5592,
  0.5446,
  0.5299,
  0.5150,
  0.5000,
  0.4848,
  0.4695,
  0.4540,
  0.4384,
  0.4226,
  0.4067,
  0.3907,
  0.3746,
  0.3584,
  0.3420,
  0.3256,
  0.3090,
  0.2924,
  0.2756,
  0.2588,
  0.2419,
  0.2250,
  0.2079,
  0.1908,
  0.1736,
  0.1564,
  0.1392,
  0.1219,
  0.1045,
  0.0872,
  0.0698,
  0.0523,
  0.0349,
  0.0175,
  0.0000,
  -0.0175,
  -0.0349,
  -0.0523,
  -0.0698,
  -0.0872,
  -0.1045,
  -0.1219,
  -0.1392,
  -0.1564,
  -0.1736,
  -0.1908,
  -0.2079,
  -0.2250,
  -0.2419,
  -0.2588,
  -0.2756,
  -0.2924,
  -0.3090,
  -0.3256,
  -0.3420,
  -0.3584,
  -0.3746,
  -0.3907,
  -0.4067,
  -0.4226,
  -0.4384,
  -0.4540,
  -0.4695,
  -0.4848,
  -0.5000,
  -0.5150,
  -0.5299,
  -0.5446,
  -0.5592,
  -0.5736,
  -0.5878,
  -0.6018,
  -0.6157,
  -0.6293,
  -0.6428,
  -0.6561,
  -0.6691,
  -0.6820,
  -0.6947,
  -0.7071,
  -0.7193,
  -0.7314,
  -0.7431,
  -0.7547,
  -0.7660,
  -0.7771,
  -0.7880,
  -0.7986,
  -0.8090,
  -0.8192,
  -0.8290,
  -0.8387,
  -0.8480,
  -0.8572,
  -0.8660,
  -0.8746,
  -0.8829,
  -0.8910,
  -0.8988,
  -0.9063,
  -0.9135,
  -0.9205,
  -0.9272,
  -0.9336,
  -0.9397,
  -0.9455,
  -0.9511,
  -0.9563,
  -0.9613,
  -0.9659,
  -0.9703,
  -0.9744,
  -0.9781,
  -0.9816,
  -0.9848,
  -0.9877,
  -0.9903,
  -0.9925,
  -0.9945,
  -0.9962,
  -0.9976,
  -0.9986,
  -0.9994,
  -0.9998,
  -1.0000,
  -0.9998,
  -0.9994,
  -0.9986,
  -0.9976,
  -0.9962,
  -0.9945,
  -0.9925,
  -0.9903,
  -0.9877,
  -0.9848,
  -0.9816,
  -0.9781,
  -0.9744,
  -0.9703,
  -0.9659,
  -0.9613,
  -0.9563,
  -0.9511,
  -0.9455,
  -0.9397,
  -0.9336,
  -0.9272,
  -0.9205,
  -0.9135,
  -0.9063,
  -0.8988,
  -0.8910,
  -0.8829,
  -0.8746,
  -0.8660,
  -0.8572,
  -0.8480,
  -0.8387,
  -0.8290,
  -0.8192,
  -0.8090,
  -0.7986,
  -0.7880,
  -0.7771,
  -0.7660,
  -0.7547,
  -0.7431,
  -0.7314,
  -0.7193,
  -0.7071,
  -0.6947,
  -0.6820,
  -0.6691,
  -0.6561,
  -0.6428,
  -0.6293,
  -0.6157,
  -0.6018,
  -0.5878,
  -0.5736,
  -0.5592,
  -0.5446,
  -0.5299,
  -0.5150,
  -0.5000,
  -0.4848,
  -0.4695,
  -0.4540,
  -0.4384,
  -0.4226,
  -0.4067,
  -0.3907,
  -0.3746,
  -0.3584,
  -0.3420,
  -0.3256,
  -0.3090,
  -0.2924,
  -0.2756,
  -0.2588,
  -0.2419,
  -0.2250,
  -0.2079,
  -0.1908,
  -0.1736,
  -0.1564,
  -0.1392,
  -0.1219,
  -0.1045,
  -0.0872,
  -0.0698,
  -0.0523,
  -0.0349,
  -0.0175,
  0.0000,
  0.0175,
  0.0349,
  0.0523,
  0.0698,
  0.0872,
  0.1045,
  0.1219,
  0.1392,
  0.1564,
  0.1736,
  0.1908,
  0.2079,
  0.2250,
  0.2419,
  0.2588,
  0.2756,
  0.2924,
  0.3090,
  0.3256,
  0.3420,
  0.3584,
  0.3746,
  0.3907,
  0.4067,
  0.4226,
  0.4384,
  0.4540,
  0.4695,
  0.4848,
  0.5000,
  0.5150,
  0.5299,
  0.5446,
  0.5592,
  0.5736,
  0.5878,
  0.6018,
  0.6157,
  0.6293,
  0.6428,
  0.6561,
  0.6691,
  0.6820,
  0.6947,
  0.7071,
  0.7193,
  0.7314,
  0.7431,
  0.7547,
  0.7660,
  0.7771,
  0.7880,
  0.7986,
  0.8090,
  0.8192,
  0.8290,
  0.8387,
  0.8480,
  0.8572,
  0.8660,
  0.8746,
  0.8829,
  0.8910,
  0.8988,
  0.9063,
  0.9135,
  0.9205,
  0.9272,
  0.9336,
  0.9397,
  0.9455,
  0.9511,
  0.9563,
  0.9613,
  0.9659,
  0.9703,
  0.9744,
  0.9781,
  0.9816,
  0.9848,
  0.9877,
  0.9903,
  0.9925,
  0.9945,
  0.9962,
  0.9976,
  0.9986,
  0.9994,
  0.9998
};

int xa, ya, xb, yb, xc, yc, xd, yd, xe, ye;

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
// Set up the constructor, define display type, controller, RAM buffer size, and communication protocol

void setup() {
  // put your setup code here, to run once:
  u8g2.begin();// Initialize the library
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 72; i++){
    // Cycle through image display
    u8g2.firstPage();
    do {
        drawPentagram(64, 32, 20, i);// Use draw function
    } while( u8g2.nextPage() );

    //delay(5);
  }
  
}

void drawPentagram(int x, int y, int rad, int angle) { 
    u8g2.drawCircle(x, y, rad, U8G2_DRAW_ALL);// Draw a full circle with a diameter of 21 at coordinates (20, 25)    

    xa = round((float)x + (float)rad * sin_values[adjustAngle(angle)]);
    ya = round((float)y - (float)rad * cos_values[adjustAngle(angle)]);
    xb = round((float)x + (float)rad * sin_values[adjustAngle(angle + 72)]);
    yb = round((float)y - (float)rad * cos_values[adjustAngle(angle + 72)]);
    xc = round((float)x + (float)rad * sin_values[adjustAngle(angle + 144)]);
    yc = round((float)y - (float)rad * cos_values[adjustAngle(angle + 144)]);
    xd = round((float)x + (float)rad * sin_values[adjustAngle(angle + 216)]);
    yd = round((float)y - (float)rad * cos_values[adjustAngle(angle + 216)]);
    xe = round((float)x + (float)rad * sin_values[adjustAngle(angle + 288)]);
    ye = round((float)y - (float)rad * cos_values[adjustAngle(angle + 288)]);

    // Serial.print(xa);
    // Serial.print(" ");
    // Serial.print(ya);
    // Serial.print(" ");
    // Serial.print(xc);
    // Serial.print(" ");
    // Serial.println(yc);

    u8g2.drawLine(xa, ya, xc, yc);
    u8g2.drawLine(xc, yc, xe, ye);
    u8g2.drawLine(xb, yb, xe, ye);
    u8g2.drawLine(xb, yb, xd, yd);
    u8g2.drawLine(xa, ya, xd, yd);
}

int adjustAngle(int angle){
  while (angle < 0){
    angle += 360;
  };
  while (angle >= 360){
    angle -= 360;
  };

  return angle;
}
