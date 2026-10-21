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
        
    private:
        
        esp_now_peer_info_t peerInfo;
        static EspNow* instance;
    
        static void OnDataSent(const uint8_t* mac_addr, esp_now_send_status_t status);
        void handleSendStatus(const uint8_t* mac_addr, esp_now_send_status_t status);
};

#endif