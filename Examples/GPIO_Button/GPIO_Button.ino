/**/
#include <GPIOEasy.h>

/*Set pin numbers*/
const int LED_BUILTIN = 2;
const int BUTTON = 0;

IOBlink Led(LED_BUILTIN,HIGH);

IOInput Button(BUTTON,INPUT,LOW);

void setup() {
	/*IOBlink.Blink(Count, TimeOn, TimeOff)*/
	Led.Blink(2,1000,4000);
}

void loop() {
	/* GPIO handler */
	Led.handller();
	Button.handller();

	if(Button.GetTimeActive() >= 3000) {
		Led.Blink(2,100,1000);
	}
	
}