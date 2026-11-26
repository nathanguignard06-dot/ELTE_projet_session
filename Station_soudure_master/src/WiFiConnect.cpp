#include "WiFiConnect.hpp"

WiFiConnect::WiFiConnect(const char ssidAP[], Oled& screen) : SSID_AP(ssidAP), oled(screen), server(80) {}

bool WiFiConnect::begin()
{
    preferences.begin("wifi-config", false);

    String ssid = preferences.getString("ssid", "");
    String pass = preferences.getString("password", "");

    if(ssid.length() > 0)
    {
        oled.clearScreen();
        oled.screenSettings(1, 0, 10);
        Serial.println("[WIFI] Saved credentials found");
        oled.print("[WIFI] Saved credentials found");

        WiFi.mode(WIFI_AP_STA);

        if(wifiConnectToRouter(ssid.c_str(), pass.c_str()))
        {
            oled.screenSettings(1, 0, 13);
            Serial.println("[WIFI] Successfully reconnected!");
            oled.print("[WIFI] Successfully reconnected!");
            return true;
        }

        oled.clearScreen();
        oled.screenSettings(1, 0, 11);
        Serial.println("[WIFI] Unable to reconnect!");
        oled.print("[WIFI] Unable to reconnect!");
    }

    oled.screenSettings(1, 0, 12);
    Serial.println("[WIFI] Starting configuration portal...");
    oled.print("[WIFI] Starting configuration portal...");

    wifiAPmode();
    getAPIP();

    return false;
}

void WiFiConnect::wifiAPmode()
{
    WiFi.mode(WIFI_AP);

    WiFi.softAP(SSID_AP);

    server.on("/", HTTP_GET, [this]() {handleRoot();});

    server.on("/connect", HTTP_POST, [this]() {handleCredentials();});

    server.begin();

    oled.screenSettings(1, 0, 13);
    Serial.println("[WIFI AP] Web server started");
    oled.print("[WIFI AP] Web server started");
}

void WiFiConnect::getAPIP()
{
    oled.screenSettings(1, 0, 14);
    IP = WiFi.softAPIP();
    Serial.print("[WIFI AP] AP IP address : ");
    oled.print("[WIFI AP] AP IP address : ");
    oled.screenSettings(1, 0, 16);
    Serial.println(IP);
    oled.print(IP.toString());
    oled.screenSettings(1, 0, 17);
    Serial.println("[WIFI AP] Connect to the hotspot and open this IP in your browser.");
    oled.print("[WIFI AP] Connect to the hotspot and open this IP in your browser.");
}

void WiFiConnect::handleClient()
{
    server.handleClient();
}

void WiFiConnect::handleRoot()
{
    String html = R"rawliteral(
    <!DOCTYPE html>
    <html>

    <head>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <title>ESP32 WiFi Configuration</title>
    </head>

    <body>

        <h1>ESP32 Configuration</h1>

        <p>Enter your WiFi network credentials below.</p>

        <form action="/connect" method="POST">

            <label>WiFi SSID:</label><br>
            <input type="text" name="ssid" required>

            <br><br>

            <label>WiFi Password:</label><br>
            <input type="password" name="password">

            <br><br>

            <button type="submit">Connect</button>

        </form>

    </body>
    </html>
    )rawliteral";

    server.send(200, "text/html", html);
}

void WiFiConnect::handleCredentials()
{
    String ssid = server.arg("ssid");
    String pass = server.arg("password");

    if(ssid.length() == 0)
    {
        server.send(400, "text/html",
            "<h1>Error</h1><p>SSID cannot be empty.</p>");
        return;
    }

    oled.clearScreen();
    oled.screenSettings(1, 0, 10);
    Serial.println("\n[WIFI] New credentials received");
    oled.print("\n[WIFI] New credentials received");
    WiFi.mode(WIFI_AP_STA);

    if(wifiConnectToRouter(ssid.c_str(), pass.c_str()))
    {
        oled.clearScreen();
        preferences.putString("ssid", ssid);
        preferences.putString("password", pass);

        server.send(200, "text/html",
            "<h1>Connected successfully!</h1>"
            "<p>Your WiFi credentials have been saved.</p>"
            "<p>You can now close this page.</p>");

        oled.screenSettings(1, 0, 10);
        Serial.println("[WIFI] Credentials saved");
        oled.print("[WIFI] Credentials saved");
        delay(500);

        server.stop();

        WiFi.softAPdisconnect(true);
        WiFi.mode(WIFI_STA);

        oled.screenSettings(1, 0, 12);
        Serial.println("[WIFI] Configuration complete");
        oled.print("[WIFI] Configuration complete");
    }
    else
    {
        oled.clearScreen();

        WiFi.mode(WIFI_AP);

        server.send(200, "text/html",
            "<h1>Connection failed!</h1>"
            "<p>Please verify your SSID and password.</p>"
            "<a href='/'>Try again</a>");

        oled.screenSettings(1, 0, 10);
        Serial.println("[WIFI] Returning to configuration portal");
        oled.print("[WIFI] Returning to configuration portal");
    }
}

bool WiFiConnect::wifiConnectToRouter(const char ssid[], const char pass[])
{
    oled.clearScreen();
    oled.screenSettings(1, 0, 10);
    Serial.print("\n[WIFI] Connecting to ");
    Serial.print(ssid);
    oled.print("[WIFI] Connecting to ");
    oled.screenSettings(1, 23, 10);
    oled.print(ssid);

    int timeout = 0;

    WiFi.begin(ssid, pass);
    while(WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
        for(int i = 0; i < 3; i++)
        {
            oled.screenSettings(1, i, 11);
            oled.print(".");
        }

        oled.clearScreen();
        oled.screenSettings(1, 0, 10);
        oled.print("[WIFI] Connecting to ");
        oled.screenSettings(1, 23, 10);
        oled.print(ssid);

        timeout++;
        if(timeout > 30)
        {
            oled.screenSettings(1, 0, 11);
            Serial.println("\n[ERROR] WiFi connection timeout");
            oled.print("[ERROR] WiFi connection timeout");
            WiFi.disconnect(false, false);
            return false;
        }
    }

    oled.clearScreen();
    oled.screenSettings(1, 0, 10);
    Serial.println("\n[WIFI] Connected successfully");
    Serial.print("[WIFI] IP address : ");
    Serial.println(WiFi.localIP());
    oled.print("[WIFI] Connected successfully");
    oled.screenSettings(1, 0, 11);
    oled.print("[WIFI] IP address : ");
    oled.screenSettings(1, 22, 11);
    oled.print(WiFi.localIP().toString());

    return true;
}

bool WiFiConnect::isConnected()
{
    return WiFi.status() == WL_CONNECTED;
}

void WiFiConnect::getMac()
{
    mac = WiFi.macAddress();
    Serial.print("MAC address : ");
    Serial.println(mac);
}