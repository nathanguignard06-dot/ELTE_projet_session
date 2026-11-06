#include "CreateSlave.hpp"

CreateSlave::CreateSlave(int pinLaser1) : PIN_LASER1(pinLaser1) {}

void CreateSlave::begin()
{
    pinMode(PIN_LASER1, INPUT);
}

bool CreateSlave::readLaserEntry()
{
    EntryLaserData = digitalRead(PIN_LASER1);
    return EntryLaserData;
}