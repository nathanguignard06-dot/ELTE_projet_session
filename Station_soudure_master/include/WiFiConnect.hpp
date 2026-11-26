#ifndef WIFICONNECT
#define WIFICONNECT

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <Preferences.h>
#include "CreateMaster.hpp"
#include "Oled.hpp"

class WiFiConnect
{
    public:

        WiFiConnect(const char ssidAP[], Oled& screen);

        bool begin();

        void wifiAPmode();
        void getAPIP();
        bool wifiConnectToRouter(const char ssid[], const char pass[]);
        void handleClient();
        bool isConnected();
        void getMac();

    private:

        const char* SSID_AP;        
        IPAddress IP;
        WebServer server;
        Preferences preferences;
        String mac;
        Oled& oled;

        void handleRoot();
        void handleCredentials();

};
#endif