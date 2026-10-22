#ifndef DEF_WIFICONNECT
#define DEF_WIFICONNECT

#include "Logique.hpp"
#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>

class WiFiConnect
{
    public:

        WiFiConnect(const char ssid[]);

        int32_t init();
        
        private:
        
        const char* SSID;
        int32_t CHANNEL;
        
        int32_t getWiFiChannel(const char* ssid);
    };

#endif