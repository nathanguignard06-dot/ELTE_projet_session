#ifndef MQTTCOMMUNICATION
#define MQTTCOMMUNICATION

#include "WiFiConnect.hpp"
#include <ArduinoMqttClient.h>
#include "MqttTopics.h"

class MqttCommunication
{
    public:

        MqttCommunication(const char broker[], int port, MqttClient& client);

        bool begin();
        void poll();
        void publish(String json, const char topic[]);

    private:

        const char* BROKER;
        const int PORT;

        MqttClient& mqttClient;

        static MqttCommunication* instance;
        static void onMqttMessageCallback(int messageSize);
        void onMqttMessage(int messageSize);
        void onMessage();
        void subscribeToTopics();
};

#endif