#ifndef _WEBINTERFACE_H_
#define _WEBINTERFACE_H_

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

extern byte cooling;
extern byte sparking;
extern byte brightness;

extern ESP8266WebServer server;

void setupWiFi(void);
void setupWebServer(void);

#endif //_WEBINTERFACE_H_
