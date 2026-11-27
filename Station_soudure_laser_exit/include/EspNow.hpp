#ifndef DEF_ESPNOW
#define DEF_ESPNOW

#include "WiFiConnect.hpp"

class EspNow
{
    public:

        /**
         * @brief Constructeur de la classe permettant la communication esp-now
         */
        EspNow() { instance = this; }


        /**
         * @brief Fonction initialisation de communication esp-now
         */
        void init();

        /**
         * @brief Fonction pour enregistrer les peers (autre esp32)
         * 
         * @param uint8_t mac[] : Adresse mac du esp32 MASTER
         */
        void peer(const uint8_t mac[6]);

        /**
         * @brief Fonction pour recevoire des message venue d'autre esp32
         */
        void receiveCallBack();


        /**
         * @brief Fonction pour envoyer des message avec esp-now
         * 
         * @param uint8_t mac[]                 : Adresse mac du esp32 MASTER
         * @param struct_message dataPayload    : Payload contenant les valeur a envoyer
         * 
         * @returns resultat de l'envoie
         */
        esp_err_t espSendMessage(const uint8_t mac[6], struct_message dataPayload);

        /**
         * @brief Fonction pour verifier l'envoie du message
         */
        void verifySending();
        
    private:
        
        esp_now_peer_info_t peerInfo;
        static EspNow* instance;
        esp_err_t result;
    
        /**
         * @brief Fonction du callback
         * 
         * @param wifi_tx_info_t tx_info
         * @param esp_now_send_status_t status
         * 
         */
        static void OnDataSent(const wifi_tx_info_t* tx_info, esp_now_send_status_t status);

        /**
         * @brief Message de confirmation de l'envoie
         * 
         * @param esp_now_send_status_t status
         */
        void handleSendStatus(esp_now_send_status_t status);
};

#endif