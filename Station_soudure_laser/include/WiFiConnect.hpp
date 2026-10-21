#ifndef DEF_WIFICONNECT
#define DEF_WIFICONNECT

#include "Logique.hpp"
#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>

class WiFiConnect
{
    public:

        WiFiConnect(char* ssid);

        int32_t init();
        int32_t getWiFiChannel(const char* ssid);

    private:

        const char* SSID;
        int32_t CHANNEL;
};

#endif