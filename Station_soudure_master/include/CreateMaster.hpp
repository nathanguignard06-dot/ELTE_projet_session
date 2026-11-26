#ifndef DEF_CREATEMASTER
#define DEF_CREATEMASTER

#include <Arduino.h>
#include "msgPayload.hpp"
#include "Oled.hpp"

class CreateMaster
{
    public:

        CreateMaster(Oled& screen, int baud);

        void begin();
        
    private:
        
        const int SERIAL_BAUD_R8;
        Oled& oled;

        void setupSerial(int baud);
};

#endif