#include <Arduino.h>
#include <U8g2lib.h>
U8G2_SSD1306_128X64_NONAME_F_SW_I2C display(U8G2_R0, SCL, SDA, U8X8_PIN_NONE);
int drawcolor = 1;
void setup() {
    display.begin();
    display.clearBuffer();
    display.sendBuffer();
}
void loop(){
    display.setDrawColor(++drawcolor%2);
    uint8_t nbox[4] = {random(0,128), random(0,64), random(0,128), random(0,64)};
    uint8_t box[4] = {min(nbox[0], nbox[2]), min(nbox[1], nbox[3]), max(nbox[0], nbox[2]), max(nbox[1], nbox[3])};
    display.drawBox(box[0], box[1], box[2], box[3]);
    display.sendBuffer();
    Serial.println('['+String(box[0], HEX)+','+String(box[1], HEX)+','+String(box[2], HEX)+','+String(box[3], HEX)+']');
    delay(20);
}