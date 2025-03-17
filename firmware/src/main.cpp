#define DEBUG

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Encoder.h>
#include <OneButton.h>
#include <Wire.h>

#ifdef DEBUG
#include <Serial.h>
#endif

//Screen defines
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3D

Encoder* UserInputController;
long EncoderState = -999;
OneButton* UserInputSelector;
Adafruit_SSD1306* Screen;

void setup() {
    #ifdef DEBUG
    Serial.begin(9600);
    #endif
    UserInputController = new Encoder(2, 3);
    UserInputSelector = new OneButton(3);
    Screen = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
    if (!Screen->begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        #ifdef DEBUG
        Serial.println('FAILED TO INIT DISPLAY');
        #endif
        for(;;);
    }
    Screen->clearDisplay();
    const int16_t cx = Screen->width()/2;
    const int16_t cy = Screen->height()/2;
    const int16_t rad = min<int16_t>(2*cx, 2*cy)/2;
    const int16_t cstroke = 1;
    Screen->drawCircle(cx, cy, rad, SSD1306_WHITE);
    Screen->drawCircle(cx, cy, rad - cstroke, SSD1306_BLACK);
    Screen->display();
}

void loop() {
    volatile long nEncoderState = UserInputController->read();
    if (nEncoderState != EncoderState)
        EncoderState = nEncoderState;
    
}