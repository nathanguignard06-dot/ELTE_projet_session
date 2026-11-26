#include "include_all.h"

/*--- OBJECT INITIALISING ---*/
struct_message dataPayload;

CreateMaster master;
Logique systemeLogique(dataPayload);

WiFiConnect wifi("Station_Soudure_Setup");
EspNow espNow(dataPayload);

WiFiClient networkClient;
MqttClient client(networkClient);
MqttCommunication mqtt(broker, port, client);


/*--- GLOBAL VARIABLES ---*/
bool applicationStarted      = false;   //to start app

int baudRate                 = 115200;  //serial baud rate

int peopleCount              = 0;

unsigned long previousMillis = 0;
int interval                 = 5000;

//application initializer
void startApplication()
{
  Serial.println("[SYSTEM] Starting application...");

  espNow.init();
  mqtt.begin();
  wifi.getMac();

  applicationStarted = true;

  Serial.println("[SYSTEM] Application started!");
}

void setup()
{
  master.setupSerial(baudRate);

  if(wifi.begin())
  {
    Serial.println("[SYSTEM] WiFi ready");
    startApplication();
  }
}

void loop()
{
  if(!applicationStarted)
  {
    wifi.handleClient();

    //check if the user successfully configured WiFi
    if(wifi.isConnected())
    {
      Serial.println("[SYSTEM] WiFi configured");
      startApplication();
    }
  }
  if(applicationStarted)
  {
    mqtt.poll();

    peopleCount = systemeLogique.peopleCounter();

    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis >= interval)
    {
      previousMillis = currentMillis;

      JsonDocument doc;

      doc["entryVal"]    = dataPayload.entryLaserData;
      doc["exitVal"]     = dataPayload.exitLaserData;
      doc["peopleCount"] = peopleCount;

      String json;
      serializeJson(doc, json);

      Serial.println("\n[PAYLOAD]");
      Serial.println(json);

      mqtt.publish(json, MqttTopics::laserData);
    }
  }
}