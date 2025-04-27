#include <Arduino.h>
#include <WiFi.h>
#include <WiFiManager.h>

const int TOUCH_SENSOR = 35;
const char *INIT_AP_NAME = "beAP";

int sensor_value = 0;

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  delay(1000);

  WiFiManager wm;
  bool res;

  Serial.print("connecting to WiFi...");
  // wm.resetSettings();
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

  pinMode(TOUCH_SENSOR, INPUT);
}

void loop()
{
  sensor_value = analogRead(TOUCH_SENSOR);
  Serial.println(sensor_value);

  delay(1000);
}
