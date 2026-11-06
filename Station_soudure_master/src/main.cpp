#include "EspNow.hpp"

constexpr char ssid[] = "UNIFI_IDO2";
constexpr char pass[] = "#26ccNB!#";

struct_message dataPayload;
CreateMaster master();
Logique systemeLogique(dataPayload);
WiFiConnect wifi(ssid, pass);
EspNow espNow(dataPayload);

void OnDataRecv(const uint8_t* mac_addr, const uint8_t *incomingData, int len)
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
}

void setup()
{
  Serial.begin(115200);
  while(!Serial) {}

  wifi.init();
  wifi.getMac();
  espNow.init();

  esp_now_register_recv_cb(OnDataRecv);
}

void loop()
{
  
}