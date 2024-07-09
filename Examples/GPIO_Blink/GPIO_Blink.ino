/**/
#include <GPIOEasy.h>

/*Set pin numbers*/
const int LED_BUILTIN = 2;

IOBlink Led(LED_BUILTIN,HIGH);

void setup() {
	/*IOBlink.Blink(Count, TimeOn, TimeOff)*/
	Led.Blink(2,1000,4000);
}

void loop() {
	/* GPIO handler */
	Led.handller();
}