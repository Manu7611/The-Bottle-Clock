#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include <Wire.h>

#define TFT_SCLK 9
#define TFT_MOSI 10
#define TFT_RST 8
#define TFT_DC 6
#define TFT_CS 7
#define TFT_BL 21

#define SW1 2
#define SW2 3
#define SW3 4

#define BUZZER 20

Adafruit_ST7789 tft(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

int hour = 0;
int minute = 0;
unsigned long lastTick = 0;
bool ScreenOn = true;

void setup() {
pinMode(SW1, INPUT_PULLUP);
pinMode(SW2, INPUT_PULLUP);
pinMode(SW3, INPUT_PULLUP);
pinMode(TFT_BL, OUTPUT);
digitalWrite(TFT_BL, HIGH);

tft.init(76, 284); 
tft.setOffsets(82, 18);
tft.invertDisplay(false); 
tft.setRotation(1); 
tft.fillScreen(ST77XX_BLACK); 
tft.setTextColor(ST77XX_WHITE);
tft.setTextSize(4);
Serial.println("TFT Initialized!");
tft.setCursor(0,0);

}

bool pressed(int pin) {
  if (digitalRead(pin) == LOW) {
    delay(30);
    while (digitalRead(pin) == LOW);
    return true;
  }
  return false;
}
void loop() {
  if (millis() - lastTick >= 1000) {
    lastTick += 1000;
    if (++minute >=60 ) { minute = 0 ; if (++hour >=24) hour = 0;}
  }
  if (pressed(SW1)) {
    screenOn = !screenOn;
    digitalWrite(TFT_BL, screenOn ? HIGH : LOW);
  }
  if (pressed(SW2)) hour = (hour+1) % 24;
  if (pressed(SW3)) minute = (minute+1) % 60;

  if (screenOn) {
    tft.fillScreen(ST77XX_BLACK); 
    tft.setCursor(0,0);
    char buf[6];
    sprintf(buf, "%02d:%02d", hour, minute);
    tft.print(buf);
  }
  delay(200);

}
