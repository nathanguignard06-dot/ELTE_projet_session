#include "WiFiConnect.hpp"

WiFiConnect::WiFiConnect(char ssid[], char pass[]): SSID(ssid), PASS(pass) {}

void WiFiConnect::init()
{
    Serial.print("Connexion au WiFi ");
    Serial.println(SSID);

    while (WiFi.begin(SSID, PASS) != WL_CONNECTED) 
    {
        delay(2000);
    }

    Serial.println("WiFi connecte !");
    Serial.print("adresse IP : ");
    Serial.println(WiFi.localIP());
}