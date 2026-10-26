#include "EspNow.hpp"

// definition de l'addresse mac du esp master
uint8_t broadcastAddress[] = {/*mac address esp master*/};

// definition ssid wifi
constexpr char ssid[] = "UNIFI_IDO2";

// definition des pin de capteur laser
const int ENTRY_LASER_PIN = 35;
const int EXIT_LASER_PIN  = 34;

// creation des objet
CreateSlave laserSlave(ENTRY_LASER_PIN, EXIT_LASER_PIN);
Logique     peopleCounter(laserSlave);
WiFiConnect wifi(ssid);
EspNow espNow;

int peopleCount = 0;
const int interval = 1000;
unsigned long int previousMillis = 0;

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
    int state = peopleCounter.peopleCounter();            // lecture des capteur de laser et traitement (verifier si personne entre ou sort)
    if(state > 0 || state < 0)
    {
        peopleCount += state;
        delay(1500);
    }
    //espNow.espSendMessage(broadcastAddress, peopleCount);   // envoie du message au master
    //espNow.verifySending();                                 // verifier si l'envoie est correct

    unsigned long int currentMillis = millis();
    if(currentMillis - previousMillis >= interval)
    {
        previousMillis = currentMillis;
        
        Serial.print("persone dans la piece : ");
        Serial.println(peopleCount);
    }
}