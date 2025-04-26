#include <Arduino.h>
#include <WiFi.h>
#include <WiFiManager.h>

const char *INIT_AP_NAME = "";

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  delay(1000);

  WiFiManager wm;
  bool res;

  Serial.print("connecting to WiFi...");
  wm.resetSettings();
  res = wm.autoConnect(INIT_AP_NAME);

  if (res)
  {
    Serial.println("done.");
  }
  else
  {
    Serial.println("failed! restarting...");
    ESP.restart();
  }
}

void loop()
{
}
