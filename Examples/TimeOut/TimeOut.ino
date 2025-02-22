/**/
#include <Arduino.h>
#include <TimeOut.h>

/*Set pin numbers*/
const int LED_BUILTIN = 2;

bool ledstate = LOW;

TimeOut TO_main(1000);

void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop(){
  if(TO_main.Expired()){
    TO_main.Update(1000); // Update restart timeout.
    digitalWrite(LED_BUILTIN, ledstate = !ledstate);  // Blink LED
  }
}