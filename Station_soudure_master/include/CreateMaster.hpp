#ifndef DEF_CREATEMASTER
#define DEF_CREATEMASTER

#include <Arduino.h>
#include "msgPayload.hpp"

class CreateMaster
{
    public:

        CreateMaster();

        void begin();
        void setupSerial(int baud);

    private:

};

#endif