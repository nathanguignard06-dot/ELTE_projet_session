#ifndef ESPNOW
#define ESPNOW

#include "WiFiConnect.hpp"
#include <esp_now.h>
#include <esp_wifi.h>

class EspNow
{
    public:

        EspNow(struct_message payload);

        bool init();
        
        private:
        
        struct_message& dataPayload;
        static EspNow* instance;
        
        void registerRecvData();
        static void OnDataRecv(const esp_now_recv_info_t* recv_info, const uint8_t *incomingData, int len);
        void handleRecvData(const uint8_t* mac_addr, const uint8_t *incomingData, int len);

};
#endif