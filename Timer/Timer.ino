#include <TimerTC3.h>

int ticks = 0;

void setup() {
  // put your setup code here, to run once:
  TimerTc3.initialize(1000);
  TimerTc3.attachInterrupt(millisTick);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void millisTick()
{
  ticks++;
  if (ticks == 1000){
    ticks = 0;
    secondTick();
  }
}

void secondTick(){
  Serial.print(".");
}
