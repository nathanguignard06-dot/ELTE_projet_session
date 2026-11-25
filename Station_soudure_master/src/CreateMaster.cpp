#include "CreateMaster.hpp"

CreateMaster::CreateMaster() {}

void CreateMaster::begin() {}       //empty for now because no current pins used

void CreateMaster::setupSerial(int baud)
{
    Serial.begin(baud);
    while(!Serial) {}
    Serial.println("\n[SERIAL] Serial communication for debug active.\n");
}