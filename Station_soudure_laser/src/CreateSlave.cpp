#include "CreateSlave.hpp"

CreateSlave::CreateSlave(int pinLaser1, int pinLaser2) : PIN_LASER1(pinLaser1), PIN_LASER2(pinLaser2) {}

void CreateSlave::begin()
{
    pinMode(PIN_LASER2, INPUT);
    pinMode(PIN_LASER1, INPUT);
}

bool CreateSlave::readLaserEntry()
{
    EntryLaserData = digitalRead(PIN_LASER1);
    return EntryLaserData;
}

bool CreateSlave::readLaserExit()
{
    ExitLaserData  = digitalRead(PIN_LASER2);
    return ExitLaserData;
}