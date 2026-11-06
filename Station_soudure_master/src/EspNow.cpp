#include "EspNow.hpp"

EspNow::EspNow(struct_message payload) : dataPayload(payload) {}

void EspNow::init()
{
    if (esp_now_init() != ESP_OK) 
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
}

/*void EspNow::OnDataRecv(const uint8_t* mac_addr, const uint8_t *incomingData, int len)
{
    memcpy(&dataPayload, incomingData, sizeof(dataPayload));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.println("-----------------");
  Serial.print("entry laser value : ");
  Serial.println(dataPayload.entryLaserData);
  Serial.println("-----------------");
  Serial.print("exit laser value : ");
  Serial.println(dataPayload.exitLaserData);
  Serial.println("-----------------");
}*/

/*void EspNow::registerRecvData()
{
    esp_now_register_recv_cb(OnDataRecv);
}*/