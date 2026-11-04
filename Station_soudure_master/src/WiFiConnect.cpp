#include "WiFiConnect.hpp"

WiFiConnect::WiFiConnect(const char ssid[], const char pass[]): SSID(ssid), PASS(pass) {}

void WiFiConnect::init()
{
    WiFi.mode(WIFI_AP_STA);

    WiFi.begin(SSID, PASS);
    while(WiFi.status() != WL_CONNECTED)
    {
        for(int attempt = 0; attempt < 4; attempt++)
        {
            if(attempt = 0)
            {
                Serial.print("Connecting to ");
                Serial.println(SSID);
                delay(5000);
            }
            else if(attempt = 1)
            {
                Serial.println("Connection failed, attempting reconnection...");
                delay(5000);
            }
            else if(attempt = 2)
            {
                Serial.println("Connection failed, attempting reconnection...");
                delay(5000);
            }
            else if(attempt = 3)
            {
                Serial.println("Connection failed, verify and make sure the right information is entered.");
            }
        }
    }
    Serial.print("Connected to station : ");
    Serial.println(WiFi.localIP());
    Serial.print("In channcel : ");
    Serial.println(WiFi.channel());
}