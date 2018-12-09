#ifndef WIFI_NETWORK_H
#define WIFI_NETWORK_H

#include "status_led.h"

#include <WiFiType.h>

class WiFiNetwork
{
  public:
	using RunningMode = enum RunningMode
	{
		Disconnected,
		Configuring,
		Connecting,
		Connected
	};

	void begin(String hostName, IPAddress configIP, StatusLed *satusLed = nullptr);
	void loop();

  private:
	RunningMode m_mode { Disconnected };
	int m_wifiStatus { WL_IDLE_STATUS };
	StatusLed* m_statusLed{ nullptr };
};

extern WiFiNetwork wifi_network;

#endif // WIFI_NETWORK_H