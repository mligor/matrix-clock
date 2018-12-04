#include "status_led.h"

void status_led(int pin, StatusLedMode mode)
{
	static byte lastState = 0;
	static unsigned long lastMillis = millis();
	unsigned long currentMillis = millis();
	
	switch (mode)
	{
		case slmOff:
		case slmOn:
			lastState = (mode == slmOn) ? 1 : 0;
			lastMillis = currentMillis;
			digitalWrite(pin, lastState);
			break;

		case slmBlinkFast:
		case slmBlinkMiddle:
		case slmBlinkSlow:
			int blinkTime = (mode == slmBlinkFast) ? 100 : ( mode == slmBlinkMiddle ? 500 : 2000 );
			if (currentMillis < lastMillis /* overflow */ || currentMillis - lastMillis >= blinkTime)
			{
				lastMillis = currentMillis;
				lastState ^= 1;
				digitalWrite(pin, lastState);
			}
	}
}
