#include "EspNow.hpp"
#include "secrets.h"

// definition des pin de capteur laser
const int ENTRY_LASER_PIN = 39;

// creation des objet
CreateSlave laserSlave(ENTRY_LASER_PIN);
WiFiConnect wifi(ssid);
EspNow espNow;
struct_message dataPayload;

int laser1Reading = 0;
int passing = 0;
unsigned long previousMillis = 0;
int interval = 5000;

void setup() 
{
    Serial.begin(115200);           // initialisation comm serial (debug)
    while(!Serial) {}               // attendre que moniteur serial ouvre

    wifi.init();                    // initialisation wifi

    espNow.init();                  // initialisation esp-now

    laserSlave.begin();             // initialisation du slave

    espNow.receiveCallBack();       // recevoir les donnees du callback (du master)

    espNow.peer(broadcastAddress);  // enregistrer et ajouter peer (le master)

    Serial.println("Slave Ready");  // debug
}

void loop() 
{
    //laser1Reading = laserSlave.readLaserEntry();

    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis >= interval && laser1Reading > 0)
    {
        previousMillis = currentMillis;
        laser1Reading = 0;

        if(laser1Reading < 1)
        {
            if(passing < 1)
            {
                passing = 1;
                
                dataPayload.entryLaserData = laser1Reading;
    
                espNow.espSendMessage(broadcastAddress, dataPayload);
                espNow.verifySending();
    
                Serial.println(dataPayload.entryLaserData);
            }
        }
        else if(laser1Reading > 0)
        {
            if(passing > 0)
            {
                passing = 0;
    
                dataPayload.entryLaserData = laser1Reading;
    
                espNow.espSendMessage(broadcastAddress, dataPayload);
                espNow.verifySending();
    
                Serial.println(dataPayload.entryLaserData);
            }
        }
    }
    else if(currentMillis - previousMillis >= interval && laser1Reading < 1)
    {
        previousMillis = currentMillis;
        laser1Reading = 1;

        if(laser1Reading < 1)
        {
            if(passing < 1)
            {
                passing = 1;
                
                dataPayload.entryLaserData = laser1Reading;
    
                espNow.espSendMessage(broadcastAddress, dataPayload);
                espNow.verifySending();
    
                Serial.println(dataPayload.entryLaserData);
            }
        }
        else if(laser1Reading > 0)
        {
            if(passing > 0)
            {
                passing = 0;
    
                dataPayload.entryLaserData = laser1Reading;
    
                espNow.espSendMessage(broadcastAddress, dataPayload);
                espNow.verifySending();
    
                Serial.println(dataPayload.entryLaserData);
            }
        }
    }
}