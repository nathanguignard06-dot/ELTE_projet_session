#include "EspNow.hpp"

EspNow::EspNow(uint8_t broadcastAddress, esp_now_peer_info_t peer): BROADCAST_ADDRESS(broadcastAddress), peerInfo(peer) {}

void EspNow::init()
{
    if (esp_now_init() != ESP_OK) 
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
}

void EspNow::peer(esp_now_peer_info_t peer, uint8_t broadcastAddress)
{
    memcpy(peerInfo.peer_addr, BROADCAST_ADDRESS, 6);
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
    Serial.print("\r\nLast Packet Send Status:\t");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void EspNow::receiveCallBack()
{
    esp_now_register_send_cb(OnDataSent);
}