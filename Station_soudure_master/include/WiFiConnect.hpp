#ifndef WIFICONNECT
#define WIFICONNECT

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <Preferences.h>
#include "CreateMaster.hpp"

class WiFiConnect
{
    public:

        WiFiConnect(const char ssidAP[]);

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

        void handleRoot();
        void handleCredentials();

};
#endif