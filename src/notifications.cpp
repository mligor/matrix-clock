#include "notifications.h"
#include "wifi_network.h"
#include "ArduinoJson.h"

Notifications notifications{};

void mqtt_client_callback(char *topic, byte *payload, unsigned int length)
{
	if (length > 1024)
	{
		Serial.printf("mqtt message for topic '%s' too large\n", topic);
		return;
	}

	StaticJsonBuffer<1024> jsonBuffer;
	JsonObject &root = jsonBuffer.parseObject(payload, length);

	// handle message arrived

	if (root["msg"] == "hi")
	{
		notifications.send("msg", "Hi to you. How are you doing today?");
	}

	Serial.printf("Notification: %s :\n", topic);
	root.printTo(Serial);
	Serial.println();
}

void Notifications::begin(String host, int port, String username, String password)
{
	m_host = host;
	m_port = port;
	m_username = username;
	m_password = password;
	m_wifiClient = WiFiClient();
	m_client = PubSubClient(m_host.c_str(), m_port, mqtt_client_callback, m_wifiClient);
}

bool Notifications::connect()
{
	String clientId = "MatrixClock-";
	clientId += String(random(0xffff), HEX);

	if (!m_client.connect(clientId.c_str(), m_username.c_str(), m_password.c_str()))
	{
		Serial.printf("Unable to connect\n");
		return false;
	}
	m_client.publish("outTopic", "hello world");
	if (!m_client.subscribe("#"))
	{
		Serial.printf("Unable to subscribe\n");
		return false;
	}
	return true;
}

void Notifications::loop()
{
	if (m_client.connected())
		m_client.loop();
	else
	{
		if (WiFi.isConnected())
			connect();
	}
}

void Notifications::send(String topic, String message)
{
	if (m_client.connected())
		m_client.publish(topic.c_str(), message.c_str());
}