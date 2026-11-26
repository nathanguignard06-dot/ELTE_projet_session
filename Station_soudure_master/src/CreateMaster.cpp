#include "CreateMaster.hpp"

CreateMaster::CreateMaster(Oled& screen, int baud) : oled(screen), SERIAL_BAUD_R8(baud) {}

void CreateMaster::begin()
{
    setupSerial(SERIAL_BAUD_R8);
    if(!oled.begin())
    {
        Serial.println("[OLED] Restarting allocation");
        oled.begin();
    }
    
    oled.startScreen();
}

void CreateMaster::setupSerial(int baud)
{
    Serial.begin(baud);
    while(!Serial) {}

    Serial.println("[SERIAL] Serial monitor for debug ready\n");
}