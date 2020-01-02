/*

  Wifi Kit OLED Display
  Test Code with time since on code

*/

#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 15, /* data=*/ 4, /* reset=*/ 16);


unsigned long start = millis();
unsigned long timeNow = 0;
unsigned long secs = 1;
unsigned long mins = 0;
unsigned long hours = 0;
unsigned long days = 0;
int count = 0;

void setup(void) {
  u8g2.begin();
}

void loop(void) {
  timeNow = millis();
  secs = (timeNow / 1000) % 60;
  mins = (timeNow / (1000 * 60)) % 60;
  hours = (timeNow / (1000 * 60 * 60)) % 24;
  days =  (timeNow / (1000 * 60 * 60)) / 24;


  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);

  u8g2.setCursor(0, 10);
  u8g2.print("SRestart: ");
  u8g2.print(days);
  u8g2.print(":");
  u8g2.print(hours);
  u8g2.print(":");
  u8g2.print(mins);
  u8g2.print(":");
  u8g2.print(secs);


  u8g2.setCursor(0, 20);
  u8g2.print("Jar 1: ");
  u8g2.print(secs);

  u8g2.setCursor(0, 30);
  u8g2.print("Jar 2: ");
  u8g2.print(mins);

  u8g2.setCursor(0, 40);
  u8g2.print("Jar 3: ");
  u8g2.print(hours);

  u8g2.setCursor( 0, 50);
  u8g2.print("Jar 4: ");
  u8g2.print(days);

  u8g2.sendBuffer();
  delay(10);

}
