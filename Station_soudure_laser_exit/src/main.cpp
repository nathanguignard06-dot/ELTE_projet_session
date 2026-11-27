#include "EspNow.hpp"
#include "secrets.h"

/*--- DEFINITIONS ---*/
#define EXIT_LASER_PIN 39
#define SERIAL_BAUD     115200

/*--- DECLARATIONS ---*/
CreateSlave laserSlave(EXIT_LASER_PIN, SERIAL_BAUD);
WiFiConnect wifi(ssid);
EspNow espNow;
struct_message dataPayload;

/*--- GLOBAL VARIABLES ---*/
int laser2Reading = 0;
int passing = 0;

void setup() 
{
    laserSlave.begin();             // initialisation de l'objet et moniteur Serial

    wifi.init();                    // initialisation wifi

    espNow.init();                  // initialisation esp-now

    espNow.receiveCallBack();       // recevoir les donnees du callback (du master)

    espNow.peer(broadcastAddress);  // enregistrer et ajouter peer (le master)

    Serial.println("Slave Ready");  // debug
}

void loop() 
{
    laser2Reading = laserSlave.readLaserEntry();    // lecture du capteur laser

    if(laser2Reading < 1)   // pour envoyer une fois a chaque changement
    {
        if(passing < 1)
        {
            passing = 1;
                
            dataPayload.exitLaserData = laser2Reading; // stocker la valeur dans le payload
    
            espNow.espSendMessage(broadcastAddress, dataPayload);   //envoie du payload au master
            espNow.verifySending();
    
            Serial.println(dataPayload.exitLaserData); // debug
        }
    }
    else if(laser2Reading > 0)
    {
        if(passing > 0)
        {
            passing = 0;
    
            dataPayload.exitLaserData = laser2Reading; // stocker la valeur dans le payload
    
            espNow.espSendMessage(broadcastAddress, dataPayload);   // envoie du payload
            espNow.verifySending();
    
            Serial.println(dataPayload.exitLaserData); // debug
        }
    }
}