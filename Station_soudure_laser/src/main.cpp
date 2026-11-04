#include "EspNow.hpp"

// definition de l'addresse mac du esp master
uint8_t broadcastAddress[] = {/*mac address esp master*/};

// definition ssid wifi
constexpr char ssid[] = "UNIFI_IDO2";

// definition des pin de capteur laser
const int ENTRY_LASER_PIN = 35;

// creation des objet
CreateSlave laserSlave(ENTRY_LASER_PIN);
WiFiConnect wifi(ssid);
EspNow espNow;

int laser1Reading = 0;
int passing = 0;

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
    laser1Reading = laserSlave.readLaserEntry();

    if(laser1Reading < 1)
    {
        if(passing < 1)
        {
            passing = 1;

            //espNow.espSendMessage(broadcastAddress, laser1Reading);
            //espNow.verifySending();

            Serial.println(laser1Reading);
        }
    }
    else if(laser1Reading > 0)
    {
        if(passing > 0)
        {
            passing = 0;

            //espNow.espSendMessage(broadcastAddress, laser1Reading);
            //espNow.verifySending();

            Serial.println(laser1Reading);
        }
    }

}