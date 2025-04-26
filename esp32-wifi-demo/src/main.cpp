#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char *SERVER = "http://";

void initWiFi()
{
  const char *WIFI_SSID = "";
  const char *WIFI_PASSWORD = "";

  WiFi.mode(WIFI_OFF);
  delay(1000);
  WiFi.mode(WIFI_STA);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting to WiFi.");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    switch (WiFi.status())
    {
    case WL_CONNECT_FAILED:
      Serial.println("connection failed");
      break;
    
    case WL_NO_SSID_AVAIL:
      Serial.println("ssid search failed");
      break;
    case WL_IDLE_STATUS:
      Serial.println("idle status");
      break;
    case WL_SCAN_COMPLETED:
      Serial.println("scan complete, connecting...");
      break;
    default:
      break;
    }
  }

  Serial.print("\nIP: ");
  Serial.print(WiFi.localIP());
  Serial.print('\n');
}

void setup()
{
  Serial.begin(115200);
  initWiFi();
}

void loop()
{
  if(WiFi.status() != WL_CONNECTED) initWiFi();

  delay(1000);
}
