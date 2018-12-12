#ifndef SETTINGS_H
#define SETTINGS_H
#include <Arduino.h>

class Settings
{
  public:
	void begin() { read(); }
	void read();
	bool isWiFiConfigured() const { return m_wifiConfigured; }
	const String &getWiFiSSID() const { return m_wifiSSID; }
	const String &getWiFiPassword() const { return m_wifiPassword; }
	bool writeWiFiConfig(const char *ssid, const char *password);

  private:
	bool m_wifiConfigured{false};
	String m_wifiSSID;
	String m_wifiPassword;
};

extern Settings settings;

#endif // SETTINGS_H