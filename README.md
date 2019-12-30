# Kombucha Manager

This is an esp32 based Kombucha Manager. The device manages 4 jars of Kombucha. It displays the temperature of each jar. It then can turn off and on via a relay the attached heater for each jar. It will keep the Kombucha jar at a specific temp range. This is especially good for indoor monitoring and winter in a house. 

Bill of Materials:
* Heltech Wifi Kit 32 with OLED Screen
* DS188c2 Dallas One wire temperature sensors
* 4 relay Module
* Strip board or Custom PCB for Dallas One wire temperature sensors using JST connectors

Assembly:
1. TBD

The code progression for creating this:
1. Test the attached relay module
2. Test the attached Dallas OneWire sensors
3. Test the Heltec OLED diplay
4. Combine the tested code into one Kombucha Manager code
5. Add wifi support 
6. Add Web Thing Support
7. Add MQTT

