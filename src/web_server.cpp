#include "web_server.h"

WiFiServer server(80);
String header;
String output5State = "off";
String output4State = "off";

extern const char favicon_ico[] asm("_binary_html_favicon_ico_start");
extern const char index_html[] asm("_binary_html_index_html_start");
extern const char main_js[] asm("_binary_html_main_js_start");
extern const char polyfills_js[] asm("_binary_html_polyfills_js_start");
extern const char runtime_js[] asm("_binary_html_runtime_js_start");
extern const char styles_js[] asm("_binary_html_styles_js_start");

extern const char favicon_ico_end[] asm("_binary_html_favicon_ico_end");
extern const char index_html_end[] asm("_binary_html_index_html_end");
extern const char main_js_end[] asm("_binary_html_main_js_end");
extern const char polyfills_js_end[] asm("_binary_html_polyfills_js_end");
extern const char runtime_js_end[] asm("_binary_html_runtime_js_end");
extern const char styles_js_end[] asm("_binary_html_styles_js_end");


void StartWebServer()
{
	server.begin();
}

void ProcessWebServerRequests()
{
	WiFiClient client = server.available(); // Listen for incoming clients

	if (client)
	{								   // If a new client connects,
		Serial.println("New Client."); // print a message out in the serial port
		String currentLine = "";	   // make a String to hold incoming data from the client
		while (client.connected())
		{ // loop while the client's connected
			if (client.available())
			{							// if there's bytes to read from the client,
				char c = client.read(); // read a byte, then
				Serial.write(c);		// print it out the serial monitor
				header += c;
				if (c == '\n')
				{ // if the byte is a newline character
					// if the current line is blank, you got two newline characters in a row.
					// that's the end of the client HTTP request, so send a response:
					if (currentLine.length() == 0)
					{
						// HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
						// and a content-type so the client knows what's coming, then a blank line:
						client.println("HTTP/1.1 200 OK");
						client.println("Connection: close");

						//TODO: some files are too large to send it with single write operation
						if (header.indexOf("GET /favicon.ico") >= 0)
						{
							client.println("Content-type:image/x-icon");
							client.println();
							client.write(favicon_ico, favicon_ico_end - favicon_ico - 1);
							client.flush();
						}
						else if (header.indexOf("GET /main.js") >= 0)
						{
							client.println("Content-type:application/javascript; charset=utf-8");
							client.println();
							client.write(main_js, main_js_end - main_js - 1);
							client.flush();
						}
						else if (header.indexOf("GET /polyfills.js") >= 0)
						{
							client.println("Content-type:application/javascript; charset=utf-8");
							client.println();
							client.write(polyfills_js, polyfills_js_end - polyfills_js - 1);
							client.flush();
						}
						else if (header.indexOf("GET /runtime.js") >= 0)
						{
							client.println("Content-type:application/javascript; charset=utf-8");
							client.println();
							client.write(runtime_js, runtime_js_end - runtime_js - 1);
							client.flush();
						}
						else if (header.indexOf("GET /styles.js") >= 0)
						{
							client.println("Content-type:application/javascript; charset=utf-8");
							client.println();
							client.write(styles_js, styles_js_end - styles_js - 1);
							client.flush();
						}
						else if (header.indexOf("GET /scan") >= 0)
						{
							int numSsid = WiFi.scanNetworks();
							for (int thisNet = 0; thisNet < numSsid; thisNet++) {
								Serial.print(thisNet);
								Serial.print(") ");
								Serial.print(WiFi.SSID(thisNet));
								Serial.print("\tSignal: ");
								Serial.print(WiFi.RSSI(thisNet));
								Serial.print(" dBm");
								Serial.println("");
							}
						}
						else if (header.indexOf("GET /set") >= 0)
						{
							//WriteWlanConfig("_ssid_", "_password_");
							//Reset
							ESP.restart();
  						}
						else 
						{
							client.println("Content-type:text/html; charset=UTF-8");
							client.println();
							client.write(index_html, index_html_end - index_html - 1);
							client.flush();
						}
						break;
					}
					else
					{ // if you got a newline, then clear currentLine
						currentLine = "";
					}
				}
				else if (c != '\r')
				{					  // if you got anything else but a carriage return character,
					currentLine += c; // add it to the end of the currentLine
				}
			}
		}
		// Clear the header variable
		header = "";
		// Close the connection
		client.stop();
		Serial.println("Client disconnected.");
	}
}
