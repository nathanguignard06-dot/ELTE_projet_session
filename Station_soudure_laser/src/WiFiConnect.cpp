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

    //WiFi.printDiag(Serial); // Uncomment to verify channel number before
    esp_wifi_set_promiscuous(true);
    esp_wifi_set_channel(CHANNEL, WIFI_SECOND_CHAN_NONE);
    esp_wifi_set_promiscuous(false);
    //WiFi.printDiag(Serial); // Uncomment to verify channel change after

    return CHANNEL;
}