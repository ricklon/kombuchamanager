#include <Arduino.h>

int relays[] = {14, 32, 27, 26, 25, 33, } ;
int num_relays = sizeof(relays) / sizeof(relays[0]);
void setup() {
  Serial.begin(9600);
  for (int ii = 0; ii < num_relays; ii++) {
    pinMode(relays[ii], OUTPUT);
  }
  for (int ii = 0; ii < num_relays; ii++) {
    digitalWrite(relays[ii], HIGH);
  }
  delay(1000);
}

void loop() {
  for (int ii = 0; ii < num_relays ; ii++)
  {
    Serial.println("HIGH");
    digitalWrite(relays[ii], LOW);
    delay(50);
  }
  for (int ii = 0; ii < num_relays ; ii++)
  {
    Serial.print(ii); Serial.print(":"); Serial.println(relays[ii]);
    digitalWrite(relays[ii], HIGH);
    Serial.print("HIGH");
    delay(500);
    digitalWrite(relays[ii], LOW);
    Serial.print("LOW");
    delay(500);
  }
  for (int ii = 0; ii < num_relays ; ii++)
  {
    Serial.println("LOW");
    digitalWrite(relays[ii], HIGH);
    delay(50);
  }
  delay(1000);


}
