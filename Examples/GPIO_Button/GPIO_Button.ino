/**/
#include <GPIOEasy.h>

/*Set pin numbers*/
const int BUTTON = 0;

GPIOInput Button(BUTTON,LOW);

void setup() {
  Serial.begin(115200);
}

void loop() {
	/* GPIO handler */
	if(Button.actived()) {
		Serial.println("Button is Actived !");
	}

	if(Button.inactived()) {
		Serial.println("Button is Inactived !");
	}

	if(Button.timeChange() > 3000 && Button.isActive()) {
		Serial.println("Button is actived more than 3 seconds!");
		delay(1000);
	}
}