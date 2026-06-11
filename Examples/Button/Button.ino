#include <Button.h>

Button button1(2, LOW); // Connect your button between pin 2 and GND
Button button2(3, LOW); // Connect your button between pin 3 and GND
Button button3(4, LOW); // Connect your button between pin 4 and GND

void setup() {
	button1.begin();
	button2.begin();
	button3.begin();
	
	while (!Serial) { }; // for Leos
	Serial.begin(9600);
}

void loop() {
	if (button1.pressed())
		Serial.println("Button 1 pressed");
	
	if (button2.released())
		Serial.println("Button 2 released");
	
	if (button3.toggled()) {
		Serial.println("Button 3 has been toggled");
	}
}