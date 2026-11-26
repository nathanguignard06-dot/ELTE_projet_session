#include "Oled.hpp"

Oled::Oled(Adafruit_SSD1306& screen) : oled(screen) {}

bool Oled::begin()
{
    Serial.println("\n[OLED] Allocating SSD1306...");

    if(!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println(F("[OLED] SSD1306 allocation failed"));
        return false;
    }

    Serial.println("[OLED] SSD1306 allocation successful");
    return true;
}

void Oled::startScreen()
{
    clearScreen();
    screenSettings(1, 0, 10);
    print("Oled Ready!");
    displayScreen();
}

void Oled::clearScreen()
{
    oled.clearDisplay();
}

void Oled::screenSettings(int txtSize, int xAxis, int yAxis)
{
    oled.setTextSize(txtSize);
    oled.setCursor(xAxis, yAxis);
    oled.setTextColor(WHITE, BLACK);
}

void Oled::print(String message)
{
    oled.println(message);
}

void Oled::print(int value)
{
    oled.println(value);
}

void Oled::print(float value, int decimals)
{
    oled.println(value, decimals);
}

void Oled::print(double value, int decimals)
{
    oled.println(value, decimals);
}

void Oled::displayScreen()
{
    oled.display();
}