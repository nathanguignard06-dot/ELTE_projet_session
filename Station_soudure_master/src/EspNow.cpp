#include "EspNow.hpp"

EspNow* EspNow::instance = nullptr;

EspNow::EspNow(struct_message payload) : dataPayload(payload) 
{
    instance = this;
}

bool EspNow::init()
{
    Serial.println("\n[ESP_NOW] Initializing ESP-NOW...");

    if(esp_now_init() != ESP_OK)
    {
        Serial.println("[ESP_NOW] Error initializing ESP-NOW");
        return false;
    }

    Serial.println("[ESP_NOW] ESP_NOW successfully initialized");
    Serial.println("[ESP_NOW] Now listening for incoming payloads");
    registerRecvData();
    return true;
}

void EspNow::registerRecvData()
{
    esp_now_register_recv_cb(OnDataRecv);
}

void EspNow::OnDataRecv(const esp_now_recv_info_t* recv_info, const uint8_t *incomingData, int len)
{
    if(instance != nullptr)
    {
        instance->handleRecvData(recv_info->src_addr, incomingData, len);
    }
}

void EspNow::handleRecvData(const uint8_t* mac_addr, const uint8_t *incomingData, int len)
{
    if(len != sizeof(dataPayload))
    {
        Serial.println("[ESP_NOW] Received payload with incorrect size");
        return;
    }

    memcpy(&dataPayload, incomingData, sizeof(dataPayload));

    Serial.println("\n[PAYLOAD] Start of payload");
    Serial.println("-----------------");

    Serial.print("Bytes received: ");
    Serial.println(len);

    Serial.println("-----------------");

    Serial.print("Entry laser value: ");
    Serial.println(dataPayload.entryLaserData);

    Serial.println("-----------------");

    Serial.print("Exit laser value: ");
    Serial.println(dataPayload.exitLaserData);

    Serial.println("-----------------\n");
    Serial.println("[PAYLOAD] End of payload");
}