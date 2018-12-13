#ifndef NOTIFICATIONS_H
#define NOTIFICATIONS_H

#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>

class Notifications
{
  public:
	void begin(String host, int port, String username, String password);
	void loop();
	bool connect();
	void send(String topic, String message);

  private:
	String m_host;
	int m_port{1883};
	String m_username;
	String m_password;
	PubSubClient m_client;
	WiFiClient m_wifiClient;
};

extern Notifications notifications;

#endif // NOTIFICATIONS_H