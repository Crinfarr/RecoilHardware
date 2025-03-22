#include <Arduino.h>
#include <U8g2lib.h>
#include <Encoder.h>
#include <OneButton.h>

U8G2_SSD1306_128X64_NONAME_F_SW_I2C display(U8G2_R0, SCL, SDA, U8X8_PIN_NONE);
int drawcolor = 1;
Encoder uinput(9, 8);
OneButton uclick(10);

const int maxAmmo = 10;
int ammoCt = 10;
unsigned long bounceDelta = millis();

void setup() {
    display.begin();
    display.clearBuffer();
    for (int i = 0; i <= maxAmmo; i++) {
        if (i <= ammoCt) {
            display.drawBox((i - 1) * 2 + i * 12, 0, 12, 64);
        }
        else {
            display.drawFrame((i - 1) * 2 + i * 12, 0, 12, 64);
        }
    }
    display.sendBuffer();
}

void loop() {
    delay(200);
    int newpos = uinput.readAndReset();
    int dir = (0 < newpos) - (newpos < 0);
    if (dir == 0) return;
    bounceDelta = millis();
    if (dir < 0) {
        Serial.println("Moved left");
        ammoCt--;
    }

    if (dir > 0) {
        Serial.println("Moved right");
        ammoCt++;
    }
    display.clearBuffer();
    for (int i = 0; i <= maxAmmo; i++) {
        if (i <= ammoCt) {
            display.drawBox((i - 1) * 2 + i * 12, 0, 12, 64);
        }
        else {
            display.drawFrame((i - 1) * 2 + i * 12, 0, 12, 64);
        }
    }
    display.sendBuffer();

    // bool debounce = (bounceDelta + 10ul) < millis();
    // if (newpos != encPos && !debounce) {
    //     if (encPos < newpos) ammoCt++;
    //     if (encPos > newpos) ammoCt--;
    //     encPos = newpos;
    //     Serial.println("Encoder changed to " + String(encPos, DEC));
    //     display.clearBuffer();
    //     for (int i = 0; i <= maxAmmo; i++) {
    //         if (i <= ammoCt) {
    //             Serial.print('O');
    //             display.drawBox((i - 1) * 2 + i * 12, 0, 12, 64);
    //         }
    //         else {
    //             Serial.print('X');
    //             display.drawFrame((i - 1) * 2 + i * 12, 0, 12, 64);
    //         }
    //     }
    //     Serial.println();
    //     display.sendBuffer();
    // }
    // else if (!debounce) Serial.println("Debounce triggered");
}