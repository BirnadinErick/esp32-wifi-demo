#include <Arduino.h>
#include <WiFi.h>
#include <WiFiManager.h>
#include <HTTPClient.h>

const int TOUCH_SENSOR = 35; // GPIO 35
const char *INIT_AP_NAME = "beAP";
const int TIME_INTERVAL = 5 * 1000;

// plz use https in prod, http is just for learning purposes
const char *API = "http://192.168.201.71:2003/save-data";

int sensor_value = 0;
unsigned long timestamp = 0;

void send_data(int data)
{
  WiFiClient wifi_client;
  HTTPClient http_client;

  http_client.begin(wifi_client, API);
  http_client.addHeader("Content-Type", "text/plain");
  auto req = String(data);

  int res = http_client.POST(req);
  Serial.printf("httP res: %d\n", res);
}

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  delay(1000);

  WiFiManager wm;
  bool res;

  Serial.print("connecting to WiFi...");
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
  timestamp = millis();
}

void loop()
{
  if (millis() - timestamp < TIME_INTERVAL)
  {
    goto LOOP_TAIL;
  }

  if (WiFi.status() != WL_CONNECTED)
  {
    ESP.restart();
  }

  sensor_value = analogRead(TOUCH_SENSOR);
  send_data(sensor_value);

LOOP_TAIL:
  timestamp = millis();
}
