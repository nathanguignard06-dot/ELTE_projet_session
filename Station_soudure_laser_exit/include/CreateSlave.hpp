#ifndef DEF_CREATESLAVE
#define DEF_CREATESLAVE

#include <Arduino.h>
#include "msgPayload.hpp"

class CreateSlave
{
    public:

        /**
         * @brief Constructeur de l'objet pour le laser d'entrer
         * 
         * @param int pinLaser : Broche du capteur laser
         * @param int baud     : Baud rate du moniteur Serial
         */
        CreateSlave(int pinLaser1, int baud);


        /**
         * @brief Fonction d'initialisation des broches
         */
        void begin();

        /**
         * @brief Fonction pour la lecture de la valeur brute du laser
         * 
         * @returns 1/0 (bool)
         */
        bool readLaserEntry();

    private:

        const int PIN_LASER1;
        const int SERIAL_BAUD;
        bool EntryLaserData;

        /**
         * @brief Fonction pour commencer moniteur Serial
         * 
         * @param int baud : Baud rate du moniteur Serial
         */
        void initSerial(int baud);
};

#endif