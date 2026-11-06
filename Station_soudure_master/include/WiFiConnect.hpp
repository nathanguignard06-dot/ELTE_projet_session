#ifndef DEF_WIFICONNECT
#define DEF_WIFICONNECT

#include "Logique.hpp"
#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>

class WiFiConnect
{
    public:

        WiFiConnect(const char ssid[], const char pass[]);

        void init();
        void getMac();
        
        private:
        
        const char* SSID;
        const char* PASS;
        String mac;
    };

#endif