#ifndef DEF_CREATESLAVE
#define DEF_CREATESLAVE

#include <Arduino.h>

class CreateSlave
{
    public:

        CreateSlave(int pinLaser1);

        void begin();
        bool readLaserEntry();

    private:

        const int PIN_LASER1;

        bool EntryLaserData;
};

#endif