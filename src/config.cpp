
#include <EEPROM.h>
#include "config.h"

bool wifi_configured = false;
String wifi_ssid;
String wifi_password;

void ReadConfig()
{
	if (!EEPROM.begin(65))
	{
		Serial.println("Unable to access EEPROM");
		return;
	}
	int eepromAddress = 0;
	wifi_configured = EEPROM.readBool(eepromAddress);
	eepromAddress += 1;
	if (wifi_configured)
	{
		wifi_ssid = EEPROM.readString(eepromAddress);
		if (wifi_ssid == "0")
		{
			wifi_configured = false;
			wifi_ssid = "";

		}
		else
		{
			eepromAddress += 32 + 1;
			wifi_password = EEPROM.readString(eepromAddress);
			eepromAddress += 32 + 1;

		}
	}
	Serial.println("Reading WiFi config from EEPROM : " + wifi_ssid + "/" + wifi_password);
}

bool WriteWlanConfig(String ssid, String password)
{
	if (!EEPROM.begin(65))
	{
		Serial.println("Unable to access EEPROM");
		return false;
	}
	Serial.println("Writing WiFi info to EEPROM : " + ssid + "/" + password);
	int eepromAddress = 0;
	wifi_configured = ssid.length() > 0;
	wifi_ssid = ssid;
	wifi_password = password;

	EEPROM.writeBool(eepromAddress, wifi_configured);
	if (wifi_configured)
	{
		eepromAddress += 1;
		EEPROM.writeString(eepromAddress, wifi_ssid);
		eepromAddress += 32 + 1;
		EEPROM.writeString(eepromAddress, wifi_password);
		eepromAddress += 32 + 1;
	}
	if (!EEPROM.commit())
	{
		Serial.println("Unable to access EEPROM");
		return false;
	}
	return true;
}

bool ConfigIsWifiConfigured() 
{
	return wifi_configured;
}

String ConfigGetWifiSSID()
{
	return wifi_ssid;
}

String ConfigGetWifiPassword()
{
	return wifi_password;
}
