#include "MqttCommunication.hpp"

MqttCommunication* MqttCommunication::instance = nullptr;

MqttCommunication::MqttCommunication(const char broker[], int port, MqttClient& client) : BROKER(broker), PORT(port), mqttClient(client) {}

bool MqttCommunication::begin()
{
    if(!mqttClient.connect(BROKER, PORT))
    {
        Serial.print("[MQTT] Connection failed! Error code = ");
        Serial.println(mqttClient.connectError());
        
        return false;
    }

    onMessage();
    subscribeToTopics();

    Serial.println("[MQTT] Connected successfully!");

    return true;
}

void MqttCommunication::subscribeToTopics()
{
    mqttClient.subscribe("light/control/#");
}

void MqttCommunication::onMessage()
{
    instance = this;
    mqttClient.onMessage(onMqttMessageCallback);
}

void MqttCommunication::onMqttMessageCallback(int messageSize)
{
    if(instance != nullptr)
    {
        instance->onMqttMessage(messageSize);
    }
}

void MqttCommunication::onMqttMessage(int messageSize)
{
    //to be modified later on

    // Retrieve topic BEFORE reading payload
    String receivedTopic = mqttClient.messageTopic();
    String payload = "";

    for(int i = 0; i < messageSize; i++)
    {
        if(mqttClient.available())
        {
            payload += (char)mqttClient.read();
        }
    }

    Serial.println("[MQTT] Message received");

    Serial.print("\n[MQTT] Topic: ");
    Serial.println(receivedTopic);

    Serial.print("[MQTT] Payload: ");
    Serial.println(payload);
}

void MqttCommunication::poll()
{
    mqttClient.poll();
}

void MqttCommunication::publish(String json, const char topic[])
{
    mqttClient.beginMessage(topic);
    mqttClient.print(json);
    mqttClient.endMessage();
}