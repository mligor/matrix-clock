#include "terminal.h"
#include "settings.h"

Terminal terminal{};

void Terminal::begin()
{
	this->on("wifireset", []()
	{
		settings.writeWiFiConfig("", "");

		//TODO: reconnect is better then restart;
		ESP.restart();
	});
	
	this->on("hi", []()
	{
		Serial.println("Hi to you. How are you today?");
	});
}

Terminal &Terminal::on(const char *command, const Fn fn)
{
	Serial.println("Term added: " + String(command));
	m_commands[String(command)] = fn;
	return *this;
}

void Terminal::loop()
{
	while (Serial.available())
	{
		//TODO: Improve reading multiple commands and detect new line char
		// Read char by char (it should be faster)
		String command = Serial.readString();
		command.trim();

		Serial.println("Term read: " + command);

		FnMap::const_iterator it = m_commands.find(command);
		if (it == m_commands.cend())
		{
			Serial.println("Unknown command: " + command);
			continue;
		}

		if (it->second)
			it->second();
	}
}