#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 27
#define TEMPERATURE_PRECISION 9
#define MAX_DEVICES 8

int DeviceCount = 0;

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

// arrays to hold device addresses
DeviceAddress DeviceAddresses[MAX_DEVICES];

// function to print a device address
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

// function to print a device's resolution
void printResolution(DeviceAddress deviceAddress)
{
  Serial.print("Resolution: ");
  Serial.print(sensors.getResolution(deviceAddress));
  Serial.println();
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


void setup(void)
{
  // start serial port
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");

  // Start up the library
  sensors.begin();

  // locate devices on the bus
  Serial.print("Locating devices...");
  Serial.print("Found ");
  DeviceCount = sensors.getDeviceCount();
  Serial.print(DeviceCount, DEC);
  DeviceCount = 4;
  Serial.println(" devices.");

  // report parasite power requirements
  Serial.print("Parasite power is: ");
  if (sensors.isParasitePowerMode())
    Serial.println("ON");
  else Serial.println("OFF");

  // Search for devices on the bus and assign based on an index.

  for (int ii = 0; ii < DeviceCount; ii++) {
    if (!sensors.getAddress(DeviceAddresses[ii], ii)) Serial.println("Unable to find address for Device 0");
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
  while(Serial.available() == 0){}
}
  /*
     Main function, calls the temperatures in a loop.
  */
  void loop(void)
  {
    // call sensors.requestTemperatures() to issue a global temperature
    // request to all devices on the bus
    Serial.print("#Devs: ");
    Serial.print(DeviceCount);
    Serial.print("Requesting temperatures...");
    sensors.requestTemperatures();
    Serial.println("DONE");

    // print the device information
    for (int ii = 0; ii < DeviceCount; ii++) {
      printData(DeviceAddresses[ii]);
    }
    delay(333);
  }