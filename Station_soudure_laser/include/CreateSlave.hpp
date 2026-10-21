#ifndef DEF_CREATESLAVE
#define DEF_CREATESLAVE

#include <Arduino.h>

class CreateSlave
{
    public:

        CreateSlave(int pinLaser1, int pinLazer2);

        void begin();
        bool readLaserEntry();
        bool readLaserExit();

    private:

        const int PIN_LASER1;
        const int PIN_LASER2;

        bool EntryLaserData;
        bool ExitLaserData;
};

#endif