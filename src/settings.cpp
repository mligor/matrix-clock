
#include <EEPROM.h>
#include "settings.h"

Settings settings{};

void Settings::read()
{
	if (!EEPROM.begin(65))
	{
		Serial.println("Unable to access EEPROM");
		return;
	}
	int eepromAddress = 0;
	m_wifiConfigured = EEPROM.readBool(eepromAddress);
	eepromAddress += 1;
	if (m_wifiConfigured)
	{
		m_wifiSSID = EEPROM.readString(eepromAddress);
		if (m_wifiSSID == "0")
		{
			m_wifiConfigured = false;
			m_wifiSSID = "";
		}
		else
		{
			eepromAddress += 32 + 1;
			m_wifiPassword = EEPROM.readString(eepromAddress);
			eepromAddress += 32 + 1;
		}
	}
	Serial.println("Reading WiFi config from EEPROM: " + m_wifiSSID + "/" + m_wifiPassword);
}

bool Settings::writeWiFiConfig(const char *ssid, const char *password)
{
	if (!EEPROM.begin(65))
	{
		Serial.println("Unable to access EEPROM");
		return false;
	}

	m_wifiSSID = ssid;
	m_wifiPassword = password;

	Serial.println("Writing WiFi Config to EEPROM: " + m_wifiSSID + "/" + m_wifiPassword);
	int eepromAddress = 0;
	m_wifiConfigured = m_wifiSSID.length() > 0;

	EEPROM.writeBool(eepromAddress, m_wifiConfigured);
	if (m_wifiConfigured)
	{
		eepromAddress += 1;
		EEPROM.writeString(eepromAddress, m_wifiSSID);
		eepromAddress += 32 + 1;
		EEPROM.writeString(eepromAddress, m_wifiPassword);
		eepromAddress += 32 + 1;
	}
	if (!EEPROM.commit())
	{
		Serial.println("Unable to access EEPROM");
		return false;
	}
	return true;
}
