#include "WiFiConnect.hpp"

WiFiConnect::WiFiConnect(const char ssid[], const char pass[]): SSID(ssid), PASS(pass) {}

void WiFiConnect::init()
{
    WiFi.mode(WIFI_AP_STA);

        Serial.print("Connecting to ");
    Serial.println(SSID);

    WiFi.begin(SSID, PASS);

    int attempts = 0;
    const int maxAttempts = 20;

    while(WiFi.status() != WL_CONNECTED && attempts < maxAttempts)
    {
        Serial.print(".");
        delay(1000);
        attempts++;
    }

    if(WiFi.status() == WL_CONNECTED)
    {
        Serial.println();
        Serial.println("WiFi connected!");

        Serial.print("Station IP: ");
        Serial.println(WiFi.localIP());

        Serial.print("WiFi channel: ");
        Serial.println(WiFi.channel());
    }
    else
    {
        Serial.println();
        Serial.println("WiFi connection failed!");

        Serial.print("WiFi status: ");
        Serial.println(WiFi.status());
    }
}

void WiFiConnect::getMac()
{
    mac = WiFi.macAddress();
    Serial.print("MAC address : ");
    Serial.println(mac);
}