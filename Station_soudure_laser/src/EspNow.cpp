#include "EspNow.hpp"

EspNow* EspNow::instance = nullptr;

void EspNow::init()
{
    if (esp_now_init() != ESP_OK) 
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
}

void EspNow::peer(const uint8_t mac[6])
{
    memset(&peerInfo, 0, sizeof(peerInfo));
    memcpy(peerInfo.peer_addr, mac, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if(esp_now_add_peer(&peerInfo) != ESP_OK)
    {
        Serial.println("Failed to add peer");
        return;
    }
}

void EspNow::OnDataSent(const uint8_t* mac_addr, esp_now_send_status_t status)
{
    if (instance != nullptr)
    {
        instance->handleSendStatus(mac_addr, status);
    }
}

void EspNow::handleSendStatus(const uint8_t* mac_addr, esp_now_send_status_t status)
{
    Serial.print("\r\nLast Packet Send Status:\t");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void EspNow::receiveCallBack()
{
    esp_now_register_send_cb(OnDataSent);
}