#include "include_all.h"

/*--- DEFINITIONS ---*/
#define SERIAL_BAUD_R8 115200
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

/*--- OBJECT INITIALISING ---*/
struct_message dataPayload;

Adafruit_SSD1306 screen(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Oled oled(screen);

CreateMaster master(oled, SERIAL_BAUD_R8);
Logique systemeLogique(dataPayload);

WiFiConnect wifi("Station_Soudure_Setup", oled);
EspNow espNow(dataPayload);

WiFiClient networkClient;
MqttClient client(networkClient);
MqttCommunication mqtt(broker, port, client);


/*--- GLOBAL VARIABLES ---*/
bool applicationStarted      = false;   //to start app

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
  master.begin();

  delay(1000);

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
      oled.clearScreen();
      oled.screenSettings(1, 0, 6);
      Serial.println("[SYSTEM] WiFi configured!");
      oled.print("WiFi configured!");
      oled.screenSettings(1, 0, 16);
      oled.print("Starting application");
      oled.displayScreen();
      delay(1000);

      startApplication();
    }
  }
  if(applicationStarted)
  {
    oled.clearScreen();
    oled.displayScreen();

    mqtt.poll();

    peopleCount = systemeLogique.peopleCounter();
    int entryLaser = dataPayload.entryLaserData;
    int exitLaser = dataPayload.exitLaserData;

    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis >= interval)
    {
      previousMillis = currentMillis;

      JsonDocument doc;

      doc["entryVal"]    = entryLaser;
      doc["exitVal"]     = exitLaser;
      doc["peopleCount"] = peopleCount;

      String json;
      serializeJson(doc, json);

      Serial.println("\n[PAYLOAD]");
      Serial.println(json);

      mqtt.publish(json, MqttTopics::laserData);
    }
  }
}