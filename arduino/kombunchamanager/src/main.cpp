/*

  Wifi Kit OLED Display
  Test Code with time since on code

*/

#include <Arduino.h>
#include <U8g2lib.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "SPIFFS.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 27
#define TEMPERATURE_PRECISION 9
#define MAX_DEVICES 8
#define SENSOR_CNT 4

int DeviceCount = 0;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress DeviceAddresses[MAX_DEVICES];
float temps[SENSOR_CNT];
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 15, /* data=*/ 4, /* reset=*/ 16);


unsigned long start = millis();
unsigned long timeNow = 0;
unsigned long secs = 1;
unsigned long mins = 0;
unsigned long hours = 0;
unsigned long days = 0;
int count = 0;

void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    // zero pad the address if necessary
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

// function to print the temperature for a device
void printTemperature(DeviceAddress deviceAddress)
{
  float tempC = sensors.getTempC(deviceAddress);
  Serial.print("Temp C: ");
  Serial.print(tempC);
  Serial.print(" Temp F: ");
  Serial.print(DallasTemperature::toFahrenheit(tempC));
}
// main function to print information about a device
void printData(DeviceAddress deviceAddress)
{
  Serial.print("Device Address: ");
  printAddress(deviceAddress);
  Serial.print(" ");
  printTemperature(deviceAddress);
  Serial.println();
}

//function to print startup status
void oledPrint() {
  int line = 10;
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);

  u8g2.setCursor(0, line);
  u8g2.print("Kombucha Time");
  u8g2.print(days);
  u8g2.print(":");
  u8g2.print(hours);
  u8g2.print(":");
  u8g2.print(mins);
  u8g2.print(":");
  u8g2.print(secs);

  for (int ii = 0; ii < DeviceCount; ii++) {
    line  += 10;  
  u8g2.setCursor(0, line);
  u8g2.print("Jar ");
  u8g2.print(ii);
  u8g2.print(": ");
  u8g2.print(DallasTemperature::toFahrenheit(temps[ii]));

  }

  u8g2.sendBuffer();
  delay(333);

}

void setup(void) {
  pinMode(0, INPUT_PULLUP);

  Serial.begin(9600);
  u8g2.begin();
 
 if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  sensors.begin();
  //DeviceCount = sensors.getDeviceCount();
  DeviceCount = 4;
   for (int ii = 0; ii < DeviceCount; ii++) {
    if (!sensors.getAddress(DeviceAddresses[ii], ii)) Serial.println("Unable to find address for Device 0");
        sensors.setResolution(DeviceAddresses[ii], TEMPERATURE_PRECISION);
  }
    // show the addresses we found on the bus
  for (int ii = 0; ii < DeviceCount; ii++)  {
      Serial.print("Device[" );
      Serial.print(ii);
      Serial.print("] Address: ");
      //Serial.print(ii);
      printAddress(DeviceAddresses[ii]);
      Serial.println();

      // set the resolution to 9 bit per device
      sensors.setResolution(DeviceAddresses[ii], TEMPERATURE_PRECISION);
  }
  while(Serial.available() == 0 && digitalRead(0) == HIGH){}


}

void loop(void) {
  int line = 10;
  timeNow = millis();
  secs = (timeNow / 1000) % 60;
  mins = (timeNow / (1000 * 60)) % 60;
  hours = (timeNow / (1000 * 60 * 60)) % 24;
  days =  (timeNow / (1000 * 60 * 60)) / 24;

  sensors.requestTemperatures();


 // print the device information
    for (int ii = 0; ii < DeviceCount; ii++) {
      printData(DeviceAddresses[ii]);
      temps[ii] = sensors.getTempC(DeviceAddresses[ii]);

    }
     

  // Display Status
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);

  u8g2.setCursor(0, line);
  u8g2.print("uptime: ");
  u8g2.print(days);
  u8g2.print(":");
  u8g2.print(hours);
  u8g2.print(":");
  u8g2.print(mins);
  u8g2.print(":");
  u8g2.print(secs);

  for (int ii = 0; ii < DeviceCount; ii++) {
    line  += 10;  
  u8g2.setCursor(0, line);
  u8g2.print("Jar ");
  u8g2.print(ii);
  u8g2.print(": ");
  u8g2.print(DallasTemperature::toFahrenheit(temps[ii]));

  }

  u8g2.sendBuffer();
  delay(333);

}
