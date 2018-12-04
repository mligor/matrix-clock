
#include <EEPROM.h>
#include "config.h"

bool wifi_configured = false;
String wifi_ssid;
String wifi_password;

void ReadConfig()
{
	// As the WriteWlanConfig is not working, we return hard coded settings
	wifi_configured = true;
	wifi_ssid = "_my_ssid_";
	wifi_password = "_my_password_";
	return;

	int eepromAddress = 0;
	wifi_configured = EEPROM.readBool(eepromAddress);
	eepromAddress += sizeof(bool);
	wifi_ssid = EEPROM.readString(eepromAddress);
	eepromAddress += 32 + 1;
	wifi_password = EEPROM.readString(eepromAddress);
	eepromAddress += 32 + 1;
}

//TODO: not sure why this code will not write data to EEPROM
void WriteWlanConfig(String ssid, String password)
{
	int eepromAddress = 0;
	wifi_configured = ssid.length() > 0;
	wifi_ssid = ssid;
	wifi_password = password;

	EEPROM.writeBool(eepromAddress, wifi_configured);
	if (wifi_configured)
	{
		eepromAddress += sizeof(bool);
		EEPROM.writeString(eepromAddress, wifi_ssid);
		eepromAddress += 32 + 1;
		EEPROM.writeString(eepromAddress, wifi_password);
		eepromAddress += 32 + 1;
	}
	delay(1000); // Give a chance to write to EEPROM;
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
