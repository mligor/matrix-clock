#include <Arduino.h>

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#include <WiFi.h>
#include <EEPROM.h>

#include "config.h"
#include "status_led.h"
#include "web_server.h"


// ESP: SP32 240MHz 320KB RAM (4MB Flash)

const char *ConfigSSID = "MatrixClock_0000";
IPAddress ConfigIP(10, 0, 0, 1);
IPAddress ConfigGateway(10, 0, 0, 1);
IPAddress ConfigSubnet(255, 255, 255, 0);

// Configuration
#define STATUS_LED 2

enum RunningMode
{
	rmUnknown = 0,
	rmConfigure,
	rmConnecting,
	rmRunning
};

RunningMode runningMode{rmUnknown};
StatusLedMode statusLedMode{slmOff};
int wifiStatus = WL_IDLE_STATUS;

void ReadFromTerminal()
{
	if (Serial.available())
	{
		String command = Serial.readString();
		command.trim();
		Serial.println("CMD: " + command);

		if (command == "wifireset")
		{
			WriteWlanConfig("", "");
			ESP.restart();
		}
	}	
}


void setup()
{
	Serial.begin(115200);
	pinMode(STATUS_LED, OUTPUT);
	delay(10);

	ReadConfig();

	if (!ConfigIsWifiConfigured())
	{
		WiFi.mode(WIFI_AP);

		runningMode = rmConfigure;
		statusLedMode = slmBlinkFast;

		Serial.print("Setting soft-AP configuration ... ");
  		Serial.println(WiFi.softAPConfig(ConfigIP, ConfigGateway, ConfigSubnet) ? "Ready" : "Failed!");
	
		Serial.print("Setting soft-AP ... ");
  		Serial.println(WiFi.softAP(ConfigSSID, nullptr, 1, false, 1) ? "Ready" : "Failed!");

		Serial.print("Soft-AP IP address = ");
		Serial.println(WiFi.softAPIP());
		StartWebServer();
	}
	else
	{
		WiFi.mode(WIFI_STA);
		WiFi.setHostname(ConfigSSID);

		Serial.printf("Connecting to WiFi: %s\n", ConfigGetWifiSSID().c_str());
		runningMode = rmConnecting;
		statusLedMode = slmBlinkMiddle;
		WiFi.begin(ConfigGetWifiSSID().c_str(), ConfigGetWifiPassword().c_str());
	}
}

void loop()
{
	status_led(STATUS_LED, statusLedMode);
	ReadFromTerminal();

	if (runningMode == rmConnecting)
	{
		delay(100);
		wifiStatus = WiFi.status();
		if (wifiStatus == WL_CONNECTED)
		{
			runningMode = rmRunning;
			statusLedMode = slmBlinkSlow;
			IPAddress ip = WiFi.localIP();
			Serial.print("Connected with ip ");
			Serial.println(ip);
			StartWebServer();
		}
		else
		{
			return; // don't allow process requests
		}
	}

	ProcessWebServerRequests();
	delay(10);
}