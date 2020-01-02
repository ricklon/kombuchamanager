#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 14
#define TEMPERATURE_PRECISION 9

OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire); 

DeviceAddress devices[]; 

setup
  Serial.begin(9600); 

  sensors.begin(); 
  Serial.print(sensors.getDeviceCount(), DEC); 
  set max sensor count
  int sensor_cnt 
  for count in foundsensors
  populate address array

loop
  getallsensor values
  print all sensor values

    max, min, cur

    

