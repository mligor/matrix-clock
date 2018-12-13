#include <Arduino.h>
#include "settings.h"
#include "terminal.h"
#include "wifi_network.h"
#include "status_led.h"
#include "web_server.h"
#include "notifications.h"

// StatusLed needs to create own instance as it is possible to have multiple LEDs
StatusLed statusLed;

void setup()
{
	// Initialize serial (required for logging and terminal)
	Serial.begin(115200);
	// Configure statusLed class - using Port 2 - connected with intern blue LED (DOIT Esp32 DevKit v1 specific)
	statusLed.begin(2);
	// Initialize settings class (reading/saving settings data to EEPROM)
	settings.begin();
	// Initialize terminal - provide possibility to read commands from Serial port
	terminal.begin();
	// Initialize WiFi network and connect it to status led
	wifi_network.begin("MatrixClock_0000", IPAddress(10, 0, 0, 1), &statusLed);
	// Initialize web server (handling REST request and static files)
	matrixClockWebServer.begin();
	// Initialize notification engine
	notifications.begin("**.cloudmqtt.com", 13924, "*****", "*****");
}

void loop()
{
	statusLed.loop();
	terminal.loop();
	wifi_network.loop();
	matrixClockWebServer.loop();
	notifications.loop();
}
