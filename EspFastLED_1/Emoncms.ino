#include "Emoncms.h"

WiFiClient client;

#define UPDATE_PERIOD 60000
#define TIMEOUT_PERIOD 1000
const char* dataHost = "emoncms.org";
const char* apiKey = "9a3e3c9cf65c70a597097b065dcb24e3";
long dataLogTimer;

#ifdef ESP8266
extern "C" {
#include "user_interface.h"
}
#endif


void logToEmoncms(void)
{
  if (millis() < dataLogTimer + UPDATE_PERIOD)
  {
    return;
  }
  dataLogTimer = millis();

  Serial.print("DATA LOG > ");
  Serial.print(dataHost);
  Serial.print(" > ");

  if (!client.connect(dataHost, 80))
  {
    Serial.print("Connection failure!");
    return;
  }

  Serial.print("Sending data > ");
  String message;
  message += "GET http://" + (String) dataHost;
  message += "/input/post.json?json={";
  message += "EspFastLED_1_UpTime:" + String (dataLogTimer / 60000) + ",";
  message += "EspFastLED_1_HeapSize:" + String (system_get_free_heap_size());
  message += "}&apikey=" + (String) apiKey + "\n";
  message += "Connection: close\n\n";
  client.print(message);

  while (client.available() == 0)
  {
    if (millis() > dataLogTimer + TIMEOUT_PERIOD)
    {
      Serial.println("Reply timeout!");
      client.stop();
      return;
    }
  }

  while (client.available())
  {
    Serial.write(client.read());
  }
  Serial.print(" > Done");
  client.stop();
  
  // show time to log the data on Emoncms
  Serial.print(" in ");
  Serial.print(millis()-dataLogTimer);
  Serial.println("ms");
}

