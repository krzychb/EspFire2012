#include "WebInterface.h"

const char* ssid = "********";
const char* password = "********";

ESP8266WebServer server(80);

void showControlScreen(void)
{
	String message;
  message += "<html>";
  message += "<head><meta http-equiv=\"refresh\" content=\"20; url='/\"'><title>EspFire2012 Control</title></head>";
  message += "<body>";
  message += "<h3><a href=\"https://github.com/krzychb\">EspFire2012</a></h3>";
	message += "<form action=\"/\" method=\"get\">";
  message += "Brightness <input type=\"text\" name=\"brightness\" size=\"3\" value=\"" + (String) brightness + "\"><input type=\"submit\" value=\"Submit\"> (0-255)";
  message += "</form>";
  message += "<form action=\"/\" method=\"get\">";
  message += "Cooling <input type=\"text\" name=\"cooling\" size=\"3\" value=\"" + (String) cooling + "\"><input type=\"submit\" value=\"Submit\"> (20-100)";
  message += "</form>";
  message += "<form action=\"/\" method=\"get\">";
  message += "Sparking <input type=\"text\" name=\"sparking\" size=\"3\" value=\"" + (String) sparking + "\"><input type=\"submit\" value=\"Submit\"> (50-200)";
  message += "</form>";
  message += "Based on Fire2012 by <a href=\"https://twitter.com/markkriegsman\">Mark Kriegsman</a>";
  message += "</body>";
  message += "</html>";
  server.send(200, "text/html", message);
}

void handleNotFound(void)
{
	String message = "File Not Found\n\n";
	message += "URI: ";
	message += server.uri();
	message += "\nMethod: ";
	message += (server.method() == HTTP_GET) ? "GET" : "POST";
	message += "\nArguments: ";
	message += server.args();
	message += "\n";
	for (uint8_t i=0; i<server.args(); i++)
	{
		message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
	}
	server.send(404, "text/plain", message);
}


void setupWiFi(void)
{
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
		Serial.print(".");
	}
	Serial.println();
	Serial.print("Connected to ");
	Serial.println(ssid);
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());
}


void setupWebServer(void)
{
	server.on("/", []() {
		Serial.print("HTTP REQUEST > ");

		for (uint8_t i = 0; i < server.args(); i++)
		{
			if (server.argName(i) == "brightness")
			{
				brightness = (byte) server.arg(i).toInt();
			}
			else if (server.argName(i) == "cooling")
			{
				cooling = (byte) server.arg(i).toInt();
			}
			else if (server.argName(i) == "sparking")
			{
				sparking = (byte) server.arg(i).toInt();
			}
			else
			{
				Serial.println("unknown argument! ");
			}
			Serial.print(server.argName(i));
			Serial.print(": ");
			Serial.print(server.arg(i));
			Serial.print(" > ");
		}
		Serial.println("done");

		showControlScreen();
	});

	server.onNotFound(handleNotFound);

	server.begin();
	Serial.println("HTTP server started");
}
