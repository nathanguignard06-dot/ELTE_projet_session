#include "WiFiConnect.hpp"

WiFiConnect::WiFiConnect(char* ssid): SSID(ssid) {}

int32_t WiFiConnect::getWiFiChannel(const char* ssid)
{
    if (int32_t n = WiFi.scanNetworks()) {
      for (uint8_t i=0; i<n; i++) {
          if (!strcmp(ssid, WiFi.SSID(i).c_str())) {
              return WiFi.channel(i);
          }
      }
  }
  return 0;
}

int32_t WiFiConnect::init()
{
    WiFi.mode(WIFI_STA);

    CHANNEL = getWiFiChannel(SSID);

    return CHANNEL;
}