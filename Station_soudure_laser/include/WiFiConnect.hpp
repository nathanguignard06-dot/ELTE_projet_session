#ifndef DEF_WIFICONNECT
#define DEF_WIFICONNECT

#include <Arduino.h>
#include <WiFi.h>

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