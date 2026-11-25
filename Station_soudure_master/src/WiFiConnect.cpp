#include "WiFiConnect.hpp"

WiFiConnect::WiFiConnect(const char ssidAP[]) : SSID_AP(ssidAP), server(80) {}

bool WiFiConnect::begin()
{
    preferences.begin("wifi-config", false);

    String ssid = preferences.getString("ssid", "");
    String pass = preferences.getString("password", "");

    if(ssid.length() > 0)
    {
        Serial.println("[WIFI] Saved credentials found");

        WiFi.mode(WIFI_AP_STA);

        if(wifiConnectToRouter(ssid.c_str(), pass.c_str()))
        {
            Serial.print("[WIFI] Successfully reconnected to ");
            Serial.println(ssid.c_str());
            return true;
        }

        Serial.println("[WIFI] Unable to reconnect!");
    }

    Serial.println("[WIFI] Starting configuration portal...");

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

    Serial.println("[WIFI AP] Web server started");
}

void WiFiConnect::getAPIP()
{
    IP = WiFi.softAPIP();
    Serial.print("[WIFI AP] AP IP address : ");
    Serial.println(IP);
    Serial.println("[WIFI AP] Connect to the hotspot and open this IP in your browser.");
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

    Serial.println("\n[WIFI] New credentials received");
    WiFi.mode(WIFI_AP_STA);

    if(wifiConnectToRouter(ssid.c_str(), pass.c_str()))
    {
        preferences.putString("ssid", ssid);
        preferences.putString("password", pass);

        server.send(200, "text/html",
            "<h1>Connected successfully!</h1>"
            "<p>Your WiFi credentials have been saved.</p>"
            "<p>You can now close this page.</p>");

        Serial.println("[WIFI] Credentials saved");
        delay(500);

        server.stop();

        WiFi.softAPdisconnect(true);
        WiFi.mode(WIFI_STA);

        Serial.println("[WIFI] Configuration complete");
    }
    else
    {
        WiFi.mode(WIFI_AP);

        server.send(200, "text/html",
            "<h1>Connection failed!</h1>"
            "<p>Please verify your SSID and password.</p>"
            "<a href='/'>Try again</a>");

        Serial.println("[WIFI] Returning to configuration portal");
    }
}

bool WiFiConnect::wifiConnectToRouter(const char ssid[], const char pass[])
{
    Serial.print("\n[WIFI] Connecting to ");
    Serial.print(ssid);

    int timeout = 0;

    WiFi.begin(ssid, pass);
    while(WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");

        timeout++;
        if(timeout > 30)
        {
            Serial.println("\n[ERROR] WiFi connection timeout");
            WiFi.disconnect(false, false);
            return false;
        }
    }

    Serial.println("\n[WIFI] Connected successfully");
    Serial.print("[WIFI] IP address : ");
    Serial.println(WiFi.localIP());

    return true;
}

bool WiFiConnect::isConnected()
{
    return WiFi.status() == WL_CONNECTED;
}