#include<Arduino.h>
#include<U8g2lib.h>//Use U8g2 library
#include<Wire.h>

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
//Set the constructor, define the display type, controller, RAM buffer size, and communication protocol, generally determine according to the used display model

void setup(void) {
    u8g2.begin();//Initialize u8x8 library
    //u8g2.setFlipMode(0);//Flip the display 180 degrees, generally numbers 0 and 1
    
}

void loop(void) {
    u8g2.firstPage();
    do {
        //u8g2.setFont(u8x8_font_chroma48medium8_r);//Define u8x8 font
        // u8g2.setCursor(0, 0);//Set the position of the drawing cursor
        // u8g2.print("Hello World!");//Draw content on OLED: Hello World
        u8g2.drawLine(5, 15, 7, 27);
    } while( u8g2.nextPage() );
    
}