#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <Arduino.h>

class MatrixClockWebServer
{
  public:
	void begin();
	void loop();
};

extern MatrixClockWebServer matrixClockWebServer;

#endif // WEB_SERVER_H
