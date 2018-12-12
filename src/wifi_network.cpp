#include "wifi_network.h"
#include "settings.h"
#include <WiFi.h>

WiFiNetwork wifi_network{};

void WiFiNetwork::begin(String hostName, IPAddress configIP, StatusLed *satusLed)
{
	m_statusLed = satusLed;
	m_hostName = hostName;
	m_configIP = configIP;
}

void WiFiNetwork::loop()
{
	if (m_mode == Connecting)
	{
		m_wifiStatus = WiFi.status();
		if (m_wifiStatus == WL_CONNECTED)
		{
			m_mode = Connected;
			if (m_statusLed)
				m_statusLed->setMode(StatusLed::BlinkSlow);

			IPAddress ip = WiFi.localIP();
			Serial.print("Connected with ip ");
			Serial.println(ip);
		}
		else
		{
			//TODO:  handle disconnects or timeouts
		}
	}
}

void WiFiNetwork::connect()
{
	if (!settings.isWiFiConfigured())
		connectInConfigMode();
	else
	{
		WiFi.mode(WIFI_STA);
		WiFi.setHostname(m_hostName.c_str());

		Serial.printf("Connecting to WiFi: %s\n", settings.getWiFiSSID().c_str());
		m_mode = Connecting;
		if (m_statusLed)
			m_statusLed->setMode(StatusLed::BlinkMiddle);
		WiFi.begin(settings.getWiFiSSID().c_str(), settings.getWiFiPassword().c_str());
	}
}

void WiFiNetwork::connectInConfigMode()
{
	WiFi.mode(WIFI_AP);

	m_mode = Configuring;
	if (m_statusLed)
		m_statusLed->setMode(StatusLed::BlinkFast);

	IPAddress ConfigGateway(10, 0, 0, 1);
	IPAddress ConfigSubnet(255, 255, 255, 0);

	Serial.print("Setting soft-AP configuration ... ");
	Serial.println(WiFi.softAPConfig(m_configIP, m_configIP, IPAddress(255, 255, 255, 0)) ? "Ready" : "Failed!");

	Serial.print("Setting soft-AP ... ");
	Serial.println(WiFi.softAP(m_hostName.c_str(), nullptr, 1, false, 1) ? "Ready" : "Failed!");

	Serial.print("Soft-AP IP address = ");
	Serial.println(WiFi.softAPIP());
}

void WiFiNetwork::disconnect()
{
	WiFi.disconnect(true);
	m_mode = Disconnected;
	m_statusLed->setMode(StatusLed::Off);
}
