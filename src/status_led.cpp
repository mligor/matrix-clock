#include "status_led.h"

void StatusLed::begin(int pin)
{
	m_pin = pin;
	pinMode(m_pin, OUTPUT);
}

void StatusLed::loop()
{
	unsigned long currentMillis = millis();

	switch (m_mode)
	{
	case StatusLed::Off:
	case StatusLed::On:
	{
		bool newLedState = (m_mode == StatusLed::On);
		if (newLedState != m_lastLedState)
		{
			digitalWrite(m_pin, newLedState ? 1 : 0);
			m_lastLedState = newLedState;
		}
		m_lastMillis = currentMillis;
	}
	break;

	case StatusLed::BlinkFast:
	case StatusLed::BlinkMiddle:
	case StatusLed::BlinkSlow:
	{
		int blinkTime = (m_mode == StatusLed::BlinkFast) ? 100 : (m_mode == StatusLed::BlinkMiddle ? 500 : 2000);
		if (currentMillis < m_lastMillis /* overflow */ || currentMillis - m_lastMillis >= blinkTime)
		{
			m_lastMillis = currentMillis;
			m_lastLedState = !m_lastLedState;
			digitalWrite(m_pin, m_lastLedState ? 1 : 0);
		}
	}
	}
}
