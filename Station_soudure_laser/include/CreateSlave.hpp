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
         */
        CreateSlave(int pinLaser1);


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

        bool EntryLaserData;
};

#endif