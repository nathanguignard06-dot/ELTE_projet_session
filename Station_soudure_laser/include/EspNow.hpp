#ifndef DEF_ESPNOW
#define DEF_ESPNOW

#include "WiFiConnect.hpp"

class EspNow
{
    public:

        EspNow() { instance = this; }

        void init();
        void peer(const uint8_t mac[6]);
        void receiveCallBack();

        esp_err_t espSendMessage(const uint8_t mac[6], struct_message dataPayload);
        void verifySending();
        
    private:
        
        esp_now_peer_info_t peerInfo;
        static EspNow* instance;
        esp_err_t result;
    
        static void OnDataSent(const wifi_tx_info_t* tx_info, esp_now_send_status_t status);
        void handleSendStatus(esp_now_send_status_t status);
};

#endif