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
        oled.screenSettings(1, 0, 6);
        Serial.println("[WIFI] Saved credentials found");
        oled.print("Saved credentials found");
        oled.displayScreen();
        delay(1000);

        WiFi.mode(WIFI_AP_STA);

        if(wifiConnectToRouter(ssid.c_str(), pass.c_str()))
        {
            oled.screenSettings(1, 0, 16);
            Serial.println("[WIFI] Successfully reconnected!");
            oled.print("Successfully reconnected!");
            oled.displayScreen();
            delay(1000);

            return true;
        }

        oled.clearScreen();
        oled.screenSettings(1, 0, 16);
        Serial.println("[WIFI] Unable to reconnect!");
        oled.print("Unable to reconnect!");
        oled.displayScreen();
    }

    oled.screenSettings(1, 0, 16);
    Serial.println("[WIFI] Starting configuration portal...");
    oled.print("Starting configuration portal...");
    oled.displayScreen();
    delay(1000);

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

    oled.clearScreen();
    oled.screenSettings(1, 0, 16);
    Serial.println("[WIFI AP] Web server started");
    oled.print("Web server started");
    oled.displayScreen();
    delay(1000);
}

void WiFiConnect::getAPIP()
{
    oled.clearScreen();
    oled.screenSettings(1, 0, 6);
    IP = WiFi.softAPIP();
    Serial.print("[WIFI AP] AP IP address : ");
    oled.print("IP address: ");
    oled.screenSettings(1, 0, 18);
    Serial.println(IP);
    oled.print(IP.toString());
    oled.screenSettings(1, 0, 32);
    Serial.println("[WIFI AP] Connect to the hotspot and open this IP in your browser.");
    oled.print("Connect to hotspot and open IP in browser.");
    oled.displayScreen();
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
    oled.screenSettings(1, 0, 16);
    Serial.println("\n[WIFI] New credentials received");
    oled.print("New credentials received");
    oled.displayScreen();
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

        oled.screenSettings(1, 0, 16);
        Serial.println("[WIFI] Credentials saved");
        oled.print("Credentials saved");
        delay(500);

        server.stop();

        WiFi.softAPdisconnect(true);
        WiFi.mode(WIFI_STA);

        oled.screenSettings(1, 0, 32);
        Serial.println("[WIFI] Configuration complete");
        oled.print("Configuration complete");
        oled.displayScreen();
    }
    else
    {
        oled.clearScreen();

        WiFi.mode(WIFI_AP);

        server.send(200, "text/html",
            "<h1>Connection failed!</h1>"
            "<p>Please verify your SSID and password.</p>"
            "<a href='/'>Try again</a>");

        oled.screenSettings(1, 0, 16);
        Serial.println("[WIFI] Returning to configuration portal");
        oled.print("Returning to configuration portal");
        oled.displayScreen();
    }
}

bool WiFiConnect::wifiConnectToRouter(const char ssid[], const char pass[])
{
    oled.clearScreen();
    oled.screenSettings(1, 0, 6);
    Serial.print("\n[WIFI] Connecting to ");
    Serial.print(ssid);
    oled.print("Connecting to ");
    oled.screenSettings(1, 0, 16);
    oled.print(ssid);
    oled.displayScreen();

    int timeout = 0;

    WiFi.begin(ssid, pass);
    while(WiFi.status() != WL_CONNECTED)
    {
        int j = 3;
        delay(500);
        Serial.print(".");
        for(int i = 0; i < 3; i++)
        {
            oled.screenSettings(1, i + j++, 30);
            oled.print(".");
            oled.displayScreen();
        }

        oled.clearScreen();
        oled.screenSettings(1, 0, 6);
        oled.print("Connecting to ");
        oled.screenSettings(1, 0, 16);
        oled.print(ssid);
        oled.displayScreen();

        timeout++;
        if(timeout > 30)
        {
            oled.screenSettings(1, 0, 16);
            Serial.println("\n[ERROR] WiFi connection timeout");
            oled.print("WiFi connection timeout");
            oled.displayScreen();
            delay(1000);
            WiFi.disconnect(false, false);
            return false;
        }
    }

    oled.clearScreen();
    oled.screenSettings(1, 0, 6);
    Serial.println("\n[WIFI] Connected successfully");
    Serial.print("[WIFI] IP address : ");
    Serial.println(WiFi.localIP());
    oled.print("Connected successfully");
    oled.screenSettings(1, 0, 16);
    oled.print("IP address : ");
    oled.screenSettings(1, 0, 30);
    oled.print(WiFi.localIP().toString());
    oled.displayScreen();
    delay(1000);
    oled.clearScreen();

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