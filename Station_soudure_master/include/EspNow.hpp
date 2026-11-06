#ifndef DEF_ESPNOW
#define DEF_ESPNOW

#include "WiFiConnect.hpp"

class EspNow
{
    public:

        EspNow(struct_message payload);

        void init();
        /*void registerRecvData();*/
        
    private:
    
        void OnDataRecv(const uint8_t* mac_addr, const uint8_t *incomingData, int len);

        struct_message& dataPayload;
};

#endif