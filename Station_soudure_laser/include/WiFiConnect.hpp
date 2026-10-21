#ifndef DEF_WIFICONNECT
#define DEF_WIFICONNECT

#include <Arduino.h>
#include <WiFi.h>

class WiFiConnect
{
    public:

        WiFiConnect(char ssid[], char pass[]);

        void init();

    private:

        String SSID;
        String PASS;
};

#endif