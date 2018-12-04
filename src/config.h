#ifndef CONFIG_H
#define CONFIG_H
#include <Arduino.h>

void ReadConfig();
bool ConfigIsWifiConfigured();
String ConfigGetWifiSSID();
String ConfigGetWifiPassword();

#endif