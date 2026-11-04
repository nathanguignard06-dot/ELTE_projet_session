#ifndef DEF_ESPNOW
#define DEF_ESPNOW

#include "WiFiConnect.hpp"

class EspNow
{
    public:

        EspNow();

        void init();
        void registerRecvData();
        
    private:
    
        static void OnDataRecv(const uint8_t* mac_addr, const uint8_t *incomingData, int len);
};

#endif