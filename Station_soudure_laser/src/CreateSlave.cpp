#include "CreateSlave.hpp"

CreateSlave::CreateSlave(int pinLaser1, int baud) : PIN_LASER1(pinLaser1), SERIAL_BAUD(baud) {}

void CreateSlave::begin()
{
    initSerial(SERIAL_BAUD);
    
    pinMode(PIN_LASER1, INPUT);
}

bool CreateSlave::readLaserEntry()
{
    EntryLaserData = digitalRead(PIN_LASER1);
    return EntryLaserData;
}

void CreateSlave::initSerial(int baud)
{
    Serial.begin(baud);
    while(!Serial) {}
    Serial.println("Serial monitor ready for debug");
}