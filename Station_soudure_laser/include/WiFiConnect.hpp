#ifndef DEF_WIFICONNECT
#define DEF_WIFICONNECT

#include "CreateSlave.hpp"
#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>

class WiFiConnect
{
    public:

        /**
         * @brief Constructeur de l'objet pour la communication
         * 
         * @param char ssid : SSID du reseau
         */
        WiFiConnect(const char ssid[]);


        /**
         * @brief Fonction pour ce connecter au channel du reseau
         * 
         * @returns Channel (int32_t)
         */
        int32_t init();
        
    private:
        
        const char* SSID;
        int32_t CHANNEL;
        
        /**
         * @brief Fonction pour recuperer le channel du reseau
         * 
         * @param char ssid : SSID du reseau
         * @returns Numereau du reseau (int32_t)
         */
        int32_t getWiFiChannel(const char* ssid);
    };

#endif