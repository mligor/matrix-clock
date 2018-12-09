#ifndef STATUS_LED_H
#define STATUS_LED_H

#include <Arduino.h>

class StatusLed
{
public:
	using StatusLedMode = enum StatusLedMode{
		On,
		Off,
		BlinkFast,
		BlinkMiddle,
		BlinkSlow
	};

public:
	void begin(int pin);
	void loop();
	void setMode(StatusLedMode newMode) { m_mode = newMode; }
private:
	int m_pin{-1};
	StatusLedMode m_mode{ StatusLed::Off };
	unsigned long m_lastMillis{ 0 };
	bool m_lastLedState{ false };
};

#endif // STATUS_LED_H