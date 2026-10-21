#ifndef DEF_ESPNOW
#define DEF_ESPNOW

#include "WiFiConnect.hpp"

class EspNow
{
    public:

        EspNow(uint8_t broadcastAddress, esp_now_peer_info_t peer);

        void init();
        void peer(esp_now_peer_info_t peer, uint8_t broadcastAddress);
        void receiveCallBack();
        
    private:
        
        const uint8_t BROADCAST_ADDRESS;
        esp_now_peer_info_t peerInfo;
    
        void OnDataSent(const uint8_t* mac_addr, esp_now_send_status_t status);
};      

#endif