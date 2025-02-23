/**/
#include <GPIOEasy.h>

/*Set pin numbers*/
const int LED_BUILTIN = 2;

GPIOBlink Led(LED_BUILTIN,HIGH);

void setup() {
	/*IOBlink.Blink(Count, TimeOn, TimeOff)*/
	Led.Blink(100,1000,4000);

  Serial.begin(115200);
}

void loop() {
	/* GPIO handler */
	Led.handler();

  if(Led.isChange()) {
    Serial.println("Led state is change.");
  }
}