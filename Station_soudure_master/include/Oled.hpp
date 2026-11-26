#ifndef OLED
#define OLED

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class Oled
{
    public:

        Oled(Adafruit_SSD1306& screen);
        
        bool begin();
        void startScreen();
        void clearScreen();
        void screenSettings(int txtSize, int xAxis, int yAxis);
        void print(String message);
        void print(int value);
        void print(float value, int decimals = 2);
        void print(double value, int decimals = 2);
        void displayScreen();
    
    private:

        Adafruit_SSD1306& oled;
};

#endif